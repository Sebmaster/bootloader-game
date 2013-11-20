.model TINY
.586

extrn _KMain:near
extrn _KeyboardInterrupt:near
extrn _TimerInterrupt:near

.code
	org 7C00h

_main:
	cli
	mov AX, CS
	mov ES, AX
	
	mov [es:(4 * 8)], TimerInterrupt
	mov [es:(4 * 8 + 2)], CS

	mov [es:(4 * 9)], KeyboardInterrupt
	mov [es:(4 * 9 + 2)], CS
	sti

	call _KMain

	jmp $

TimerInterrupt proc near
	call _TimerInterrupt

	mov AL, 20h
	out 20h, AL
	iret
TimerInterrupt ENDP

KeyboardInterrupt proc near
	in AL, 60h

	push AX
	call _KeyboardInterrupt
	pop AX

	mov AL, 20h
	out 20h, AL
	iret
KeyboardInterrupt ENDP

END _main
