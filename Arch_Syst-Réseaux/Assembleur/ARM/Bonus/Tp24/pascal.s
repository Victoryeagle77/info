/*
n -> r1
m -> r2
x -> r3
z -> r4
*/

/*
On push/pop r1,r2,r3,lr
*/

.arm
.data
.text
.global _start
_start:

binome:
	push {r1,r2,r3,lr}
	cmp r1,#0
	beq Out
	cmp r1,r2
	beq Out
	
	sub r2,r2,#1
	sub r1,r1,#1
	
	bl binome
	mov r3,r4
	add r2,r2,#1

	bl binome
	add r4,r4,r3
	b Fin

Out:
	mov r4,#1

Fin:
	pop {r2,r3,r4,pc}

start:
	mov r1,#3
	mov r2,#7
	bl binome
	mov r4,r0
	mov r7,#1
	swi 0
.end
