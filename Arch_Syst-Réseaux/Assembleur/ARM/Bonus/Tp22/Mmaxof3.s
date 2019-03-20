#Nos tros variables seront stockees dans les registres r1,r2 r3. Le resultat sera stocke sur le registre r0.
#r4 servira de variable, et on stockera la variable de retour dans ce registre

.arm
.data

a: .word 53
b: .word 28
c: .word 45

.text
.global _start

min:
	push {lr}
	mov r4, r1
	cmp r2, r4
	movgt r4, r2
	cmp r3, r4
	movgt r4, r3
	pop {pc}

_start:
	ldr r0,=a
	ldr r1,[r0]
	ldr r0,=b
	ldr r2,[r0]
	ldr r0,=c
	ldr r3,[r0]
	bl min

	mov r7,#1
	mov r0, r4
	swi #0
.end
