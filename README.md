# StrataOS-public

# Intro
this is a custom OS targeting x86_64 built for myself as well as an educational tool to help beginners understand OS concepts.
It uses the Limine Bootloader. It will have two sets of documentation: 1.) auto generated API and standard library docs using external tools that scrape the method signatures and compiles complete documentation and 2.) custom made docs geared towards beginners that explain the "why" behind OS concepts. This is planned to be the following: each system/subsystem can be configured to use between 3-5 different implementations of each system/subsystem that can be swapped either via flags passed in via the terminal or you can edit the master Makefile directly. the algorithms will range from as simple as possible to full production level stack. Each system/subsystem will have their own Makefiles that exist to tell the master Makefile how to tell the linker script how to stitch together the final binary. it also exists to keep the preprocessor stuff out of the actual code files and header files (for the applicable languages).

# Lang Stack
Core kernel systems/subsystems: pure C

Drivers and non-core systems/subsystems: mix of possible languages include: C, C++, C3, Rust, Zig and/or Odin

I also want to implement my own simple network stack with drivers either in: C, C++, or C3. Interactivity through a Go wrapper

# Virtual Machine/Emulator Support
Initial support will be limited to only QEMU for now. Plans exist to add support for both Bochs and VirtualBox emulators in the future


# Build System
The build system will be GNU Make
