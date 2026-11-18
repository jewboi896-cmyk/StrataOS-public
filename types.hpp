#ifndef STRATA_TYPES_HPP
#define STRATA_TYPES_HPP

#pragma once

// General Rule: Anything that has P prefixed onto it represents a pointer, U represents the unsigned version of the type, 
// and I or S represents the signed version of the type

// Provides primitive definitions
#include <cstddef>
#include <cstdint>

// for the non-null wrapper class
#include <cassert>

// for the optional null pointer
#include <optional>

// Core and Null Definitions
using VOID = void;
using PVOID = void*;
using NPTR = decltype(nullptr);

// class for a non-null pointer as C++ doesnt have a built-in type and i think it would be generally easier to be able to
// distinguish explicitly these sorts of things
class NonNull {
private:
   void* ptr;
public:
   explicit NonNull(void* ptr) : ptr(ptr) { assert(ptr != nullptr); }
   void* get() const noexcept { return ptr; } 
};

using NNPTR = NonNull;

using OPTNPTR = std::optional<NonNull>;

// Boolean definition
using BOOL = std::uint8_t;
using PBOOL = BOOL*;

inline constexpr BOOL TRUE = 1;
inline constexpr BOOL FALSE = 0;

// Fixed Width Integer Types
using U8 = std::uint8_t;
using PU8 = U8*;
using I8 = std::int8_t;
using PI8 = I8*;

using U16 = std::uint16_t;
using PU16 = U16*;
using I16 = std::int16_t;
using PI16 = I16*;

using U32 = std::uint32_t;
using PU32 = U32*;
using I32 = std::int32_t;
using PI32 = I32*;

using U64 = std::uint64_t;
using PU64 = U64*;
using I64 = std::int64_t;
using PI64 = I64*;

// Byte and Character Types
using BYTE = std::uint8_t;
using PBYTE = BYTE*;

using UBYTE = std::uint8_t;
using PUBYTE = UBYTE*;

using SBYTE = std::int8_t;
using PSBYTE = SBYTE*;

using CHAR = char;
using PCHAR = CHAR*;

using SCHAR = signed char;
using PSCHAR = SCHAR*;

using UCHAR = unsigned char;
using PUCHAR = UCHAR*;

// Standard Integer Aliases
using SHORT = std::int16_t;
using PSHORT = SHORT*;

using SSHORT = std::int16_t;
using PSSHORT = SSHORT*;

using USHORT = std::uint16_t;
using PUSHORT = USHORT*;

using LONG = std::int64_t;
using PLONG = LONG*;

using SLONG = std::int64_t;
using PSLONG = SLONG*;

using ULONG = std::uint64_t;
using PULONG = ULONG*;

using LLONG = std::int64_t;
using PLLONG = LLONG*;

using SLLONG = std::int64_t;
using PSLLONG = SLLONG*;

using ULLONG = std::uint64_t;
using PULLONG = ULLONG*;

// Floating Point Definitions
// These should not be used inside the kernel core because they may use
// FPU/SSE/AVX registers, which are not necessarily saved during a context
// switch. Define STRATA_KERNEL_CORE_TYPES to omit these aliases
#ifndef STRATA_KERNEL_CORE_TYPES
  using FLOAT = float;
  using PFLOAT = FLOAT*;

  using DOUBLE = double;
  using PDOUBLE = DOUBLE*;

  // Avoid using LDOUBLE across FFI boundaries between C and other OS languages
  using LDOUBLE = long double;
  using PLDOUBLE = LDOUBLE*;
#endif

// Memory, Address, and Size Types
using SIZE = std::uint64_t;
using PSIZE = SIZE*;

using SSIZE = std::int64_t;
using PSSIZE = SSIZE*;

using UPTR = std::uintptr_t;
using PUPTR = UPTR*;

using IPTR = std::intptr_t;
using PIPTR = IPTR*;

// String aliases
// Represented as character pointers to preserve C ABI compatibility and the other languages used
using STR = char*;
using PSTR = STR*;

using CSTR = const char*;
using PCSTR = CSTR*;

// Generic HANDLE definition mirroring the Windows API naming conventions
// Since generic HANDLEs are just opaque pointers, use the strongly typed handles when the type is known
using HANDLE = PVOID;
using PHANDLE = HANDLE*;

// The reserved invalid generic handle representation
// The conversion is implementation defined so its intentionally not marked as constexpr
inline HANDLE const INVALID_HANDLE = reinterpret_cast<HANDLE>(static_cast<UPTR>(~UPTR{0}));

[[nodiscard]] inline bool IS_VALID_HANDLE(const HANDLE handle) noexcept {
  return handle != nullptr && handle  != INVALID_HANDLE;
}

// Declare distinct and intentionally incomplete struct type for each distinct handle category 
// This provides type safety without needing to construct a dummy object each time we need a new type
#define STRATA_DECLARE_HANDLE(name) \
  struct name##__;                  \
  using name = name##__*;           \
  using P##name = name*

// Typed Handles
STRATA_DECLARE_HANDLE(H_PROCESS); // Handle to a process
STRATA_DECLARE_HANDLE(H_THREAD); // Handle to a thread
STRATA_DECLARE_HANDLE(H_FILE); // Handle to a file
STRATA_DECLARE_HANDLE(H_DIRECTORY); // Handle to a directory
STRATA_DECLARE_HANDLE(H_DEVICE); // Handle to a device
STRATA_DECLARE_HANDLE(H_SOCKET); // Handle to a network socket
STRATA_DECLARE_HANDLE(H_EVENT); // Handle to an event
STRATA_DECLARE_HANDLE(H_MUTEX); // Handle to a mutex
STRATA_DECLARE_HANDLE(H_VIRT_MEM_OBJ); // Handle to a virtual memory object
STRATA_DECLARE_HANDLE(H_MEM_SECTION); // Handle to a memory section for shared-memory IPC
STRATA_DECLARE_HANDLE(H_VIRT_ADD_SPACE); // Handle to a virtual address space
STRATA_DECLARE_HANDLE(H_DRIVER_MOD); // Handle to a driver module
STRATA_DECLARE_HANDLE(H_LIBRARY_MOD); // Handle to a library module
STRATA_DECLARE_HANDLE(H_SEMAPHORE); // Handle to a semaphore
STRATA_DECLARE_HANDLE(H_READ_WRITE_LOCK); // Handle to a read-write lock
STRATA_DECLARE_HANDLE(H_TIMER); // Handle to a timer
STRATA_DECLARE_HANDLE(H_PIPE); // Handle to a unidirectional IPC byte stream
STRATA_DECLARE_HANDLE(H_CHANNEL); // Handle to a bidirectional IPC message endpoint
STRATA_DECLARE_HANDLE(H_PORT); // Handle to a general I/O port
STRATA_DECLARE_HANDLE(H_IO_COMPLETION_PORT); // Handle to a completion port
STRATA_DECLARE_HANDLE(H_EVENT_QUEUE); // Handle to an event-polling queue
STRATA_DECLARE_HANDLE(H_JOB); // Handle to a job
STRATA_DECLARE_HANDLE(H_INTERRUPT); // Handle to a CPU interrupt
STRATA_DECLARE_HANDLE(H_DIRECT_MEM_ACCESS_BUFF); // Handle to a DMA buffer
STRATA_DECLARE_HANDLE(H_TOKEN); // Handle to a security token

// Status return codes
// Layout: 2 severity bits, 6 subsystem bits, and 24 code bits
// The result is stored as a signed 32-bit integer
using STATUS = I32;
using PSTATUS = STATUS*;

inline constexpr U32 STRATA_SEVERITY_SUCCESS = 0x0U;
inline constexpr U32 STRATA_SEVERITY_INFO = 0x1U;
inline constexpr U32 STRATA_SEVERITY_WARNING = 0x2U;
inline constexpr U32 STRATA_SEVERITY_ERROR = 0x3U;

inline constexpr U32 STRATA_CORE = 0x00U;
inline constexpr U32 STRATA_MMU = 0x01U;
inline constexpr U32 STRATA_SCHED = 0x02U;
inline constexpr U32 STRATA_IPC = 0x03U;
inline constexpr U32 STRATA_FILESYS = 0x04U;
inline constexpr U32 STRATA_DRIVER = 0x05U;
inline constexpr U32 STRATA_NETWORK = 0x06U;
inline constexpr U32 STRATA_SYSTEM = 0x07U;
inline constexpr U32 STRATA_SECURITY = 0x08U;
inline constexpr U32 STRATA_LOADER = 0x09U; // Libraries and modules
inline constexpr U32 STRATA_INTERRUPT = 0x0AU;
inline constexpr U32 STRATA_TIMER = 0x0BU;
inline constexpr U32 STRATA_IO = 0x0CU;

[[nodiscard]] constexpr STATUS MAKE_STATUS(const U32 severity, const U32 status_level, const U32 code) noexcept {
  const U32 value = ((severity & 0x3U) << 30U) | ((status_level & 0x3FU) << 24U) | (code & 0xFFFFFFU);
  return static_cast<STATUS>(value);
}

[[nodiscard]] constexpr bool STATUS_OK(const STATUS status) noexcept {
  return status >= 0;
}

[[nodiscard]] constexpr bool STATUS_FAILED(const STATUS status) noexcept {
  return status < 0;
}

[[nodiscard]] constexpr U32 STATUS_SEVERITY(const STATUS status) noexcept {
  return (static_cast<U32>(status) >> 30U) & 0x3U;
}

[[nodiscard]] constexpr U32 STATUS_STRATA(const STATUS status) noexcept {
  return (static_cast<U32>(status) >> 24U) & 0x3FU;
}

[[nodiscard]] constexpr U32 STATUS_CODE(const STATUS status) noexcept {
  return static_cast<U32>(status) & 0xFFFFFFU;
}

// Define status values
inline constexpr STATUS STATUS_SUCCESS = MAKE_STATUS(STRATA_SEVERITY_SUCCESS, STRATA_CORE, 0x000000U);
inline constexpr STATUS STATUS_PENDING = MAKE_STATUS(STRATA_SEVERITY_INFO, STRATA_CORE, 0x000001U);
inline constexpr STATUS STATUS_GENERIC_ERROR = MAKE_STATUS(STRATA_SEVERITY_ERROR, STRATA_CORE, 0x000001U);
inline constexpr STATUS STATUS_INVALID_PARAMETER_ERROR = MAKE_STATUS(STRATA_SEVERITY_ERROR, STRATA_CORE, 0x000002U);
inline constexpr STATUS STATUS_OUT_OF_MEMORY_ERROR = MAKE_STATUS(STRATA_SEVERITY_ERROR, STRATA_MMU, 0x000001U);
inline constexpr STATUS STATUS_ACCESS_DENIED_ERROR = MAKE_STATUS(STRATA_SEVERITY_ERROR, STRATA_CORE, 0x000003U);
inline constexpr STATUS STATUS_NOT_FOUND_ERROR = MAKE_STATUS(STRATA_SEVERITY_ERROR, STRATA_CORE, 0x000004U);
inline constexpr STATUS STATUS_ALREADY_EXISTS_ERROR = MAKE_STATUS(STRATA_SEVERITY_ERROR, STRATA_CORE, 0x000005U);
inline constexpr STATUS STATUS_INVALID_HANDLE_ERROR = MAKE_STATUS(STRATA_SEVERITY_ERROR, STRATA_CORE, 0x000006U);
inline constexpr STATUS STATUS_NOT_IMPLEMENTED_ERROR = MAKE_STATUS(STRATA_SEVERITY_ERROR, STRATA_SYSTEM, 0x000001U);
inline constexpr STATUS STATUS_TIMEOUT_ERROR = MAKE_STATUS(STRATA_SEVERITY_ERROR, STRATA_SCHED, 0x000001U);
inline constexpr STATUS STATUS_BUFFER_TOO_SMALL_ERROR = MAKE_STATUS(STRATA_SEVERITY_ERROR, STRATA_CORE, 0x000007U);
inline constexpr STATUS STATUS_IO_FAILURE_ERROR = MAKE_STATUS(STRATA_SEVERITY_ERROR, STRATA_DRIVER, 0x000001U);
inline constexpr STATUS STATUS_BAD_IMAGE_ERROR = MAKE_STATUS(STRATA_SEVERITY_ERROR, STRATA_LOADER, 0x000001U);

// Compile time architecture and ABI checks
static_assert(sizeof(PVOID) == 8, "64-bit target architecture required");
static_assert(sizeof(LONG) == 8, "LONG must be 8 bytes");
static_assert(sizeof(BOOL) == 1, "BOOL must be 1 byte");
static_assert(sizeof(HANDLE) == 8, "HANDLE must be 8 bytes");
static_assert(sizeof(H_FILE) == 8, "Opaque handles must be 8 bytes");
static_assert(sizeof(STATUS) == 4, "STATUS must be 4 bytes");
static_assert(sizeof(SIZE) == 8 && sizeof(SSIZE) == 8, "SIZE and SSIZE must be 8 bytes");
static_assert(sizeof(UPTR) == 8 && sizeof(IPTR) == 8, "Pointer-sized integer types must be 8 bytes");

#endif
