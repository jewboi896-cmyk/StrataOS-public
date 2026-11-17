// Rust implementation of types.h and types.hpp
#![allow(non_camel_case_types)]
#![allow(non-snake-case)]

use core::ffi::{c_char, c_void};
use core::ptr::NonNull;

// Core and Null Definitions
pub type VOID = ();
pub type PVOID = *mut c_void;
// Rust has no direct nullptr_t equivalent so at this time, this isnt intended to by C ABI compatible as this is 
//Optional, guaranteed-non-null pointer when present
pub type OPTNPTR = Option<NonNull<c_void>>;
// because of the reason above, this is a guaranteed non-null pointer
pub type NNPTR = NonNull<c_void>;

// Boolean Type Definitions
pub type BOOL = u8;
pub type PBOOL = *mut BOOL;
pub const TRUE: BOOL = 1;
pub const FALSE: BOOL = 0;

// 8-bit Integer Definitions
pub type U8 = u8;
pub type PU8 = *mut U8;
pub type I8 = i8;
pub type PI8 = *mut I8;

// 16-bit Integer Definitions
pub type U16 = u16;
pub type PU16 = *mut U16;
pub type I16 = i16;
pub type PI16 = *mut I16;

// 32-bir Integer Definitions
pub type U32 = u32;
pub type PU32 = *mut U32;
pub type I32 = i32;
pub type PI32 = *mut I32;

// 64-bit Integer Definitions
pub type U64 = u64;
pub type PU64 = *mut U64;
pub type I64 = i64;
pub type PI64 = *mut I64;

// Byte Definitions
pub type BYTE = u8;
pub type PBYTE = *mut BYTE;
pub type UBYTE = u8;
pub type PUBYTE = *mut UBYTE;
pub type SBYTE = i8;
pub type PSBYTE = *mut SBYTE;

// Character Definitions
pub type CHAR = c_char;
pub type PCHAR = *mut CHAR;
pub type SCHAR = i8;
pub type PSCHAR = *mut SCHAR;
pub type UCHAR = u8;
pub type PUCHAR = *mut UCHAR;

// Short Definitions
pub type SHORT = i16;
pub type PSHORT = *mut SHORT;
pub type SSHORT = i16;
pub type PSSHORT = *mut SSHORT;
pub type USHORT = u16;
pub type PUSHORT = *mut USHORT;

// Long definitions
pub type LONG = i64;
pub type PLONG = *mut LONG;
pub type SLONG = i64;
pub type PSLONG = *mut SLONG;
pub type ULONG = u64;
pub type PULONG = *mut ULONG;
pub type LLONG = i64;
pub type PLLONG = *mut LLONG;
pub type SLLONG = i64;
pub type PSLLONG = *mut SLLONG;
pub type ULLONG = u64;
pub type PULLONG = *mut ULLONG;

// Enable the Cargo feature to omit floating point alias types in the core kernel sections
// They can use FPU/SSE/AVX registers, which are not necessarily saved during a context switch
#[cfg(not(feature = "strata-kernel-core-types"))]
pub type FLOAT = f32;
#[cfg(not(feature = "strata-kernel-core-types"))]
pub type PFLOAT = *mut FLOAT;
#[cfg(not(feature = "strata-kernel-core-types"))]
pub type DOUBLE = f32;
#[cfg(not(feature = "strata-kernel-core-types"))]
pub type PDOUBLE = *mut DOUBLE;
// Rust has no portable primitive equivalent to C++ `long double`.
// f64 is used as an explicit approximation; it may have less precision.
#[cfg(not(feature = "strata-kernel-core-types"))]
pub type LDOUBLE = f64;
#[cfg(not(feature = "strata-kernel-core-types"))]
pub type PLDOUBLE = *mut LDOUBLE;

// Size Type Definitions
pub type SIZE = u64;
pub type PSIZE = *mut SIZE;
pub type SSIZE = i64;
pub type PSSIZE = *mut SSIZE;

// Pointer Type Definitions
pub type UPTR = usize;
pub type PUPTR = *mut UPTR;
pub type IPTR = isize;
pub type PIPTR = *mut IPTR;

// String Type Definitions
// String treated as characters to preserve C ABI
pub type STR = *mut c_char;
pub type PSTR = *mut STR;
pub type CSTR = *const c_char;
pub type PCSTR = *mut CSTR;

// Generic HANDLE definitions
pub type HANDLE = PVOID;
pub type PHANDLE = *mut HANDLE;
// Never dereference this value
pub type INVALID_HANDLE: HANDLE = usize::MAX as HANDLE;

#[must-use]
#[inline]
pub const fn IS_HANDLE_VALID(handle: HANDLE) -> bool {
  !handle.is_null() && handle != INVALID_HANDLE;
}

// Distinct opaque handle wrappers. repr(transparent) preserves pointer ABI
macro_rules! strata_declare_handle {
  ($name:ident, $opaque:ident, $pointer_name:ident) => {
    #[repr(C)]
    pub struct $opaque { _private: [u8; 0]}

    #[repr(transparent)]
    #[derive(Clone, Copy, Debug, Eq, PartialEq, Hash)]
    pub struct $name(*mut $opaque);

    impl $name {
      #[must-use]
      #[inline]
      pub const fn from_ptr(ptr: *mut $opaque) -> Self { Self(ptr) }

      #[must-use]
      #[inline]
      pub const fn as_ptr(self) -> *mut opaque { self.0 }

      #[must-use]
      #[inline]
      pub const fn is_null(self) -> bool { self.0.is_null() }
    }

    pub type $pointer_name  = *mut $name;
  };
}

strata_declare_handle!(H_PROCESS, H_PROCESS__, PH_PROCESS);
strata_declare_handle!(H_THREAD, H_THREAD__, PH_THREAD);
strata_declare_handle!(H_FILE, H_FILE__, PH_FILE);
strata_declare_handle!(H_DIRECTORY, H_DIRECTORY__, PH_DIRECTORY);
strata_declare_handle!(H_DEVICE, H_DEVICE__, PH_DEVICE);
strata_declare_handle!(H_SOCKET, H_SOCKET__, PH_SOCKET);
strata_declare_handle!(H_EVENT, H_EVENT__, PH_EVENT);
strata_declare_handle!(H_MUTEX, H_MUTEX__, PH_MUTEX);
strata_declare_handle!(H_VIRT_MEM_OBJ, H_VIRT_MEM_OBJ__, PH_VIRT_MEM_OBJ);
strata_declare_handle!(H_MEM_SECTION, H_MEM_SECTION__, PH_MEM_SECTION);
strata_declare_handle!(H_VIRT_ADD_SPACE, H_VIRT_ADD_SPACE__, PH_VIRT_ADD_SPACE);
strata_declare_handle!(H_DRIVER_MOD, H_DRIVER_MOD__, PH_DRIVER_MOD);
strata_declare_handle!(H_LIBRARY_MOD, H_LIBRARY_MOD__, PH_LIBRARY_MOD);
strata_declare_handle!(H_SEMAPHORE, H_SEMAPHORE__, PH_SEMAPHORE);
strata_declare_handle!(H_READ_WRITE_LOCK, H_READ_WRITE_LOCK__, PH_READ_WRITE_LOCK);
strata_declare_handle!(H_TIMER, H_TIMER__, PH_TIMER);
strata_declare_handle!(H_PIPE, H_PIPE__, PH_PIPE);
strata_declare_handle!(H_CHANNEL, H_CHANNEL__, PH_CHANNEL);
strata_declare_handle!(H_PORT, H_PORT__, PH_PORT);
strata_declare_handle!(H_IO_COMPLETION_PORT, H_IO_COMPLETION_PORT__, PH_IO_COMPLETION_PORT);
strata_declare_handle!(H_EVENT_QUEUE, H_EVENT_QUEUE__, PH_EVENT_QUEUE);
strata_declare_handle!(H_JOB, H_JOB__, PH_JOB);
strata_declare_handle!(H_INTERRUPT, H_INTERRUPT__, PH_INTERRUPT);
strata_declare_handle!(H_DIRECT_MEM_ACCESS_BUFF, H_DIRECT_MEM_ACCESS_BUFF__, PH_DIRECT_MEM_ACCESS_BUFF);
strata_declare_handle!(H_TOKEN, H_TOKEN__, PH_TOKEN);

// Status Definitions
pub type STATUS = I32;
pub type PSTATUS = *mut STATUS;

// All of the different statuses
pub const STRATA_SEVERITY_SUCCESS: U32 = 0x0;
pub const STRATA_SEVERITY_INFO: U32 = 0x1;
pub const STRATA_SEVERITY_WARNING: U32 = 0x2;
pub const STRATA_SEVERITY_ERROR = 0x3;

// The strata where the status occured in
pub const STRATA_CORE: U32 = 0x00;
pub const STRATA_MMU: U32 = 0x01;
pub const STRATA_SCHED: U32 = 0x02;
pub const STRATA_IPC: U32 = 0x03;
pub const STRATA_FILESYS: U32 = 0x04;
pub const STRATA_DRIVER: U32 = 0x05;
pub const STRATA_NETWORK: U32 = 0x06;
pub const STRATA_SYSTEM: U32 = 0x07;
pub const STRATA_SECURITY: U32 = 0x08;
pub const STRATA_LOADER: U32 = 0x09; // For modules and library related things
pub const STRATA_INTERRUPT: U32 = 0x0A;
pub const STRATA_TIMER: U32 = 0x0B;
pub const STRATA_IO: U32 = 0x0C;

// Makes a MAKE_STATUS
#[must_use]
#[inline]
pub const fn MAKE_STATUS(severity: U32, status_level: U32, status_code: U32) -> STATUS {
  let bits = ((severity & 0x3) << 30) | ((status_level & 0x3F) << 24) | (status_code & 0x00FF_FFFF); 
  bits as STATUS
}

#[must_use]
#[inline]
pub const fn STATUS_OK(status: STATUS) -> bool { status >= 0 }

#[must_use]
#[inline]
pub const fn STATUS_FAILED(status: STATUS) -> bool { status < 0 }

#[must_use]
#[inline]
pub const fn STATUS_SEVERITY(status: STATUS) -> U32 { ((status as U32) >> 30) & 0x3 }

#[must_use]
#[inline]
pub const fn STATUS_STRATA(status: STATUS) -> U32 { ((status as U32) >> 24) & 0x3F }

#[must_use]
#[inline]
pub const fn STATUS_CODE(status: STATUS) -> U32 { (status as U32) & 0x00FF_FFFF}

// All error states as they currently are
pub const STATUS_SUCCESS: STATUS = MAKE_STATUS(STRATA_SEVERITY_SUCCESS, STRATA_CORE, 0x000000);
pub const STATUS_PENDING: STATUS = MAKE_STATUS(STRATA_SEVERITY_INFO, STRATA_CORE, 0x000001);
pub const STATUS_GENERIC_ERROR: STATUS = MAKE_STATUS(STRATA_SEVERITY_ERROR, STRATA_CORE, 0x000001);
pub const STATUS_INVALID_PARAMETER_ERROR: STATUS = MAKE_STATUS(STRATA_SEVERITY_ERROR, STRATA_CORE, 0x000002);
pub const STATUS_OUT_OF_MEMORY_ERROR: STATUS = MAKE_STATUS(STRATA_SEVERITY_ERROR, STRATA_MMU, 0x000001);
pub const STATUS_ACCESS_DENIED_ERROR: STATUS = MAKE_STATUS(STRATA_SEVERITY_ERROR, STRATA_CORE, 0x000003);
pub const STATUS_NOT_FOUND_ERROR: STATUS = MAKE_STATUS(STRATA_SEVERITY_ERROR, STRATA_CORE, 0x000004);
pub const STATUS_ALREADY_EXISTS_ERROR: STATUS = MAKE_STATUS(STRATA_SEVERITY_ERROR, STRATA_CORE, 0x000005);
pub const STATUS_INVALID_HANDLE_ERROR: STATUS = MAKE_STATUS(STRATA_SEVERITY_ERROR, STRATA_CORE, 0x000006);
pub const STATUS_NOT_IMPLEMENTED_ERROR: STATUS = MAKE_STATUS(STRATA_SEVERITY_ERROR, STRATA_SYSTEM, 0x000001);
pub const STATUS_TIMEOUT_ERROR: STATUS = MAKE_STATUS(STRATA_SEVERITY_ERROR, STRATA_SCHED, 0x000001);
pub const STATUS_BUFFER_TOO_SMALL_ERROR: STATUS = MAKE_STATUS(STRATA_SEVERITY_ERROR, STRATA_CORE, 0x000007);
pub const STATUS_IO_FAILURE_ERROR: STATUS = MAKE_STATUS(STRATA_SEVERITY_ERROR, STRATA_DRIVER, 0x000001);
pub const STATUS_BAD_IMAGE_ERROR: STATUS = MAKE_STATUS(STRATA_SEVERITY_ERROR, STRATA_LOADER, 0x000001);

// Compile time architecture checks
const _: () = {
  assert!(core::mem::size_of::<PVOID>() == 8, "64-bit target architecture required");
  assert!(core::mem::size_of::<LONG>() == 8, "LONG must be 8 bytes");
  assert!(core::mem::size_of::<BOOL>() == 1, "BOOL must be 1 byte");
  assert!(core::mem::size_of::<HANDLE>() == 8, "HANDLE must be 8 bytes");
  assert!(core::mem::size_of::<H_FILE>() == 8, "Opaque handles must be 8 bytes");
  assert!(core::mem::size_of::<STATUS>() == 4, "STATUS must be 4 bytes");
  assert!(core::mem::sizeof::<SIZE>() == 8, "SIZE must be 8 bytes");
  assert!(core::mem::sizeof::<SSIZE>() == 8, "SSIZE must be 8 bytes");
  assert!(core::mem::sizeof::<UPTR>() == 8, "UPTR must be 8 bytes");
  assert!(core::mem::sizeof::<IPTR>() == 8, "IPTR must be 8 bytes");
}
