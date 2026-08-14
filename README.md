# StrataOS-public

# Intro
this is a monolithic style custom OS targeting x86_64 built for myself as well as an educational tool to help beginners understand OS concepts. It uses the Limine Bootloader. It will have two sets of documentation: 1.) auto generated API and standard library docs using external tools that scrape the method signatures and compiles complete documentation and 2.) custom made docs geared towards beginners that explain the "why" behind OS concepts. This is planned to be the following: each system/subsystem can be configured to use between 3-5 different implementations of each system/subsystem that can be swapped either via flags passed in via the terminal or you can edit the master Makefile directly. the algorithms will range from as simple as possible to full production level stack. Each system/subsystem will have their own Makefiles that exist to tell the master Makefile how to tell the linker script how to stitch together the final binary. it also exists to keep the preprocessor stuff out of the actual code files and header files (for the applicable languages).

# Lang Stack
Core kernel systems/subsystems: pure C

Drivers and non-core systems/subsystems: mix of possible languages include: C, C++, C3, Rust, Zig and/or Odin

I also want to implement my own simple network stack with drivers either in: C, C++, or C3. Interactivity through a Go wrapper

# Virtual Machine/Emulator Support
Initial support will be limited to only QEMU for now. Plans exist to add support for both Bochs and VirtualBox emulators in the future


# Build System
The build system will be GNU Make. If you use a different build system because you prefer it over GNU, do not open any PRs regarding support for other build systems as i will just ignore them.

# PR Policy
Anyone can open PRs at any time but as this is a solo project, it may be years before i start reviewing any PRs. If you want to contribute to this repo early on in the dev process, keep the commits/PRs focused on the kernel code and not userspace until userspace has been scaffolded by me so that you can mirror my process.

# AI Policy
You can use AI to write code for any part of this project but you must make it known that the code is AI generated. The PR must be tagged with ai-generated. See the labels section for more info. If you use AI for writing anything other than build system scripts or other config stuff, i will probably ignore it as i am responsible for this repo's code and the legality of who owns AI generated code is still a gray area.

# Current Considerations for Viewers/Contributors
This project is in the very early planning stages and thus will not have any code written for it for a few years. im still in college and want to spend my time job/internship prepping. if you come across this repo early on in the dev process, this is why there is not much activity. This is also only the public facing repo, not my private repo for daily work. This will only get updated after certain milestones gets passed.

# Other Possible Additions
A custom GUI installer. Possible video streaming platform as a opt-in userspace app. These are just possible ideas for userspace apps.
