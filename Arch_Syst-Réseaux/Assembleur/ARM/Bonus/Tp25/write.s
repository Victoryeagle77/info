.arm
.data
	prompt:	.asciz "Input File: "
	len = 	. - prompt
.global _start
_start:
	mov r1,#1
	ldr r3,=len
	mov r7,#4
	nop
	swi 0
	nop
	mov r7,#1
	swi 0
.end
