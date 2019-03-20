/*
Question 1 ] : Affichage de chaine
Faites un programme affichant une chaine de caractère. 
*/

/* Equivalent de define, constantes */
.equ SYS_EXIT, 1
.equ SYS_WRITE, 4

.arm /* Assembleur type */
.data /* La séction data permet de protéger de la compilation les variables */
  msg:	.asciz "Chaine\n" 
  /* Décomposition pour manipulaiton en octet de la chaine 
  Définition de message en ascii [z pour comprendre le '\0'] */
  len = . - msg

/* Lancement global principal */
.text
.globl _start

_start:
  mov r0, #1
  ldr r1, =msg /* Manipulaiton par adressage de la chaine, déplacé dans r1 */
  ldr r2, =len /* Manipulaiton par adressage de la longuer de la chaine */
  /* Déplace 4 dans r7 */
  mov r7, #SYS_WRITE
  /* Arrêt du programme et analyse des valeurs dans les registres,
  Puis relancement du programme. */
  swi #0
  mov r0, #0
  /* Déplace 1 dans r7 */
  mov r7, #SYS_EXIT
  swi #0
.end
/* Saut de ligne obligatoire pour assembler en arm */