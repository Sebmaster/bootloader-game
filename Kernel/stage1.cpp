#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

extern "C" void KMain() {
	__asm {
		mov	ah, 0h
		int	010h
	}
}
