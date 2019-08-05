/* Question 1 : max-array 
On écrit max-array.s dans lequel on réalise la fonction max qui prend en arguments, 
la taille et l’adresse d’un tableau d’entiers et en retourne la valeur maximale.
Dans le programme principal, on fait la saisie, par interaction avec l’utilisateur, des nouvelles valeurs 
(taille du tableau et valeurs dans le tableau), puis l’appel de la fonction. Pour parcourir le tableau, 
On utilisera le post-indexed addressing mode ou l’offset est une constante immediate. 
La taille et les entiers dans le tableau sont donn ́es dans la section .data */

.equ SYS_EXIT, 1
.equ SYS_WRITE, 4

.arm
.data

sz: .word 4
ary: .word -10,-43,-49,-50
strfin: .asciz "\n"
str: .space 256

.text
/* Partie traitant le maximum d'un tableau d'entier avec le post-indexed addressing mode
On utilise des registres spécifiques pour nos données suivantes:	
--> r0 = sz
--> r1 = ary
--> r2 = i
--> r3 = max
--> r4 = *ary
*/

max:
    /* Pousse les registres sur la pile pour leur réutilisation, 
    lr exécutant la prochaine instrcution */
    push {r2-r4,lr}
    mov r2, #0 /* Initialisation de i à 0 */
    /* Charge la valeur de la position 0 du tableau dans max */
    ldr r3, [r1]

boucle:
    /* if (i<taile) {continuation...} */
    cmp r2, r0
    beq return /* Sortie si i<=taille */
    /* Décalage de 4 (pour un int de 4 octet) vers la droite de r1, placé dans r1. */
    ldr r4, [r1], #4
    cmp r4, r3 /* if(tab[0] > maximum) */
    /* pl = Résultat positif ou nul, correspond à max = tab[i] */
    movpl r3, r4
    add r2, #1 /* i++ */
    b boucle

return:
    mov r0, r3 /* max dans r0 */
    /* Retire les registres empilé au sommet de la pile, 
    et programme counter pc exécute l'adresse de l'instruction de lr et la retourne,
    soit celles bl max */
    pop {r2-r4,pc}

.globl _start

/* Main */
_start:
    /* Taille et adresse du tableau */	
    ldr r3, =sz
    ldr r0, [r3]
    ldr r1, =ary 

    /* Appel de la fonction max */
    bl max
	
    mov r1, r0
    ldr r0, =str
	
    /* Appel de la fonction sprintfd */
    bl sprintfd
	
    /* Equivalent de printf("%d",...) */
    mov r2, r1 /* r2 = taille */
    mov r1, r0 /* r1 = chaine*/
    mov r0, #1
    /* write(1,chaine,taille) */
    mov r7, #SYS_WRITE
    swi #0

    /* Equvialent de printf("\n") */
    mov r0, #1
    ldr r1, =strfin
    mov r2, #1	
    mov r7, #SYS_WRITE
    swi #0

    /* EXIT SUCCESS */
    sortie:
	  mov r7, #SYS_EXIT
	  mov r0, #0
	  swi #0
.end
