/* r2=n r3=m r4=a r5=r args=r2,r3 res=r5*/

	.arm
	.data
infile:	.asciz "ints.dat"
outfile:.asciz "res.dat"
a:	.word 0
b:	.word 0
r:	.word 0
err:	.word 0xfffffffe
	.text
	.globl _start

binom:	
	push {r2,r3,r4,lr}
	cmp r2,#0
	beq Return_1
	cmp r2,r3
	beq Return_1
	subs r2,r2,#1
	subs r3,r3,#1
	bl binom
	mov r4,r5
	add r3,r3,#1
	bl binom
	add r5,r5,r4
	b Out

Return_1:
	mov r5,#1
	b Out
Out:	
	pop {r2,r3,r4,pc}


_start:	
	/* open args.dat */
	ldr r0,=infile
	mov r1,#0
	mov r2,#0x1a4
	mov r7,#5
	swi 0x0

	/* verif resultat open dans r0 */
	ldr r2,=err
	ldr r8,[r2]
	cmp r0,r8
	beq Err

	/* sauvegarde descripteur de fichier */
	mov r4,r0

	/* read args.dat twice */
	ldr r1,=a
	mov r2,#4
	mov r7,#3
	swi 0x0
	mov r0,r4
	ldr r1,=b
	swi 0x0

	/* charge a et b dans les registres et fais l'appel de fonction*/
	ldr r1,=a
	ldr r2,[r1]
	ldr r1,=b
	ldr r3,[r1]
	bl binom
	ldr r1,=r
	str r5,[r1]

	/* open res.dat */
	ldr r0,=outfile
	ldr r1,=0x241
	mov r2,#0x1a4
	mov r7,#5
	swi 0x0

	/* verif */
	cmp r0,r8
	beq Err

	/* write */
	ldr r1,=r
	mov r2,#4
	mov r7,#4
	swi 0x0
Err:	mov r7,#1
	mov r0,r5 /*res dans r0 pour avoir le retour*/
	swi 0x0
	.end
