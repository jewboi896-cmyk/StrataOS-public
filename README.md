<div align="center">
  <!-- Optional Project Banner -->
  <!-- <img src="docs/strata_logo.png" alt="StrataOS Logo" width="250"/> -->

  # 🌌 StrataOS

  **A monolithic-style custom x86_64 operating system designed as an educational platform with swappable algorithmic strata.**

  [![Architecture](https://shields.io)](#)
  [![Bootloader](https://shields.io)](#)
  [![Build-System](https://shields.io)](#)
  [![License](https://shields.io)](#)
  [![API-Docs](https://shields.io)](#)
  [![Beginner-Docs](https://shields.io)](#)
</div>

---

**Note**: At this stage, all of the above links are strictly placeholders and do not link to anything. This will change in the future as things actually get built for real.

## 🏛 Project Overview & Philosophy

**StrataOS** is a monolithic-style custom operating system targeting the `x86_64` architecture, booting via the **Limine Bootloader**. It serves two primary purposes: a personal engineering sandbox and a highly structured educational tool built to help beginners master low-level concepts.

### 🔄 The Swappable Strata System
Unlike static hobbyist kernels, every core system and subsystem in StrataOS can be configured to use between **3 to 5 different algorithmic implementations**.

* **The Spectrum**: Implementations range from dead-simple (educational/naive) to full production-level stacks. This means that each system/subsystem will have multiple different implementations just with different algorithms.

* **No Code Bloat**: Swapping algorithms is handled entirely through configuration flags passed via the terminal or by editing the master `Makefile` directly. This ensures that there is no need to use complex vtable stuff to swap things out at runtime.

* **Decoupled Architecture**: Individual subsystem Makefiles instruct the master build system how to pipe configuration to the linker script, dynamically stitching together the final binary. This cleanly isolates preprocessor macros entirely outside the primary source files and headers. Note that because of this, the config files will get long, complex, and hard to read. This is a deliberate choice. I'd rather have this kind of stuff isolated from the actual logic than embedded inside of it. 

---

## 🔬 Language & Subsystem Matrix

| Stratum / Layer | Language | Architectural Purpose |
| :--- | :---: | :--- |
| **Core Kernel** | `Pure C` | Core executive, MMU, scheduling, and foundational stubs. |
| **Drivers & Non-Core** | `Polyglot` | Modular extensions written in C, C++, C3, Rust, Zig, and/or Odin. |
| **Network Stack** | `C / C++ / C3` | Custom-built network stack running native drivers. |
| **Interactivity Layer** | `Go` | Handled seamlessly via a dedicated Go runtime wrapper. |

## ⚠️ Custom System Call & Existing Binary Compatibility
> I'm planning on creating my own custom system call numbers and such. This means that no app can natively run on this without code modification. This is a deliberate decision and I understand the implications.
> As such, all of the user-space stuff will be quite extensive and cover a wide range of projects so as to reduce the dependence on needing to rewrite existing systems to comply with my syscall mappings.
> I am planning on writing a custom intercept and mapping layer eventually so that apps don't need to be rewritten but until that point in time comes, you are on your own for this stuff. Thank you for your understanding.

---

## 📚 Dual-Track Documentation Blueprint

To maximize educational utility, the project generates and maintains two distinct documentation tracks:
1. **Auto-Generated API Reference**: External automated tools scrape code signature definitions to compile complete, strict standard library documentation.

2. **Conceptual "Why" Documentation**: Custom-authored guides tailored specifically for beginners, detailing the exact logic and system design tradeoffs behind low-level OS concepts. 

**Note**: These tools and docs will not be part of the final binary but they will be linked to in this README file as external sites. This decision could change but for now, this is what's gonna happen. Thanks for your understanding.

---

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

## ⚠️ Repository Status Notice (Read Before Viewing)

> **Important**: This project is in its early architectural planning phases. 
> 
> I (the only dev) am currently in college focusing heavily on career and internship preparation. I graduate in 2029. Consequently, active logic commits will not begin for a few years at the earliest and none before 2029. Do not open PRs or Issues at this time. Discussions are welcome. Thank you for your understanding. 
> 
> Additionally, **this repository is a public mirror** meant for tracking stable milestones. Daily active development occurs entirely inside a private workspace and will be pushed here only when major checkpoints are cleared. Nobody is permitted to use the private repo at any time unless I specifically give you access/permission to do so (as in you want to be a part of the core dev team).

---

## 🤝 Contribution & Pull Request Policy

Contributions are welcome, but given the solo nature of the project, please respect the following operational guidelines:

* **Review Latency**: Pull requests may sit unreviewed for extended periods (potentially years) during early infrastructure phases.

* **Scope Isolation**: Keep early PRs tightly focused on core **kernel-space code**. Do not touch user space until the foundation has been formally scaffolded by me (the sole maintainer and dev). If you have user-space app ideas please open up a thread under the Discussions tab and I will get back to you on your idea as soon as I can.

* **Strict Build Consistency**: Do not submit PRs changing the core GNU Make structure unless you see that I have made a mistake somewhere or you see that a optimization can be made to improve build times, have a smaller final binary size, etc. You are also free to edit the linker for the same reasons as well. If you do so just open a PR and I will get back to you whenever I can.

* **Discussions**: If you have other ideas for user-space apps, please submit something in the discussions tab and tag me in it so that when I have time, I can take a look at it. Please keep this only regarding user-space stuff. If you spot a kernel bug or issue please open either a PR for bugs or a Issue for issues and I will take a look.

* **Contributions**: Anybody can become a contributor regardless of number of commits or activity. Anybody is also free to reach out directly to me in the event that they want to become part of the core dev team. If you want to contact me privately, open an issue on my main page and I will get back to you as soon as I can. There will be no required time commitment for any potential core dev team members, you can build, test, and review anything at your own pace.

* **Style & Formatting Rules**:
  * **Functions & Variables**: `camelCase`
  * **Types (Structs, Enums, Unions, Typedefs)**: `PascalCase`
  * **Brace Style**: Opening brackets `{` must be placed on the **same line** as the function declaration/header, not on a new line.
  * **Naming**: Almost always use **descriptive variable names**. Limit single-letter variables strictly to loop counters or math formulas to maintain readability for educational purposes.

Any PRs submitted that do not follow this style guide will be automatically rejected and I will leave a comment directing you to the style guidelines.

---

## 🤖 AI Usage & Legality Policy

AI tools may be leveraged to accelerate development, provided they align with the following compliance parameters:

* **Mandatory Disclosure**: Any code generated via AI must be clearly declared in the PR description. The PR must be tagged with the `ai-generated` label. See the PR section and find the labels section on the top of the page for more info. You are free to add other/new labels as needed granted you open a Discussion with me and I approve it.

* **Core Logic Restrictions**: AI assistance should be confined to build system configurations, automation scripts, and administrative templates. Contributions containing AI-generated kernel logic, core runtime systems (ie, drivers and such) or user-space apps will most likely be ignored due to current intellectual property gray areas.

* **Internal Alignment**: I personally restrict internal AI usage to generating Markdown documentation, tracking design decisions, and scripting build structures. No actual kernel, system logic, or driver code is AI-generated by me.

Failure to comply with the AI guidelines will result in a ban from the ability to contribute anymore. I am not gonna be responsible for your laziness when it comes to anything other than the above exceptions. 

---

## 🗺 Future User-space Concept Roadmap

While deep in kernel planning, future opt-in user-space components are tracking the following targets:
- [ ] Statically compiled custom user runtime environment
- [ ] Native Graphical User Interface (GUI) system installer
- [ ] Dedicated video streaming platform integrated directly as a native user-space app - like a Youtube esc app
- [ ] Custom CLI tool as a user-space app - this will be done by me as i have custom ideas for this
- [ ] Music Streaming Platform as a user-space app - like a Spotify esc app
- [ ] Web Browser as a user-space app - like a Brave Browser esc app
- [ ] Fully compliant network stack - this must be built before the browser and right now, the scope is extremely simple
- [ ] File Explorer esc app using the custom Rust filesystem
- [ ] Security Monitor - like a Windows Security esc app
- [ ] Resource Monitor - like a Task Manager esc app

If you have any other ideas, please open up a Discussion thread inside of the Ideas section and we can talk it over. Once its approved, add it to this list above and you are free to start working on whatever it is. Once something on this list is confirmed to be done, mark it like this: (Done) at the end of the entry and edit the appropriate entry via this doc to add a checkmark so that everyone else knows as well.

---

## 🐳 Reproducibility & Containerization
I am planning on using Docker eventually but until then, the languages standards at the moment will be the following (I will update these as newer stable standards come out until development starts at which point, these toolchains will become locked for a time.):

| Language | Current Stable Version (2026) | Notes |
| :--- | :---: | :--- |
| C | C23 | None |
| Rust | 1.97.1 | None |
| C++ | C++23 | None |
| Zig | 0.16.0 | Will not be used until at least 1.0 release and confirmed solid freestanding support |
| Odin | dev-2026-08 | Same as Zig above |
| C3 | 0.8.3 | Same as both Zig and Odin |

Anyone is free to open PRs expanding the containerization infrastructure but just like adding another build system, you will be solely responsible for building, testing, deploying, and maintaining it. I will not help you.

---

## 🦊 GitLab Notice (Read first if viewing in GitLab)

> Hello to everyone reading this on GitLab. Please note that the main contributions, issues, PRs, discussions and such are on Github. Also understand that the GitLab mirror could fall significantly behind every so often so I'd advise you to also check the GitHub page as well if you want frequent updates and changes.
>
> The GitLab is here for redundancy mostly. You are still free to open PRs or Issues and such just know that I will not be regularly checking on them so its best if you came to the GitHub page instead. Once a style guide is posted on GitHub, I will also post it on GitLab and all PRs must adhere to it. Thanks for your understanding.

---

## 📜 License

Distributed under the **Apache License 2.0**. See the `LICENSE` file for more details. Everything from the core kernel space to the multi-language driver strata to any user-space apps is open for modification, distribution, and commercial use under these terms.

