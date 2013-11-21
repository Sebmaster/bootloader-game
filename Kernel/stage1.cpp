#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

static struct {
	char size;
	char res;
	short transferSize;
	int dest;
	long source;
} LBAPacket = {0x10, 0, 0, 0, 0};


inline void PrintChar(char c) {
	__asm {
		mov AH, 0x0A;
		mov AL, c;
		mov CX, 1;
		int 0x10;
	}
}

inline char* ReadSector(int source, int size) {
	LBAPacket.source = source;
	LBAPacket.transferSize = size;

	__asm {
		mov SI, LBAPacket;
		mov AH, 0x42;
		mov DL, 0x80;
		int 0x13;
	}

	return (char*)0;
}

extern "C" void KMain() {
	
}
