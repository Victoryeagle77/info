/*
Question 2 ] Is-in-sorted
On ecrit is-in-sorted.s dans lequel on dispose de la fonction memb à qui on passe la valeur de x, 
la taille et l’adresse d’un tableau d’entiers. 
Elle retourne une positiondans le tableau ou se trouve la valeur de x, si x est un élément du tableau, 
et elle retourne -1 sinon.
*/

.equ EXIT_SUCCESS, 1
.equ EXIT_FAILURE, -1
.equ SYS_WRITE, 4

.arm
.data

sz: .word 4
ary: .word 1,5,7,8
x: .word 7
strfin:	.asciz "\n"
str: .space 256

.text
/* Partie memb chargée de trouvé l'indice correspondant à l'élément x 
(si présent dans le tableau, renvoie -1 sinon) 
--> r0 = ary
--> r1 = sz
--> r2 = x
--> r3 = i
--> r4 = *ary[i] correspondant à x
--> r5 = borne maximale du tableau
--> r6 = borne minimale du tableau
*/
memb:
  /* Pousse les registres sur la pile pour leur réutilisation, 
  lr exécutant la prochaine instrcution */
  push {r2, r3, r4, r5, r6, lr}
  /* Initialisation du minimum à 0 */
  mov r6, #0
  /* Le maximum est la taille */
  mov r5, r1

boucle:
  sub r3, r5, r6 /* i = max-min */
  /* Division par i par 1 afin que la position i soit considérer
  comme une valeur indépendante du tableau et soit incrémenté */
  add r3, r6, r3, lsr #1
  /* Multiplication par 2 de r3 et parcours du tableau */
  ldr r4, [r0, r3, lsl #2]
  cmp r2, r4 /* if(ary[i] == x) */
  moveq r0, r3
  /* Dépile en retirant de la pile si équivalence */
  popeq {r2, r3, r4, r5, r6, pc}
  
  movpl r6, r3
  movmi r5, r3 /* mi = Résultat négatif ou nul */

  teq r6, r5 /* if (min == max) */
  /* retrun -1 */
  moveq r0, #EXIT_FAILURE
  popeq {r2, r3, r4, r5, r6, pc}
  b boucle

.globl _start

_start:
    /* Elément x possiblement dans le tableau */
    ldr r1, =x
    ldr r2, [r1]
    ldr r0, =sz /* taille de tableau */
    ldr r1, [r0]
    ldr r0, =ary /* tableau */

    /* Appel de la fonction memb */
    bl memb
    
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
        mov r7, #EXIT_SUCCESS
        mov r0, #1
        swi #0
        
.end
