/* Question 3 : Chaînée. 
Faite un file de caractère avec une des structure et un système de maillage.
*/

#include <stdio.h>
#include <stdlib.h>

#include "file.h"

void main(void) {
  file f;
  char instru;
  char stock;
  f.premier=NULL;
  f.dernier=NULL;
  printf("La file attend vos ordres\n");
  while (instru != 'q') {
    printf("> ");
    instru=getchar();
    if (instru=='+') {
      stock=getchar();
      enqueue(&f,stock);
      printf("Le caractère %c a été ajouté\n", stock);
    }
    if (empty(f)){ printf("La file est vide\n"); }
    else {
      if (instru=='-') {
        stock=dequeue(&f);
        printf("Le caractère %c a été supprimé\n", stock);	
      } else if (instru=='t') {
        stock=top(f);
        printf("Le caractère au sommet de la file est %c\n", stock);
      } else if (instru=='c') {
        clear(&f);
        printf("La file a été vidé\n");
      }
    }
  }
  printf("Au revoir\n");
}