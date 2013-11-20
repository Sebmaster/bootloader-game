#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

struct Node {
	char x;
	char y;
	Node* next;
};

void* currMemory = (void*)0x9000;
bool moveFirst = true;

char nextMovement = 0x4D;

Node* firstNode = NULL;
Node* lastNode = NULL;

void setChar(char x, char y, char chr) {
	short offsetPtr = (y * 80 + x) * 2;

#ifdef ___MSC_VER
	__asm {
		mov DX, 0B800h; // 0xB800 in segment register => video ram
		mov ES, DX;
		mov AL, chr;
		mov AH, 5;
		mov BX, offsetPtr;
		mov word ptr ES:[BX], AX;
	}
#else
	asm("mov DX, 0x0B800\n"
	    "mov ES, DX\n"
	    "mov AL, %[chr]\n"
	    "mov AH, 5\n"
	    //"mov EBX, %[offsetPtr]\n"
	    //"mov ES:[EBX], AX\n" 
	    :
	    : [chr]"r"(chr), [offsetPtr]"r"(offsetPtr)
	);
#endif
}

Node* CreatePoint(char x, char y) {
	Node* n = (Node*)currMemory;
	currMemory = (void*)((char*)currMemory + sizeof(Node));
	n->x = x;
	n->y = y;
	n->next = NULL;
	return n;
}

void MovePlayerPosition(char deltaX, char deltaY) {
	if (moveFirst) {
		setChar(firstNode->x, firstNode->y, ' ');
		firstNode->x = lastNode->x + deltaX;
		firstNode->y = lastNode->y + deltaY;
		lastNode = firstNode;

		if (firstNode->next != NULL) {
			firstNode = firstNode->next;
		}
		setChar(firstNode->x, firstNode->y, 'X');
	} else {
		Node* n = CreatePoint(lastNode->x + deltaX, lastNode->y + deltaY);
		lastNode->next = n;
		lastNode = n;
		setChar(lastNode->x, lastNode->y, 'X');
	}

	moveFirst = true;
}

extern "C" void _KMain() {
#ifdef ___MSC_VER
	__asm {
		mov AX, 03h;
		int 10h;

		mov CX, 2000h;
		mov AX, 256;
		int 10h;
	}
#else
	asm ("mov AX, 0x03\n"
	     "int 0x10\n"
	     "mov CX, 0x02000\n"
	     "mov AX, 256\n"
	     "int 0x10\n");
#endif

	firstNode = CreatePoint(0, 0);
	lastNode = firstNode;
	setChar(0, 0, 'X');
}

short restFreq = 0;
extern "C" void _TimerInterrupt() {
	if (restFreq != 0) {
		--restFreq;
		return;
	} else {
		restFreq = 300;
	}

	switch (nextMovement) {
	case 0x48: // Up
		MovePlayerPosition(0, -1);
		break;
	case 0x4B: // Left
		MovePlayerPosition(-1, 0);
		break;
	case 0x50: // Down
		MovePlayerPosition(0, +1);
		break;
	case 0x4D: // Right
		MovePlayerPosition(+1, 0);
		break;
	}
}

extern "C" void _KeyboardInterrupt(short key) {
	if (key & 128) return;

	switch (key & 127) {
	case 0x48: // Up
	case 0x4B: // Left
	case 0x50: // Down
	case 0x4D: // Right
		nextMovement = key;
		break;
	}
}
