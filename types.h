#pragma once

// General Rule: Anything that has P prefixed onto it represents a pointer, U represents the unsigned version of the type, 
// and I or S represents the signed version of the type

// Provides the primitive definitions
#include <stdint.h>

// Core and Null Definitions
typedef void VOID;
typedef void* PVOID;

typedef typeof(nullptr) NPTR;
// A typedef for a non-null pointer, C doesnt have a built in type so actual enforcement needs to come through methods and runtime checks
typedef void* NNPTR;
// typedef for an optional null pointer. again C doesnt have a built in type so its aliased as a void pointer
typedef void* OPTNPTR;

// boolean definition
typedef uint8_t BOOL;
typedef uint8_t* PBOOL;
#define TRUE 1
#define FALSE 0

// Fixed Width Integer Types
typedef uint8_t U8;
typedef uint8_t* PU8;
typedef int8_t I8;
typedef int8_t* PI8;

typedef uint16_t U16;
typedef uint16_t* PU16;
typedef int16_t I16;
typedef int16_t* PI16;

typedef uint32_t U32;
typedef uint32_t* PU32;
typedef int32_t I32;
typedef int32_t* PI32;

typedef uint64_t U64;
typedef uint64_t* PU64;
typedef int64_t I64;
typedef int64_t* PI64;

// Byte and Character Types
typedef uint8_t BYTE;
typedef uint8_t* PBYTE;
typedef uint8_t UBYTE;
typedef uint8_t* PUBYTE;
typedef int8_t SBYTE;
typedef int8_t* PSBYTE;

typedef char CHAR;
typedef char* PCHAR;
typedef signed char SCHAR;
typedef signed char* PSCHAR;
typedef unsigned char UCHAR;
typedef unsigned char* PUCHAR;

// Standard Integer Aliases
typedef int16_t SHORT;
typedef int16_t* PSHORT;
typedef int16_t SSHORT;
typedef int16_t* PSSHORT;
typedef uint16_t USHORT;
typedef uint16_t* PUSHORT;

typedef int64_t LONG;
typedef int64_t* PLONG;
typedef int64_t SLONG;
typedef int64_t* PSLONG;
typedef uint64_t ULONG;
typedef uint64_t* PULONG;
typedef int64_t LLONG;
typedef int64_t* PLLONG;
typedef int64_t SLLONG;
typedef int64_t* PSLLONG;
typedef uint64_t ULLONG;
typedef uint64_t* PULLONG;

// Floating Point Definitions
// These should not be used inside of the core of the kernel as they use FPU/SSE/AVX registers which are usually 
// not saved during a context switch
#ifndef STRATA_KERNEL_CORE_TYPES
  typedef float FLOAT; // 4 bytes
  typedef float* PFLOAT;
  typedef double DOUBLE; // 8 bytes
  typedef double* PDOUBLE;

  // avoid using LDOUBLE across FFI boundaries between C and the other languages used in this OS
  typedef long double LDOUBLE; // 16 bytes
  typedef long double* PLDOUBLE;
#endif

// Memory, Address & Size Types - All 8 bytes
typedef uint64_t SIZE;
typedef uint64_t* PSIZE;
typedef int64_t SSIZE;
typedef int64_t* PSSIZE;
typedef uintptr_t UPTR;
typedef uintptr_t* PUPTR;
typedef intptr_t IPTR;
typedef intptr_t* PIPTR;

// C String aliases because C dosent have a built in String class like C++ or Java.
// C treats Strings as arrays of characters so that is what i will do
// This also makes the FFI easier between C and the other languages in this OS
typedef char* NSTR; // narrow
typedef char** PNSTR;
typedef const char* CNSTR; // const narrow
typedef const char** PCNSTR;
typedef char16_t* WSTR; // wide
typedef char16_t** PWSTR;
typedef const char16_t* CWSTR; // const wide
typedef const char16_t** PCWSTR;

// HANDLE definition. Im borrowing from the Windows API that uses opaque pointers to files as a void pointer named HANDLE
typedef PVOID HANDLE;
typedef HANDLE* PHANDLE;

#define INVALID_HANDLE ((HANDLE)(IPTR) - 1)
static inline BOOL IS_VALID_HANDLE(const HANDLE handle) { return handle != NPTR && handle != INVALID_HANDLE; }

#define STRATA_DECLARE_HANDLE(name) typedef struct name##__ *name, **P##name

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
typedef I32 STATUS;
typedef I32* PSTATUS;

// Status return codes
// Layout: 2 severity bits, 6 subsystem bits, and 24 code bits
// The result is stored as a signed 32-bit integer
#define STATUS_SEVERITY_SUCCESS 0x0U
#define STATUS_SEVERITY_INFO 0x1U
#define STATUS_SEVERITY_WARNING 0x2U
#define STATUS_SEVERITY_ERROR 0x3U
#define STATUS_CORE 0x00U
#define STATUS_MMU 0x01U
#define STATUS_SCHED 0x02U
#define STATUS_IPC 0x03U
#define STATUS_FILESYS 0x04U
#define STATUS_DRIVER 0x05U
#define STATUS_NETWORK 0x06U
#define STATUS_SYSTEM 0x07U
#define STATUS_SECURITY 0x08U
#define STATUS_LOADER 0x09U /* lib and driver modules */
#define STATUS_INTERRUPT 0x0AU
#define STATUS_TIMER 0x0BU
#define STATUS_IO 0x0CU

static inline STATUS MAKE_STATUS(const U32 severity, const U32 status_level, const U32 code) {
  const U32 value = ((severity & 0x3U) << 30U) | ((status_level & 0x3FU) << 24U) | (code & 0xFFFFFFU);
  return (STATUS) value;
} 

static inline BOOL STATUS_OK(const STATUS status) { return status >= 0; }
static inline BOOL STATUS_FAILED(const STATUS status) { return status < 0; }
static inline U32 STATUS_SEVERITY(const STATUS status) { return ((U32) status >> 30U) & 0x3U;}
static inline U32 STATUS_STRATA(const STATUS status) { return ((U32) status >> 24U) & 0x3FU; }
static inline U32 STATUS_CODE(const STATUS status) { return (U32) status & 0xFFFFFFU; }

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
static_assert(sizeof(PVOID) == 8, "64-bit architecture required");
static_assert(sizeof(LONG) == 8, "LONG must be 8 bytes on a 64 bit target architecture");
static_assert(sizeof(BOOL) == 1, "BOOL must be 1 byte on a 64 bit target architecture");
static_assert(sizeof(HANDLE) == 8, "HANDLE must be 8 bytes");
static_assert(sizeof(H_FILE) == 8, "Opaque handle must be 8 bytes");
static_assert(sizeof(STATUS) == 4, "STATUS must be 4 bytes");
