/* Question 2 : log_v1.s
Ecriver à partir du fichier log_v1.c, préalablement créér, la conversion de ce programme en assembleur arm. 

Il s'agit d'un assemblage multiple, avec pluiseurs fichiers, on assemblera et compliera donc ainsi :
"as -gstabs -o sprintf.o sprintfd.s"
"as -gstabs -o log_v1.o log_v1.s"
"ld -O0 log_v1.o sprintfd.o"
*/

.equ SYS_EXIT, 1
.equ SYS_WRITE, 4
.equ EXIT_SUCCESS, 0

.arm
.data  

int: .word 5
strfin: .asciz "\n"
/* Longueur allouée pour un adresse, de la taille du buffer standard */
str:	.space 256 

.text
.globl _start

 _start:
    ldr r1, =int
    ldr r0, [r1] /* Correspond à n */
    mov r1, #31 
    /* Correspond à k. Fera le test par la suite
     en prenant le bit le plus à gauche */
    /* Boucle for(k=31; k<0 && !(n>>k&1); k--) */
    boucle:
      /* Met dans r1 la soustraction de r1 avec la valeur 1 */
      subs r1, r1, #1 
      /* Passe à l'étiquette "break" si l'instruction 
      précédente est une infériorité ou une égalité */
      ble break 
      /* Met le décalage vers la gauche des bits de r0, de r1 position, dans r2 */
      lsr r2, r0, r1
      /* Comparaison avec le premier bit de r2 (le plus à gauche) */
      tst r2, #1
      /* Passe à "boucle" si égalité */
      beq boucle
       
    break:
      ldr r0, =str
      bl sprintfd /* Appel de la fonction dans le fichier sprintfd */
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
      mov r0, #EXIT_SUCCESS
      mov r7, #SYS_EXIT
      swi #0
.end
