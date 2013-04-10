Game-Bootloader
===

This is a small bootloader which is/was trying to implement a snake clone in the 512 bytes of a bootloader.


What works
---

* handles keyboard interrupts
* moves in a fixed interval
* the snake has the ability to grow


What's missing?
---

The generated source file has 498 bytes.
The BIOS of a PC loads only the first 510 bytes of code into the RAM to execute, the last 2 bytes are AA 55 to indicate that the preceding bytes are, indeed, a bootloader.
It is therefore quite problematic to add the last missing features, which are:

* catch out-of-bounds errors
* generation of additional points for the snake to eat

It might make sense to increase the speed of movement and strip the code which adds the snake length and in turn add the code for the point generation.

How do I play?
---

Easy!
* download an already built package from the "builds" branch
* install [Bochs](http://bochs.sourceforge.net/)
* load the bochsrc.bxrc file in Bochs
* "play"


How do I build it?
---

The build process relies on quite old software.

* ml.exe, the MASM compiler of Microsoft (included in Visual Studio installations)
* dmc.exe, the C(++) compiler of [Digitalmars](http://www.digitalmars.com/download/freecompiler.html)
* link.exe, the 16-bit linker of Microsoft
* dd.exe for windows from [chrysocome.net](http://www.chrysocome.net/dd)

Either add them to your path or drop them into the kernel directory, open the project in Visual Studio and run (F5; bochs path fixed for v2.6.1).