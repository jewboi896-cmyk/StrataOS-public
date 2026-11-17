#ifndef STRATA_TYPES_H
#define STRATA_TYPES_H

#pragma once

// Provides the primitive definitions
#include <stdint.h>

// Core and Null Definitions
typedef void VOID;
typedef void* PVOID;

#define NULL nullptr
typedef typeof(nullptr) NPTR;

// boolean definition
typedef uint8_t BOOL, *PBOOL;
#define TRUE 1
#define FALSE 0

// Fixed Width Integer Types
typedef uint8_t U8, *PU8;
typedef int8_t I8, *PI8;

typedef uint16_t U16, *PU16;
typedef int16_t I16, *PI16;

typedef uint32_t U32, *PU32;
typedef int32_t I32, *PI32;

typedef uint64_t U64, *PU64;
typedef int64_t I64, *PI64;

// Byte and Character Types
typedef uint8_t BYTE, *PBYTE;
typedef uint8_t UBYTE, *PUBYTE;
typedef int8_t SBYTE, *PSBYTE;

typedef char CHAR, *PCHAR;
typedef signed char SCHAR, *PSCHAR;
typedef unsigned char UCHAR, *PUCHAR;

// Standard Integer Aliases
typedef int16_t SHORT, *PSHORT;
typedef int16_t SSHORT, *PSSHORT;
typedef uint16_t USHORT, *PUSHORT;

typedef int64_t LONG, *PLONG;
typedef int64_t SLONG, *PSLONG;
typedef uint64_t ULONG, *PULONG;
typedef int64_t LLONG, *PLLONG;
typedef int64_t SLLONG, *PSLLONG;
typedef uint64_t ULLONG, *PULLONG;

// Floating Point Definitions
// These should not be used inside of the core of the kernel as they use FPU/SSE/AVX registers which are usually 
// not saved during a context switch
#ifndef STRATA_KERNEL_CORE_TYPES
  typedef float FLOAT, *PFLOAT; // 4 bytes
  typedef double DOUBLE, *PDOUBLE; // 8 bytes

  // avoid using LDOUBLE across FFI boundaries between C and the other languages used in this OS
  typedef long double LDOUBLE, *PLDOUBLE; // 16 bytes
#endif

// Memory, Address & Size Types - All 8 bytes
typedef uint64_t SIZE, *PSIZE;
typedef int64_t SSIZE, *PSSIZE;
typedef uintptr_t UPTR, *PUPTR;
typedef intptr_t IPTR, *PIPTR;

// C String aliases because C dosent have a built in String class like C++ or Java.
// C treats Strings as arrays of characters so that is what i will do
// This also makes the FFI easier between C and the other languages in this OS
typedef char* STR;
typedef char** PSTR;
typedef const char* CSTR;
typedef const char** PCSTR;

// HANDLE definition. Im borrowing from the Windows API that uses opaque pointers to files as a void pointer named HANDLE
typedef PVOID HANDLE, *PHANDLE;

#define INVALID_HANDLE ((HANDLE)(IPTR) - 1)
#define IS_VALID_HANDLE(handle) ((handle) != nullptr && (handle) != INVALID_HANDLE)

#define STRATA_DECLARE_HANDLE(name) \ typedef struct name##__ { int unused; } *name, **P##name

// Define each handle
STRATA_DECLARE_HANDLE(H_PROCESS); // Handle to a process
STRATA_DECLARE_HANDLE(H_THREAD); // Handle to a thread
STRATA_DECLARE_HANDLE(H_FILE); // Handle to a file
STRATA_DECLARE_HANDLE(H_DIRECTORY); // Handle to a directory
STRATA_DECLARE_HANDLE(H_DEVICE); // Handle to a device
STRATA_DECLARE_HANDLE(H_SOCKET); // Handle to a network socket
STRATA_DECLARE_HANDLE(H_EVENT); // Handle to an event
STRATA_DECLARE_HANDLE(H_MUTEX); // Handle to a mutex
STRATA_DECLARE_HANDLE(H_VIRT_MEM_OBJ); // Handle to a virtual memory object
STRATA_DECLARE_HANDLE(H_MEM_SECTION); // Handle to a memory section for creating shared memory buffers for zero cost IPC
STRATA_DECLARE_HANDLE(H_VIRT_ADD_SPACE); // Handle to a virtual address space
STRATA_DECLARE_HANDLE(H_DRIVER_MOD); // Handle to a driver module
STRATA_DECLARE_HANDLE(H_LIBRARY_MOD); // Handle to a library module
STRATA_DECLARE_HANDLE(H_SEMAPHORE); // Handle to a semaphore (manages resource pools)
STRATA_DECLARE_HANDLE(H_READ_WRITE_LOCK); // Handle to a Read-Write Lock
STRATA_DECLARE_HANDLE(H_TIMER); // Handle to a timer

STRATA_DECLARE_HANDLE(H_PIPE); // Handle to a pipe for IPC (Unidirectional byte stream)
STRATA_DECLARE_HANDLE(H_CHANNEL); // Handle to a channel for IPC (bidirectional message-passing endpoint)
STRATA_DECLARE_HANDLE(H_PORT); // Handle to a general I/O port
STRATA_DECLARE_HANDLE(H_IO_COMPLETION_PORT); // Handle to a completion port
STRATA_DECLARE_HANDLE(H_EVENT_QUEUE); // Handle to a event polling queue
STRATA_DECLARE_HANDLE(H_JOB); // Handle to a general job (used for tracking resource quotas, CPU limits, or killing process trees cleanly)

STRATA_DECLARE_HANDLE(H_INTERRUPT); // Handle to a general CPU interrupt 
STRATA_DECLARE_HANDLE(H_DIRECT_MEM_ACCESS_BUFF); // Handle to a direct memory access buffer
STRATA_DECLARE_HANDLE(H_TOKEN); // Handle to a token for security and stuff
// more will probably be added later/eventually

// Define STATUS return codes - Bit Packed Signed 32 bit integers
typedef I32 STATUS, *PSTATUS;

#define STRATA_SEVERITY_SUCCESS 0x0U
#define STRATA_SEVERITY_INFO 0x1U
#define STRATA_SEVERITY_WARNING 0x2U
#define STRATA_SEVERITY_ERROR 0x3U
#define STRATA_CORE 0x00U
#define STRATA_MMU 0x01U
#define STRATA_SCHED 0x02U
#define STRATA_IPC 0x03U
#define STRATA_FILESYS 0x04U
#define STRATA_DRIVER 0x05U
#define STRATA_NETWORK 0x06U
#define STRATA_SYSTEM 0x07U
#define STRATA_SECURITY 0x08U
#define STRATA_LOADER 0x09U /* lib and driver modules */
#define STRATA_INTERRUPT 0x0AU
#define STRATA_TIMER 0x0BU
#define STRATA_IO 0x0CU

#define MAKE_STATUS(severity, status_level, code) \ ((STATUS) ((((U32)(severity) & 0x3U) << 30) | \ 
                                                    (((U32)(status_level) & 0x3FU) << 24) | \ 
                                                    (((U32)(code) & 0xFFFFFFU)))) 

#define STATUS_OK(status) ((STATUS)(status) >= 0)
#define STATUS_FAILED(status) ((STATUS)(status) < 0)
#define STATUS_SEVERITY(status) (((U32)(status) >> 30) & 0x3U)
#define STATUS_STRATA(status) (((U32)(status) >> 24) & 0x3FU)
#define STATUS_CODE(status) ((U32)(status) & 0xFFFFFFU)

// Define all of the different statuses that could occur
#define STATUS_SUCCESS MAKE_STATUS(STATUS_SEVERITY_SUCCESS, STRATA_CORE, 0x000000)
#define STATUS_PENDING MAKE_STATUS(STATUS_SEVERITY_INFO, STRATA_CORE, 0x000001)
#define STATUS_GENERIC_ERROR MAKE_STATUS(STATUS_SEVERITY_ERROR, STRATA_CORE, 0x000001)
#define STATUS_INVALID_PARAMETER_ERROR MAKE_STATUS(STATUS_SEVERITY_ERROR, STRATA_CORE, 0x000002)
#define STATUS_OUT_OF_MEMORY_ERROR MAKE_STATUS(STATUS_SEVERITY_ERROR, STRATA_MMU, 0x000001)
#define STATUS_ACCESS_DENIED_ERROR MAKE_STATUS(STATUS_SEVERITY_ERROR, STRATA_CORE, 0x000003)
#define STATUS_NOT_FOUND_ERROR MAKE_STATUS(STATUS_SEVERITY_ERROR, STRATA_CORE, 0x000004)
#define STATUS_ALREADY_EXISTS_ERROR MAKE_STATUS(STATUS_SEVERITY_ERROR, STRATA_CORE, 0x000005)
#define STATUS_INVALID_HANDLE_ERROR MAKE_STATUS(STATUS_SEVERITY_ERROR, STRATA_CORE, 0x000006)
#define STATUS_NOT_IMPLEMENTED_ERROR MAKE_STATUS(STATUS_SEVERITY_ERROR, STRATA_SYSTEM, 0x000001)
#define STATUS_TIMEOUT_ERROR MAKE_STATUS(STATUS_SEVERITY_ERROR, STRATA_SCHED, 0x000001)
#define STATUS_BUFFER_TOO_SMALL_ERROR MAKE_STATUS(STATUS_SEVERITY_ERROR, STRATA_CORE, 0x000007)
#define STATUS_IO_FAILURE_ERROR MAKE_STATUS(STATUS_SEVERITY_ERROR, STRATA_DRIVER, 0x000001)
#define STATUS_BAD_IMAGE_ERROR MAKE_STATUS(STATUS_SEVERITY_ERROR, STRATA_LOADER, 0x000001)
// more will probably be added later/eventually

// Compile time architecture checks so that as much can fail at compile time rather then runtime
static_assert(sizeof(PVOID) == 8, "StrataOS requires a 64 bit target architecture");
static_assert(sizeof(LONG) == 8, "LONG must be 8 bytes on a 64 bit target architecture");
static_assert(sizeof(BOOL) == 1, "BOOL must be 1 byte on a 64 bit target architecture");
static_assert(sizeof(HANDLE) == 8, "HANDLE must be 8 bytes");
static_assert(sizeof(H_FILE) == 8, "Opaque handle must be 8 bytes");
static_assert(sizeof(STATUS) == 4, "STATUS must be 4 bytes");

#endif
