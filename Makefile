.phony: all

all: bios

folders:
	mkdir -p Kernel/Linux

bios: folders
	jwasm -Zne -q -elf -c -Fw"Kernel/Linux/bootloader.asm.err" -Fo"Kernel/Linux/bootloader.obj" "Kernel/bootloader.asm"
	g++ -m32 -nostdlib -masm=intel -s -Os -ffreestanding -Wall -Wextra -fno-exceptions -fno-rtti -o Kernel/Linux/floppy.img Kernel/stage1.cpp Kernel/Linux/bootloader.obj -T linker.ld
