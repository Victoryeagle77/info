.arm
.data

	infile: .asciz "args.dat"
	outfile: .asciz "rsltat.dat"
	a: .word 0
	b: .word 0
	r: .word 0
	err: .word 0xfffffffe

.text
.global _start

start:
	ldr r0,=infile
	mov r1,#0
	mov r2,#0x1a4
	mov r7,#5
	swi 0

	ldr r1,=err
	ldr r2,[r1]
	cmp r0,r1
	beq Err

	mov r4,r0

	ldr r1,=a
	mov r2,#4
	mov r7,#3
	swi 0

	mov r0,r4
	ldr r1,=b
	swi 0

	ldr r1,=a
	ldr r2,[r1]
	ldr r1,=b
	ldr r3,[r1]
	add r0,r2,r3
	ldr r1,=r
	str r0,[r1]

	ldr r0,=outfile
	ldr r1,#0x241
	mov r2,#0x1a4
	mov r7,#5
	swi 0

	ldr r1,=err
	ldr r2,[r1]
	cmp r0,r1
	beq Err

	ldr r1,=r
	mov r2,#4
	mov r7,#4
	swi 0

Err:
	mov r7,#1
	swi 0

.end
