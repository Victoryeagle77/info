.arm
.text
.global _start

fact:
	push {r1,lr}
	cmp r1,#0
	beq L
	sub r1,r1,#1
	bl fact

	add r1,r1,#1
	mul r2,r1,r2

Out:
	pop {r1,pc}

L:
	mov r2,#1
	b Out

_start:
	nop
	mov r1,#5
	bl fact
	mov r0,r2
	mov r7,#1
	swi #0

.end
