/*
Qestion 2 : Étapes. 
Exécutez le programme suivant dans gdb pas à pas, 
puis observer l'évolution des variables.

int main(void) {
  int a = 1, b = 2, c = 3;
  int *p, *q;
  p=&a;
  q=&c;
  *p=(*q)++;
  p=q;
  q=&b;
  *p-=*q;
  ++*q;
  *p*=*q;
  a=++*q**p;
  p=&a;
  *q=*p/(*q);
  return EXIT_SUCCESS;
}
*/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int a = 1, b = 2, c = 3;
  int *p, *q;
  
  printf("-> Etapes du pointage d'un tas d'instructions <-\n");
  p=&a;
  q=&c;
  *p=(*q)++;
  p=q;
  q=&b;
  *p-=*q;
  ++*q;
  *p*=*q;
  a=++*q**p;
  p=&a;
  *q=*p/(*q);
  return EXIT_SUCCESS;
}

/***** DEBOGUAGE ******/

/* Pour commencer on tape dans l'invite de commande (dans le répertoire de ce fichier) : 

---> Manuel <---
-> breakpoint :    b   <Numéro de la ligne>
Permet de marquer une ligne et de faire suivre l'exécution,
à partir de celle-ci.
-> run :           r
Permet de lancer un programme dans (gdb)
-> print :         p   <Nom de variables>
Permet d'afficher la valeur d'une variable,
à n'importe quel endroit d'un programme après le breakpoint.
-> backtrace :     bt 
-> list :          l   <Numéro de la ligne>
Permet d'afficher une liste de lignes en inscrivant le numéro de la dernière.
-> step :          s
Permet la lecture ligne par ligne depuis le breakpoint.

[bob@box TP13-Débogueur]$ gcc -g <programme>
[bob@box TP13-Débogueur]$ gdb ./a.out
Un fois dans gdb, on attérit dans l'intérface de déboguage.
(gdb) b étapes.c:27
(gdb) r
// Observation des variables
(gdb) s
(gdb) p <Variables(a, b, c) | ou Pointeurs(*p, *q) | ou Adresses(&a, &b, &c)>
Et ainsi de suite pour afficher l'évolution des variables.
*/
