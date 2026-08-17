<div align="center">
  <!-- Optional Project Banner -->
  <!-- <img src="docs/strata_logo.png" alt="StrataOS Logo" width="250"/> -->

  # 🌌 StrataOS

  **A monolithic-style custom x86_64 operating system designed as an educational platform with swappable algorithmic strata.**

  [![Architecture](https://shields.io)](#)
  [![Bootloader](https://shields.io)](#)
  [![Build-System](https://shields.io)](#)
  [![License](https://shields.io)](https://opensource.org)
  [![API-Docs](https://shields.io)](#)
  [![Beginner-Docs](https://shields.io)](#)
</div>

---

## 🏛 Project Overview & Philosophy

**StrataOS** is a monolithic-style custom operating system targeting the `x86_64` architecture, booting via the **Limine Bootloader**. It serves two primary purposes: a personal engineering sandbox and a highly structured educational tool built to help beginners master low-level concepts.

### 🔄 The Swappable Strata System
Unlike static hobbyist kernels, every core system and subsystem in StrataOS can be configured to use between **3 to 5 different algorithmic implementations**.

* **The Spectrum**: Implementations range from dead-simple (educational/naive) to full production-level stacks.

* **No Code Bloat**: Swapping algorithms is handled entirely through configuration flags passed via the terminal or by editing the master `Makefile` directly. This ensures that there is no need to use complex vtable stuff to swap things out at runtime.

* **Decoupled Architecture**: Individual subsystem Makefiles instruct the master build system how to pipe configuration to the linker script, dynamically stitching together the final binary. This cleanly isolates preprocessor macros entirely outside the primary source files and headers.

---

## 🔬 Language & Subsystem Matrix

| Stratum / Layer | Language | Architectural Purpose |
| :--- | :---: | :--- |
| **Core Kernel** | `Pure C` | Core executive, MMU, scheduling, and foundational stubs. |
| **Drivers & Non-Core** | `Polyglot` | Modular extensions written in C, C++, C3, Rust, Zig, and/or Odin. |
| **Network Stack** | `C / C++ / C3` | Custom custom-built network stack running native drivers. |
| **Interactivity Layer** | `Go` | Handled seamlessly via a dedicated Go runtime wrapper. |

**Note**: I'm planning on creating my own custom system call numbers and such. This means that no app can natively run on this without code modification. This is a deliberate decision and I understand the implications. As such, all of the user-space stuff will be quite extensive and cover a wide range of projects so as to reduce the dependence on needing to rewrite existing systems to comply with my syscall mappings. This will be opt-out at build time so if you opt-out, I hope you know what you are getting yourself into. I am planning on writing a custom intercept and mapping layer eventually so that apps don't need to be rewritten but until that point in time comes, you are on your own for this stuff. Thank you for your understanding.

---

## 📚 Dual-Track Documentation Blueprint

To maximize educational utility, the project generates and maintains two distinct documentation tracks:
1. **Auto-Generated API Reference**: External automated tools scrape code signature definitions to compile complete, strict standard library documentation.

2. **Conceptual "Why" Documentation**: Custom-authored guides tailored specifically for beginners, detailing the exact logic and system design tradeoffs behind low-level OS concepts.

---

## 🏗 Build & Emulator Infrastructure

* **Build System**: Strictly **GNU Make**. PRs attempting to transition to other build systems (CMake, Meson, Ninja, etc.) will be systematically ignored. You are free to add other configurations but just be aware that if you do, you are responsible for the whole process from building to testing to deploying. I will not assist you.

* **Emulator Targets**: Initial support is strictly focused on **QEMU**. Roadmap plans include expanding testing frameworks to natively target **Bochs** and **VirtualBox** down the line.

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

## ⚠️ Repository Status Notice (Read Before Viewing)

> **Important**: This project is in its early architectural planning phases. 
> 
> I (the only dev) is currently in college focusing heavily on career and internship preparation. Consequently, active logic commits may not begin for a few years at the earliest. 
> 
> Additionally, **this repository is a public mirror** meant for tracking stable milestones. Daily active development occurs entirely inside a private workspace and will be pushed here only when major checkpoints are cleared. Nobody is permitted to use the private repo at any time unless I specifically give you access/permission to do so.

---

## 🤝 Contribution & Pull Request Policy

Contributions are welcome, but given the solo nature of the project, please respect the following operational guidelines:

* **Review Latency**: Pull requests may sit unreviewed for extended periods (potentially years) during early infrastructure phases.

* **Scope Isolation**: Keep early PRs tightly focused on core **kernel-space code**. Do not touch user space until the foundation has been formally scaffolded by me (the sole maintainer and dev). If you have user-space app ideas please open up a thread under the Discussions tab and I will get back to you on your idea as soon as I can.

* **Strict Build Consistency**: Do not submit PRs changing the core GNU Make structure unless you see that I have made a mistake somewhere or you see that a optimization can be made to improve build times, have a smaller final binary size, etc. You are also free to edit the linker for the same reasons as well. If you do so just open a PR and I will get back to you whenever I can.

* **Discussions**: If you have other ideas for user-space apps, please submit something in the discussions tab and tag me in it so that when I have time, I can take a look at it. Please keep this only regarding user-space stuff. If you spot a kernel bug or issue please open either a PR for bugs or a Issue for issues and I will take a look.

* **Contributions**: Anybody can become a contributor regardless of number of commits or activity. Anybody is also free to reach out directly to me in the event that they want to become part of the core dev team. My email is: derekh789@icloud.com. There will be no required time commitment for any potential core dev team members, you can build, test, and review anything at your own pace.

* **Note**: For consistency throughout this project, everything should use **camelCase** simply because this is my OS and thus you must adhere to my preferences. This is built first for me and secondly for the general community and this keeps everything uniform. Also, starting brackets for functions start at the end of the function **not** on the next line. Same reasoning as above. Any PRs not following these guidelines will be auto-rejected and I will leave a comment mentioning this. You are then free to submit another PR for the same issue/bug if it follows these conventions.

---

## 🤖 AI Usage & Legality Policy

AI tools may be leveraged to accelerate development, provided they align with the following compliance parameters:

* **Mandatory Disclosure**: Any code generated via AI must be clearly declared in the PR description. The PR must be tagged with the `ai-generated` label. See the PR section and find the labels section on the top of the page for more info. You are free to add other/new labels as needed granted you open a Discussion with me and I approve it.

* **Core Logic Restrictions**: AI assistance should be confined to build system configurations, automation scripts, and administrative templates. Contributions containing AI-generated kernel logic or core runtime systems will most likely be ignored due to intellectual property gray areas.

* **Internal Alignment**: I personally restrict internal AI usage to generating Markdown documentation, tracking design decisions, and scripting build structures. No actual kernel or system logic code is AI-written by me.

---

## 🗺 Future Userspace Concept Roadmap

While deep in kernel planning, future opt-in user-space components are tracking the following targets:
- [ ] Statically compiled custom user runtime environment
- [ ] Native Graphical User Interface (GUI) system installer
- [ ] Dedicated video streaming platform integrated directly as a native user-space app
- [ ] Custom CLI tool as a user-space app -this will be done by me as i have custom ideas for this
- [ ] Music Streaming Platform as a user-space app
- [ ] Web Browser as a user-space app

If you have any other ideas, please open up a Discussion thread and we can talk it over. Once its approved, add it to this list above and you are free to start working on whatever it is. Once something on this list is confirmed to be done, mark it like this: (Done) at the end of the entry.

---

## 📜 License

Distributed under the **Apache License 2.0**. See the `LICENSE` file for more details. Everything from the core kernel space to the multi-language driver strata is open for modification, distribution, and commercial use under these terms.

