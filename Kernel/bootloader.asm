.model TINY
.586

extrn _KMain:near

.code
	org 07C00h
	
_main:
	jmp short start
	nop

dosOEM		DB	'MSDOS5.0'
dosBPS		DW	512
dosSPC		DB	1
dosRES		DW	1
dosTBLs		DB	2
dosRENT		DW	0F0h
dosSECs		DW	2880
dosMED		DB	0F0h
dosSPF		DW	9
dosSPT		DW	18
dosHPC		DW	2
dosHS		DD	0
dosTSECs	DD	0

start:
	cli
	xor	ax, ax
	mov	ds, ax
	mov	ss, ax
	mov	sp, 07C00h
	mov	bp, sp

	call _KMain
	hlt
END _main
