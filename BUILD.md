## 🏗 Build & Emulator Infrastructure

* **Build System**: Strictly **GNU Make**. PRs attempting to fully transition to other build systems (CMake, Meson, Ninja, etc.) will be systematically ignored. Anyone is free however to add other configurations in addition to GNU Make but just be aware that if you do, you are responsible for the whole process from building, testing, deploying, and maintaining. I will not assist you.

* **Emulator Targets**: Initial support is strictly focused on **QEMU**. Roadmap plans include expanding testing frameworks to natively target **Bochs** and **VirtualBox** down the line. Any others will not be supported so if you use them and have issues, I will not assist you and the PR/Issue will be automatically closed. You are however, free to add additional targets but if you choose to do that, you will be solely responsible for building, testing, deploying, and maintaining that support. I will not assist you.

### Building & Emulation Mockup
**Note**: this what is here right now is just a placeholder. i will add real instructions once the building process has started.
```bash
# Clone the public milestone mirror
git clone https://github.com/jewboi896-cmyk/StrataOS-public
cd StrataOS

# Compile using specific algorithmic flags (Example)
make VMM_ALGO=buddy_allocator iso

# Boot inside the QEMU environment
make run
```

---
