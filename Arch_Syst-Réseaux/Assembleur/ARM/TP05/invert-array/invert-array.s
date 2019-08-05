/*
Question 3 ] invert-array
On écrit invert-array.s dans lequel on dispose de deux fonctions. 
La fonction disp qui affiche les éléments d’un tableau d’entiers, 
et la fonction invert qui inverse les éléments dans un tableau d’entiers. 
Chacune des deux fonctions reçoit la taille du tableau et l’adresse du début du tableau. 

! Contrainte !
On utilisera deux pointeurs : un sur le début du tableau, l’autre sur la fin du tableau. 
On place les valeurs trouvées à ces adresses dans deux variables disons, x, y, respectivement. 
On écrit la valeur de y à l’adresse indiquée par le premier pointeur et on écrit la valeur de x à l’adresse indiquée par le deuxième pointeur. 
Le premier pointeur avance, le deuxième recule et on recommence. Dans la fonction invert, 
on utilisera un mode d’adressage pre-indexed ou post-indexed ou l’offset est une constante immédiate.
*/

.equ SYS_WRITE, 4
.equ SYS_EXIT, 1

.arm	
.data

sz: .word 4
ary: .word 1,5,6,9
strfin: .asciz "\n"
str: .space 256

.text
/* Partie traitant le maximum d'un tableau d'entier avec le post-indexed addressing mode
On utilise des registres spécifiques pour nos données suivantes:    
--> r0 = Initialisation du pointage *ary[i]
--> r1 = sz
--> r2 = Fin du pointage du tableau *ary[i + (capacité - 1)]
--> r3 = Commencement du tableau
--> r4 = Fin du tableau
*/

invert:
  /* Début du tableau */
  push {r2-r4, lr}

  lsl r1, #2
  sub r2, r1, #4
  add r2, r0, r2

disp:
  cmp r2, r0
  pople {r2-r4, pc}

  /* Echange des pointage */
  ldr r3, [r0]
  ldr r4, [r2]
  /* Stockages des adresses, avec décalage de registre,
  vers la fin et le commencement du tableau */
  str r4, [r0]
  str r3, [r2]

  add r0, #4
  sub r2, #4

  b disp

  pop {r2-r4, pc}

.globl _start

/* Main */
_start: 
    ldr r0, =sz /* taille de tableau */
    ldr r3, [r0]
    ldr r0, =ary /* tableau */

    /* Appel de la fonction invert */
    bl invert
    
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
