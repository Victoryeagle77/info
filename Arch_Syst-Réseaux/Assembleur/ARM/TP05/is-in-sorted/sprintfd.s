/* Ce fichier d'assembleur ARM permet d'afficher un élément à la console */

.arm
.text
.globl sprintfd

/* La fonction "udivagain" envoie dans r0 le quotient de la division
du contenus de r0 par celui de r1. Le reste est placé dans r1. */

/* Divise le contenu de r0 par celui de r1 
retourne le quotient dans r0 et le reste dans r1 */
udivagain: 
  stmfd sp!,{r2,lr}
  mov r2, #0 /* Le quotient est bougé dans r2 */
  
yoop:	
  cmp r0, r1
  addpl r2, #1
  subpl r0, r1
  bpl yoop
  /* Met le reste dans r1 */
  mov r1, r0
  /* Met le quotient dans r0 */
  mov r0, r2
  ldmfd sp!,{r2,pc}
	
  /* La fonction sprintfd écrit les entiers contenus dans le register r1,
  en format decimal en chaine str pointée par le registre r0. 
  Retourne dans r1 la longueur de str. */

sprintfd:
  stmfd sp!,{r2-r4,lr}
  mov r2, #0
  strb r2, [r0] /* Efface le minimum signé dans le cas ou le nombre entier était négatif */
  mov r4, #1
  cmp r1, #0
  addeq r1, r1, #0x30
  streqb r1, [r0]
  beq ret
  mov r2, #0x2d /* Ascii du plus petit nombre signé dans r2 */
  cmp r1, #0
  strmib r2, [r0]  /* si le nombre entier est négatif, str doit commencer avec le minimum */
  rsbmi r1, r1, #0  /* Si le nombre entier est négatif, on travaille avec son opposé */
  /* On se prépare à appeler udivagain. Il doit y trouvé le dividende dans r0. */
  mov r2, r0 /* On sauvegarde donc le pointage par adresse dans r2 */
  mov r3, #0 /* r3 contient le nombre de fois qu'on divisera par 10 un entier */
  mov r0, r1 /* udivagain doit trouver le dividende dans r0 */

loop: 
  mov r1, #10  /* udivagain doit trouver le diviseur dans r1 */
  bl udivagain
  /* Le quotient est dans r0, le reste est dans r1 */
  add r1,r1, #0x30 */ Passage de nombre entier en ascii */
  stmfd sp!,{r1}
  add r3, r3, #1
  cmp r0, #0
  bne loop

  /* On termine avec un dividende de 0. 
  On écrit la chaine en sens inverse */
  mov r4,r3
  mov r1,r2 /* commence avec la chaine dans r1 */
  ldrb r0, [r2]
  cmp r0, #0x2d
  addeq r4, r4, #1 /* Si négatif, additionne 1 à la longueur de la chaine (signe minimum) */
  addeq r1, r1, #1 /* Si le minimum est signé, passe à la location du byte suivant */

popagain:
  ldmfd sp!, {r0}
  strb r0, [r1] /* Ecrit le nombre en chaine */
  subs r3, r3, #1
  addne r1, r1, #1 /* Préparation de la location pour le prochaine nombre */
  bne popagain

  mov r0, r2 /* r0 pointe vers str */
  
ret:
  mov r1, r4
  ldmfd sp!, {r2-r4,pc}

.end
