/*
Questions 2 : Calculateur

Le fichier 'func-def.txt' contient la definition recursive de la fonction 
f: NxN->Z (c.a.d. les arguments sont les entiers naturels, 
la valeur est un entier signe). Le fichier 'argXY.dat' contient un entier non-signe, soit K, en format machine. 
Il vous faut ecrire un programme en assembleur ARM,
qui calcule les valeurs de la fonction 'f' pour tous les couples des arguments :
<i,j> tels que 0<=i<=K et 0<=j<=K.

(1) Ecrivez en C un programme 'calc-mod.c' qui fait le calcul demandé et qui:
  (a) Affiche les resultats pour que nous puissions les voir
  (b) Met les resultats dans le fichier 'res-c.dat';
  Celui-ci devra être compilable à la main en pré-assembleur 
  (avec étiquettes remplacant toutes les conditions et les boucles).

(2) Faites ensuite le programme 'calc.s' en assembleur ARM,
qui calcule la même fonction et qui met les resultats dans le fichier 'res-s.dat'.

*/

.arm
/*
  Fonction ayant besoin de deux arguments :
  * r4 -> x = i
  * r5 -> y = j
  * r3 -> variable de stockage v de la fonction
  * r2 -> variable de stockage z de la fonction
  * r1 -> variable r dans laquelle la fonction renvoie sa valeur
  * r8 et r9 -> Compteurs de boucles i et j 
  * r10 -> stocke la valeur du file descriptor
  * r6 -> stocke la valeur de k
*/
.set SYS_EXIT, 0
.set SYS_READ, 3
.set SYS_WRITE, 4
.set SYS_OPEN, 5
.set SYS_CLOSE, 6

.data
  file_src: .asciz "arg.dat"
  file_dest: .asciz "res-s.dat"
  flag: .word 0x241
  /* Permission pour ouvrir en lecture seule : 0444 */
  perm_rd: .word 0x124
  /* Permission pour ouvrir en ecriture seule : 0666 */
  perm_wo: .word 0x1b6

.text
.globl _start

/* Fonction int calc(unsigned int x, unsigned int y) */
calc:
  /* Permet de mettre dans la pile les registres r4, r5.
  Soit v et z. */
  push {r4,r5,lr}
  /* if (x==0) { goto Sortie; } */
  cmp r4, #0
  beq Sortie
  /* if (y==0) { goto Result_x; } */
  cmp r5, #0
  beq Result_x
  /* Multiplication simple dont le résultat est placé dans r1 
  Correspond à : res = x*y; */
  mul r1, r4, r5
  /* x--; */
  sub r4, r4, #1
  /* calc(x,y); */
  bl calc
  mov r3, r1
  sub r5, r5, #1
  /* calc(x,y); */
  bl calc
  mov r2, r1
  /* res *= z; */
  mul r1, r2, r1
  /* res -= v; */
  sub r1, r1, r3
  /* goto Resultat; */
  b Resultat
  /* return x */
  Result_x:
    mov r1, r4
    b Resultat
  /* return 1 */
  Sortie:
    mov r1, #1
    b Resultat

  /* Libère de la pile les registres r4, r5
  return res */
  Resultat:
    pop {r4,r5,pc}

/* int main(void) */
_start:
  /* On initialise i */
  mov r4, #0
  /* On initialise j */
  mov r5, #0
  /* fd = open("arg.dat", O_RDONLY, 0444); */
  ldr r0, =file_src
  mov r1, #0
  ldr r3, =perm_rd
  ldr r2, [r3]
  mov r7, #SYS_OPEN
  swi #0
  mov r10, r0
  /* if (fd > 0) { goto Lecture; } */
  cmp r0, #0
  bgt Lecture
  /* return 1; */
  mov r0, #1
  mov r7, #SYS_EXIT
  swi #0

  Lecture:
    /* read(fd, &k, 4); */
    mov r0, r10
    mov r2, #4
    mov r7, #SYS_READ
    swi #0
    mov r6, r1
    /* if (res==4) { goto Analyse; } */
    cmp r0, #4
    beq Analyse
    /* return 2 */
    mov r0, #2
    mov r7, #SYS_EXIT
    swi #0

  Analyse:
    /* Fermeture du fichier arg.dat */ 
    mov r7, #SYS_CLOSE
    swi #0
    /* Ouverture du fichier res-c.dat  
    fd = open("res-c.dat", O_WRONLY|O_TRUNC|O_CREAT, 0666); */
    ldr r0, =file_dest
    ldr r3, =flag
    ldr r1, [r3]
    /* Permission 0666 */
    ldr r3, =perm_wo
    ldr r2, [r3]
    mov r7, #SYS_OPEN
    swi #0
    mov r10, r0
    /* if (fd>0) { goto Ecriture; } */
    cmp r0, #0
    bgt Ecriture
    /* return 3*/
    mov r0, #3
    mov r7, #SYS_EXIT
    swi #0

  Ecriture:
    Boucle:
      /* r = calc(i, j); */
      bl calc
      /* res = write(fd, &r, 4); */
      mov r0, #1
      mov r2, #4
      mov r7, #SYS_WRITE
      swi #0
      mov r0, r10
      swi #0
      /* if (res == 4) { goto Suite; }*/
      cmp r0, #4
      beq Suite
      /* return 4 */
      mov r0, #4
      mov r7, #SYS_EXIT
      swi #0

  Suite:
    /* j++; */
    add r5, r5, #1
    /* if (j<k) { goto Fermeture; } */
    cmp r5, r6
    blt Fermeture
    /* j=0; */
    mov r5, #0
    /* i++; */
    add r4, r4, #1

  Fermeture:
    /* if (i<k) { goto Boucle; } */
    cmp r4,r6
    blt Boucle

    mov r7, #SYS_CLOSE
    swi #0
    /* Sorite standard */
    mov r0, #0
    mov r7, #SYS_EXIT
    swi #0
.end
