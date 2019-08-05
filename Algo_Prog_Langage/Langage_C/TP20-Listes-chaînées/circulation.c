/*
Question 2 : Circulation. 
Écrivez une fonction qui retire le dernier élément d'une liste, 
et partant de là une autre fonction qui effectue une permutation circulaire sur 
une liste (tous les éléments avancent d'une position, le dernier élément se retrouve au début).

Écrivez une fonction qui ajoute un élément à la fin d'une liste, 
et une fonction qui retire le premier élément d'une liste. 
Écrivez ensuite une fonction qui applique à une liste une permutation circulaire dans le sens inverse 
(tous les éléments reculent d'une position, le premier élément se retrouve à la fin).

Testez vos fonctions dans un programme qui crée une liste,
et qui permet à l'utilisateur de lui appliquer une rotation de son choix.

bob@box:~$ ./a.out
181 572 648 251 994 637 518 249 175 321 
choisissez une rotation : -5
637 518 249 175 321 181 572 648 251 994 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct liste {
  unsigned short valeur;
  struct liste* suivant;
};
typedef struct liste liste;

void afficher(liste* premier) {
  liste* p;
  for(int i = 0; i<10; p = p->suivant) {
    i++;
    printf("%d ", p->valeur);
  }
}

liste* debut(liste* premier, int nouveau){
  liste* p = (liste*) malloc(sizeof(liste));
  if (p) {
   p->suivant = premier;
   p->valeur = nouveau;
 }
 return p;
}

int main(int argc, char const *argv[]) {
  unsigned short a;
  liste* b = (liste*) malloc(sizeof(liste));
  srand(time(NULL));
  for (int i = 0; i < 10; i++) {
    a = rand()%(889) +111;
    b = debut(b, a);  
  }
  afficher(b);
  putchar ('\n');
  return 0;
}