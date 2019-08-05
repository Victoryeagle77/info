/*
Question 2 ] Comparaison
Ecrivez un programme qui compare 2 entier entre eux.
*/

/* Equivalent de define */
.equ SYS_EXIT, 1
.equ entier_1, 5
.equ entier_2, 4

.arm /* Assembleur type */
.data /* Données à entrée pour la suite */
.text
/* Lancement global principal */
.globl _start

_start:
  mov r0, #entier_1
  mov r1, #entier_2
  /* Comparaison (soustraction) entre les valeurs contenu dans les registres */
  cmp r0,r1
  /* Arrêt du programme et analyse des valeurs dans les registres,
  Puis relancement du programme. */
  mov r0,#0
  /* Déplace 1 dans r7 */
  mov r7, #SYS_EXIT
  swi #0
.end
