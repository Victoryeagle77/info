/* 
Question 1 ] Parité
Ecriver un programme vérifiant si un nombre est paire ou pas,
avec un opérateur spécifique : tst
Si le nombre est paire il sera affiché "Even !", sinon il sera affiché "Odd !".
*/

.equ SYS_EXIT, 1
.equ SYS_WRITE, 4

.arm
.data

entier: .word 8 /* Définition en mémoire */
event_1: .asciz "Even !\n"
len_event_1 = . - event_1
event_2: .asciz "Odd !\n"
len_event_2 = . - event_2

.text
.globl _start

_start:
  /* Chargement de constante définies */
  ldr r0, =entier
  /* Chargment depuis la mémoire */
  ldr r1, [r0]
  /* tst effectue un ET bit à bit de tous les éléments donné en argument
  On évite alors de faire une boucle en testant ses éléments.
  On masque les bit de valeurs que l'on n'uitilise pas avec le valeur 1 */
  tst r1, #1
  mov r0, #1
  /* Chargement de la valeur au registre r1 si équivalence */
  ldreq r1, = event_1
  /* Chargement de la valeur au registre r1 s'il n'y a pas équivalence */
  ldrne r1, = event_2
  ldreq r2, = len_event_1
  ldrne r2, = len_event_2
	
  /* Affichage */
  mov r7, #SYS_WRITE
  swi #0
    
  /* Sortie */
  mov r0, #0
  mov r7, #SYS_EXIT
  swi #0
.end
	
