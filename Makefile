# This is the stub for the master Makefile

# This is gonna be the proposed structure:
# Each system gets its own Makefile as well as each subsystem. 
# Each subsystem's Makefile only talks to the system level Makefile
# Each system's Makefile only communicates with the Master Makefile (this file)
# This allows different drivers written in different languages to only need to worry about their own isolated files when it
# comes to building either the whole project or only rebuilding a system or subsystem
# I also want the build system to be aware so that if you only touch one thing or a few things, 
# it only rebuilds that one system or subsystem or the combined suite of changes instead of rebuilding the whole source tree
# from scratch each time 
