# This is the first draft for the master Makefile

# This is gonna be the proposed structure:
# Each system gets its own Makefile as well as each subsystem. 
# Each subsystem's Makefile only talks to the system level Makefile
# Each system's Makefile only communicates with the Master Makefile (this file)
# This allows different drivers written in different languages to only need to worry about their own isolated files when it
# comes to building either the whole project or only rebuilding a system or subsystem
# I also want the build system to be aware so that if you only touch one thing or a few things, 
# it only rebuilds that one system or subsystem or the combined suite of changes instead of rebuilding the whole source tree
# from scratch each time 

# it will eventually live in StrataOS/src

# General Config

.DEFAULT_GOAL := all

SHELL := /bin/sh

# The current src directory
SRC_ROOT ?= .

# Main project directories
KERNEL_DIRECTORY ?= $(SRC_ROOT)/kernel
CORE_DIRECTORY ?= $(KERNEL_DIRECTORY)/core

# Build Config
BUILD_TYPE ?= release

# Make sure the build is either marked as release or debug
ifeq ($(BUILD_TYPE), release)
else ifeq ($(BUILD_TYPE), debug)
else
$(error Invalid BUILD_TYPE '$(BUILD_TYPE)'. Valid Options: release or debug)
endif

# The target architecture - currently only x86_64. If you want to add another target architecture, add it here
ARCH ?= x86_64
TARGET_TRIPLE ?= x86_64-elf

# Build output directories
BUILD_DIRECTORY ?= build
BUILD_ROOT := $(BUILD_DIRECTORY)/$(BUILD_TYPE)

OBJECT_ROOT := $(BUILD_ROOT)/obj
BINARY_ROOT := $(BUILD_ROOT)/bin
ISO_ROOT := $(BUILD_ROOT)/iso

# Individual system output directories
KERNEL_OBJECT_DIRECTORY := $(OBJECT_ROOT)/kernel
FILESYS_OBJECT_DIRECTORY := $(OBJECT_ROOT)/file_sys
DRIVERS_OBJECT_DIRECTORY := $(OBJECT_ROOT)/drivers

# Final kernel binary and ISO directories
KERNEL_ELF := $(BINARY_ROOT)/kernel.elf
ISO_IMAGE := $(ISO_ROOT)/StrataOS.iso

# Toolchain Config
# This file sets overrideable defaults that each system can tweak. Command line args also take precedence over these values
CC = x86_64-elf-gcc
CXX = x86_64-elf-g++
AS = x86_64-elf-as
LINK = ld.lld
AR = llvm-ar
RUSTC = rustc
GO = go
OBJECT_COPY = llvm-objcopy
OBJECT_DUMP = llvm-objdump

# Export the default toolchain config values to the lower Makefiles
export CC CXX AS LINK AR
export RUSTC GO OBJECT_COPY OBJECT_DUMP

# Export the default global build config values to the lower Makefiles
export ARCH TARGET_TRIPLE BUILD_TYPE
export BUILD_ROOT OBJECT_ROOT BINARY_ROOT ISO_ROOT

# Export individual output directories
export KERNEL_OBJECT_DIRECTORY FILESYS_OBJECT_DIRECTORY DRIVERS_OBJECT_DIRECTORY

# Algorithm Config
# These values are supplied via the command line
# Individual systems are responsible for validation and applying their algorithmic selection(s)
VMM_ALGORITHM ?=
PMM_ALGORITHM ?= 
SCHEDULER_ALGORITHM ?=

# Export these types
export VMM_ALGORITHM PMM_ALGORITHM SCHEDULER_ALGORITHM

# Kernel Config

CORE_ARCHIVE ?= $(KERNEL_OBJECT_DIRECTORY)/kernel_core.a

# Placeholder for additional objects produced by the other kernel components 
KERNEL_EXTRA_OBJECTS ?= 

# Linker
KERNEL_LINKER_SCRIPT ?= $(KERNEL_DIRECTORY)/linker/kernel_linker.ld

# Architecture Specific Linker Args
LINK_ARCH_FLAGS ?= -m elf_x86_64

# General Kernel Linker Flags
KERNEL_LD_FLAGS ?= -nostdlib -T $(KERNEL_LINKER_SCRIPT)

# Export the rest of the Objects 
export CORE_ARCHIVE
export KERNEL_EXTRA_OBJECTS
export KERNEL_LINKER_SCRIPT

# ISO Config

# Limine Bootloader Config
LIMINE_DIRECTORY ?= $(SRC_ROOT)/limine
LIMINE_CONFIG ?= $(KERNEL_DIRECTORY)/boot/limine.conf
LIMINE_BIOS_FILE ?= $(LIMINE_DIRECTORY)/limine-bios-cd.bin
LIMINE_UEFI_FILE ?= $(LIMINE_DIRECTORY)/limine-uefi-cd.bin

LIMINE ?= limine
XORRISO ?= xorriso

# ISO Staging Directory
ISO_STAGING_DIRECTORY := $(ISO_ROOT)/root

# QEMU Config
QEMU ?= qemu-system-$(ARCH)
QEMU_FLAGS ?= -m 2G

# Build Directories Config
.PHONY: directories

directories:
    @mkdir -p "$(KERNEL_OBJECT_DIRECTORY)"
    @mkdir -p "$(FILESYS_OBJECT_DIRECTORY)"
    @mkdir -p "$(DRIVERS_OBJECT_DIRECTORY)"
    @mkdir -p "$(BINARY_ROOT)"
    @mkdir -p "$(ISO_ROOT)"

# Core Kernel Build 
.PHONY: core

core: directories
    @if [ ! -f "$(CORE_DIRECTORY)/Makefile" ]; then \
        echo "ERROR: Kernel core Makefile not found: $(CORE_DIRECTORY)/Makefile"; \
        exit 1; \
    fi

    +$(MAKE) --no-print-directory -C "$(CORE_DIRECTORY)" all

# Kernel Linking 
.PHONY: kernel

kernel: $(KERNEL_ELF)

$(KERNEL_ELF): core
    @if [ ! -f "$(CORE_ARCHIVE)" ]; then \
        echo "ERROR: Kernel core archive was not produced: $(CORE_ARCHIVE)"; \
        exit 1; \
    fi

    @echo "Linking kernel..."

    $(LINK) $(LINK_ARCH_FLAGS) $(KERNEL_LD_FLAGS) \
        -o "$@" \
        $(KERNEL_EXTRA_OBJECTS) \
        "$(CORE_ARCHIVE)"

    @echo "Kernel successfully linked: $@"

# ISO Generation 
.PHONY: iso

iso: kernel directories
    @if [ ! -f "$(LIMINE_CONFIG)" ]; then \
        echo "ERROR: Limine configuration not found: $(LIMINE_CONFIG)"; \
        exit 1; \
    fi

    @if [ ! -f "$(LIMINE_BIOS_FILE)" ]; then \
		    echo "ERROR: Limine BIOS image not found: $(LIMINE_BIOS_FILE)"; \
		    exit 1; \
    fi

    @if [ ! -f "$(LIMINE_UEFI_FILE)" ]; then \
		    echo "ERROR: Limine UEFI image not found: $(LIMINE_UEFI_FILE)"; \
		    exit 1; \
	  fi

    @echo "Prepping ISO Staging Directory..."

    rm -rf "$(ISO_STAGING_DIRECTORY)"
    mkdir -p "$(ISO_STAGING_DIRECTORY)/boot/limine"

    cp "$(KERNEL_ELF)" "$(ISO_STAGING_DIRECTORY)/boot/kernel.elf"
    cp "$(LIMINE_CONFIG)" "S(ISO_STAGING_DIRECTORY)/limine.conf"

    cp -R "$(LIMINE_DIRECTORY)/." "$(ISO_STAGING_DIRECTORY)/boot/limine"

    @echo "Generating StrataOS ISO..."

    $(XORRISO) -as mkisofs \
        -R -r -J \
        -b boot/limine/limine-bios-cd.bin \
        -no-emul-boot \
        -boot-load-size 4 \
        -boot-info-table \
        --efi-boot boot/limine/limine-uefi-cd.bin \
        --efi-boot-part \
        --efi-boot-image \
        --protective-msdos-label \
        "$(ISO_STAGING_DIRECTORY)" \
        -o "$(ISO_IMAGE)"

    $(LIMINE) bios-install "$(ISO_IMAGE)"

    @echo "ISO successfully generated: $(ISO_IMAGE)"


# QEMU Config
.PHONY: run debug

# Normal execution path
run: iso
    $(QEMU) $(QEMU_FLAGS) -cdrom "$(ISO_IMAGE)"

# QEMU execution with GDB debugging interface enabled
# -s opens server on TCP port 1234
# -S pauses VM until GDB connects
debug: iso
      $(QEMU) $(QEMU_FLAGS) -cdrom "$(ISO_IMAGE)" -s -S

# Cleanup related Config
.PHONY: clean distclean

# Remove only the currently selected build config
clean:
    rm -rf "$(BUILD_ROOT)"

# Remove all build configs
distclean:
    rm -rf "$(BUILD_DIRECTORY)"

# Default Target
.PHONY: all

all: iso
