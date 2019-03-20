/*
Question 3 ] Max_array
Ecrivez un programme qui trouve le maximum d'un tableau d'entier de taille définie

On vérifie la valeur des registres en faisant :
"gdb ./a.out"
"b 21"
"run"
"step" (au niveau ou on veut voir la valeur du registre voulue)
"i r r1" (pour voir par exemple le contenu de r1) 

Ou "echo $?" qui est plus pratique que gdb
*/

.equ SYS_EXIT, 1

.arm	
.data
/* Définition du tableau de nombre entier */
tableau: 
    .word 2
    .word 3
    .word 6
/* Capacite du tableau */
capacite: .word 3

.text
.globl _start

_start:
    ldr r1, =capacite
    ldr r0, [r1]
    mov r1, #1
    ldr r2, =tableau
    ldr r3, [r2]

    boucle:
     	/* On utilise le chargement de registre à registre avec un décalage par 4.
     	On fait donc un décalage à droite par 2 dans le chargement de registre. */
        ldr r4, [r2, r1, lsl #2]
        cmplt r3, r4 /* comparaison si r3 est inférieur à r4 */
        add r1, r1, #1
        cmp r1, r0
        /* Passe à l'étiquette "boucle" si la condition de 
        l'instruction précédente est une infériorité ou une égalité */
        blt boucle

        mov r0, #0
        mov r7, #SYS_EXIT
        b sortie

    sortie:
        mov r0, #0
        mov r7, #SYS_EXIT
        swi #0

.end
