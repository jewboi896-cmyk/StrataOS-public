### 🔄 The Swappable Strata System

Unlike static hobbyist kernels, every core system and subsystem in StrataOS can be configured to use between 
**3 to 5 different algorithmic implementations**.

* **The Spectrum**: Implementations range from dead-simple (educational/naive) to full production-level stacks. This means that each system/subsystem will have multiple different implementations just with different algorithms.

* **No Code Bloat**: Swapping algorithms is handled entirely through configuration flags passed via the terminal or by editing the master `Makefile` directly. This ensures that there is no need to use complex vtable stuff to swap things out at runtime.

* **Decoupled Architecture**: Individual subsystem Makefiles instruct the master build system how to pipe configuration to the linker script, dynamically stitching together the final binary. This cleanly isolates preprocessor macros entirely outside the primary source files and headers. Note that because of this, the config files will get long, complex, and hard to read. This is a deliberate choice. I'd rather have this kind of stuff isolated from the actual logic than embedded inside of it. 

---
