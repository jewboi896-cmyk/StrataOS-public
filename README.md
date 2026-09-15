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

**Note**: At this stage, all of the above links are strictly placeholders and do not link to anything. This will change in the future as things actually get built for real. Also note that a CI using Actions is planned for the future.

## 🏛 Project Overview & Philosophy

**StrataOS** is a monolithic-style custom operating system targeting the `x86_64` architecture, booting via the **Limine Bootloader**. It serves two primary purposes: a personal engineering sandbox and a highly structured educational tool built to help beginners master low-level concepts.

### 🔄 The Swappable Strata System
Unlike static hobbyist kernels, every core system and subsystem in StrataOS can be configured to use between **3 to 5 different algorithmic implementations**.

* **The Spectrum**: Implementations range from dead-simple (educational/naive) to full production-level stacks. This means that each system/subsystem will have multiple different implementations just with different algorithms.

* **No Code Bloat**: Swapping algorithms is handled entirely through configuration flags passed via the terminal or by editing the master `Makefile` directly. This ensures that there is no need to use complex vtable stuff to swap things out at runtime.

* **Decoupled Architecture**: Individual subsystem Makefiles instruct the master build system how to pipe configuration to the linker script, dynamically stitching together the final binary. This cleanly isolates preprocessor macros entirely outside the primary source files and headers. Note that because of this, the config files will get long, complex, and hard to read. This is a deliberate choice. I'd rather have this kind of stuff isolated from the actual logic than embedded inside of it. 

---

## 🔬 Language & Subsystem Matrix

See [LANGUAGE.md](https://github.com/jewboi896-cmyk/StrataOS-public/blob/main/LANGUAGE.md) for more info

---

## 📚 Dual-Track Documentation Blueprint

See [DOCS.md](https://github.com/jewboi896-cmyk/StrataOS-public/blob/main/DOCS.md) for more info.

---

## 🏗 Build & Emulator Infrastructure

See [BUILD.md](https://github.com/jewboi896-cmyk/StrataOS-public/blob/main/BUILD.md) for more info.

## ⚠️ Repository Status Notice (Read Before Viewing)

> **Important**: This project is in its early architectural planning phases. 
> 
> I (the only dev) am currently in college focusing heavily on career and internship preparation. I graduate in 2029. Consequently, active logic commits will not begin for a few years at the earliest and none before 2029. Do not open PRs or Issues at this time. Discussions are welcome. Thank you for your understanding. 
> 
> Additionally, **this repository is a public mirror** meant for tracking stable milestones. Daily active development occurs entirely inside a private workspace and will be pushed here only when major checkpoints are cleared. Nobody is permitted to use the private repo at any time unless I specifically give you access/permission to do so (as in you want to be a part of the core dev team).
>
> Please note that if you want to be apart of the core dev team, you need to be able to commit to this project long term. This is not to say that this must be the only open source thing that you do but just be aware that this is the only expectation. Im expecting development to take at least 2-3 decades, probably more. 

---

## 🤝 Contribution & Pull Request Policy

See [CONTRIBUTING-PR.md](https://github.com/jewboi896-cmyk/StrataOS-public/blob/main/CONTRIBUTING-PR.md) for more info.

---

## 💼 Style Guide Policy

See [STYLE.md](https://github.com/jewboi896-cmyk/StrataOS-public/blob/main/STYLE.md) for more info.

---

## 🤖 AI Usage & Legality Policy

See [AI.md](https://github.com/jewboi896-cmyk/StrataOS-public/blob/main/AI.md) for more info.

---

## ♾️ CI Pipeline Using Github Actions (Planned)

| Language | Setup Notes | Miscellaneous | 
| :--- | :---: | :--- |
| C/C++ | Setup C/C++ core automations |
| Rust | Setup Rust filesystem automations |
| Zig | Setup Zig automations |
| Odin | Setup Odin automations |
| Go | Setup Go automations |
|    |                      | Style Guide PR policy |
|    |                      | General Typo and Grammar Checks |
|    |                      | General Emulator, Build Scripts & Config |

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
| C | C23 | Core kernel systems/subsystems, drivers, networking, etc |
| Rust | 1.97.1 | Filesystem, drivers, certain CLI tools, etc |
| C++ | C++23 | drivers, networking, etc |
| Zig | 0.16.0 | Will not be used until at least 1.0 release and confirmed solid freestanding support |
| Odin | dev-2026-08 | Same as Zig above |
| C3 | 0.8.3 | Same as both Zig and Odin |
| Go | 1.27.0 | Networking middleman, user-space apps, etc |

Anyone is free to open PRs expanding the containerization infrastructure but just like adding another build system, you will be solely responsible for building, testing, deploying, and maintaining it. I will not help you.

**Golang Note**: Go will be used as the middleman for the network stack. It will sit on top of the kernel network drivers but under the user-space apps that call the network drivers. This is the only place where Go will be used in this capacity. It will live in user-space. Any user-space apps are free to use whatever language the creator wants. The above languages (excluding Go for the reasons above) will be used for the kernel space mostly.

**Zig, Odin, C3 Note**: If these languages are added to the stack, they will be kernel space driver(s) and user space stuff only as C, C++, and Rust will do most of the heavy lifting.

---

## 🦊 GitLab Notice (Read first if viewing in GitLab)

> Hello to everyone reading this on GitLab. Please note that the main contributions, issues, PRs, discussions and such are on Github. Also understand that the GitLab mirror could fall significantly behind every so often so I'd advise you to also check the GitHub page as well if you want frequent updates and changes.
>
> The GitLab is here for redundancy mostly. You are still free to open PRs or Issues and such just know that I will not be regularly checking on them so its best if you came to the GitHub page instead. Once a style guide is posted on GitHub, I will also post it on GitLab and all PRs must adhere to it. Thanks for your understanding.

---

## 📜 License

Distributed under the **Apache License 2.0**. See the `LICENSE` file for more details. Everything from the core kernel space to the multi-language driver strata to any user-space apps is open for modification, distribution, and commercial use under these terms.

