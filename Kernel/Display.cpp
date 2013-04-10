#include "Display.h"

void Display::initText() {
	__asm {
		mov AX, 03h;
		int 10h;
	} 
}

void Display::print(const char* printStr) {
	__asm {
		mov SI, printStr;
PrintString:
		lodsb;
		or AL, AL;
		jz exit;

		mov AH, 0Eh;
		xor BH, BH;
		mov BL, 7h;

		int 10h;
		jmp PrintString;
	}
exit:
	return;
}

void Display::setChar(char x, char y, char chr, char col) {
	short adr = 0xB800;
	short offsetPtr = (y * 80 + x) * 2;

	__asm {
		mov DX, adr;
		mov ES, DX;
		mov AL, chr;
		mov AH, col;
		mov BX, offsetPtr;
		mov word ptr ES:[BX], AX;
	} 
}

void Display::disableCursor() {
	__asm {
		mov CX, 2000h;
		mov AH, 01h;
		int 10h;
	}
}