## 🔬 Language & Subsystem Matrix

| Stratum / Layer | Language | Architectural Purpose |
| :--- | :---: | :--- |
| **Core Kernel** | `Pure C` | Core executive, MMU, scheduling, and foundational stubs. |
| **Filesystem** | `Rust` | Filesystem and all related things like a terminal, etc |
| **Drivers & Non-Core** | `Polyglot` | Modular extensions written in C, C++, C3, Rust, Zig, and/or Odin. |
| **Network Stack** | `C / C++ / C3` | Custom-built network stack running native drivers. |
| **Network Interactivity Layer** | `Go` | Handled seamlessly via a dedicated Go runtime wrapper. |

## ⚠️ Custom System Call & Existing Binary Compatibility
> I'm planning on creating my own custom system call numbers and such. This means that no app can natively run on this without code modification. This is a deliberate decision and I understand the implications.
> As such, all of the user-space stuff will be quite extensive and cover a wide range of projects so as to reduce the dependence on needing to rewrite existing systems to comply with my syscall mappings.
> I am planning on writing a custom intercept and mapping layer eventually so that apps don't need to be rewritten but until that point in time comes, you are on your own for this stuff. Thank you for your understanding.

---
