/* Question 0.5 : Analyse 
Faites un programme qui demande un entier et et affiche ce dernier à la console en arm. 
A compiler comme ceci : 
"as -gstabs -o fichier.o fichier.s"
"gcc fichier.o"
"./a.out"
*/

.arm
/* Gère le scan de la valeur au format entier %d */
Scan: .ascii "%d"
      .align 2
/* Gère l'affichage d'un message avec le format entier %d */
Affichage: .ascii "Votre valeur : %d\n"
           .align 2
/* Configure la gestion de l'affichage de l'analyse  */
Config: .word Scan
        .word Affichage
        
.text
.global main

main:
  /* Poussez sur la pile descendante */
  stmfd sp!, {fp, lr}
  add fp, sp, #4
  sub sp, sp, #8 
  ldr r2, Config
  sub r3, fp, #8
  mov r0, r2
  mov r1, r3
  /* Appel à la fonction scanf("%d", &...) */
  bl __isoc99_scanf
  /* + 4 Pour effectuer un saut de ligne */
  ldr r2, Config + 4
  ldr r3, [fp, #-8]
  mov r0, r2
  mov r1, r3
  /* Appel à la fonction printf("%d") */
  bl printf
  mov r0, r3
  sub sp, fp, #4
  /* Pop de la pile décroissante. */
  ldmfd sp!, {fp, pc}
.end
