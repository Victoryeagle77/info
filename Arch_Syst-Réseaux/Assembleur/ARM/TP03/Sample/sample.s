/* Question 1 : sample

Il s'agit d'un assemblage multiple, avec pluiseurs fichiers, on assemblera et compliera donc ainsi :
"as -gstabs -o sprintf.o sprintfd.s"
"as -gstabs -o sample.o sample.s"
"ld -O0 sample.o sprintfd.o"
*/

.equ SYS_EXIT, 1
.equ SYS_READ, 3
.equ SYS_WRITE, 4

.arm
.data

int1: .word 0
strfin:	.asciz "\n" @ Saut de ligne après affichage du résultat
@ On réserve un espace suffisant pour écrire la chaine
str: .space 256 

	.text
	.globl _start

_start:
	@ Chargement des valeurs dans les registres
    ldr r3, =int1 
	ldr r2, [r3]   
		
	/* On appellera le fichier sprintfd. On prépare les arguents dans r0,r1.
	L'adresse de l'alocation en mémoire doit être dans r0. */
	
	ldr r0, =str

	@ La valeur à convertir doit se trouver dans r1
	mov r1, r2 

	@ Appel de la fonction
	bl sprintfd  

	/* Adresse du string doit être disposé dan r0 et sa longeur dans r1.
	On prépare les registre pour SYS_WRITE: */

	mov r2, r1
	mov r1, r0
	/* Equivalent de printf("%d"...) */
	mov r7, #SYS_WRITE
	mov r0, #1
	swi #0 
	/* Equivalent de printf("\n") */
	mov r7, #SYS_WRITE
	mov r0, #1
	ldr r1, =strfin
	mov r2, #1
    swi #0

    b sortie

sortie:   
	mov r7, #SYS_EXIT
	mov r0, #0
	swi #0

.end
