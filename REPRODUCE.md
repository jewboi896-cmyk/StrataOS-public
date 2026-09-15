## 🐳 Reproducibility & Containerization

I am planning on using Docker eventually but until then, the languages standards at the moment will be the following 
(I will update these as newer stable standards come out until development starts at which point, 
these toolchains will become locked for a time.):

| Language | Current Stable Version (2026) | Notes |
| :--- | :---: | :--- |
| C | C23 | Core kernel systems/subsystems, drivers, networking, etc |
| Rust | 1.97.1 | Filesystem, drivers, certain CLI tools, etc |
| C++ | C++23 | drivers, networking, etc |
| Zig | 0.16.0 | Will not be used until at least 1.0 release and confirmed solid freestanding support |
| Odin | dev-2026-08 | Same as Zig above |
| C3 | 0.8.3 | Same as both Zig and Odin |
| Go | 1.27.0 | Networking middleman, user-space apps, etc |

Anyone is free to open PRs expanding the containerization infrastructure but just like adding another build system, 
you will be solely responsible for building, testing, deploying, and maintaining it. I will not help you.

**Golang Note**: Go will be used as the middleman for the network stack. It will sit on top of the kernel network drivers 
but under the user-space apps that call the network drivers. This is the only place where Go will be used in this capacity. 
It will live in user-space. Any user-space apps are free to use whatever language the creator wants. 
The above languages (excluding Go for the reasons above) will be used for the kernel space mostly.

**Zig, Odin, C3 Note**: If these languages are added to the stack, they will be kernel space driver(s) and user space 
stuff only as C, C++, and Rust will do most of the heavy lifting.

---
