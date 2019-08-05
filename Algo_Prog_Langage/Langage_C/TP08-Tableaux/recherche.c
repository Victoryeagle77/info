/*
Question 3 : Recherche. 
Modifiez le programme de l'exercice "remplissage" pour qu'après l'affichage du tableau, l'utilisateur puisse entrer une valeur. 
Le programme affichera alors le plus petit indice où on peut trouver cette valeur dans le tableau 
(ou -1 si la valeur ne s'y trouve pas). 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAB 11 

void ligne(void){
  putchar('+');
  for(int i=1; i < TAB; i++)
    printf("-----+");
  putchar('\n');
}

int main (void){ 
  int i, val;
  int tab[TAB];
  srand(time(NULL));
  ligne();
  putchar('|');
  for(i=1; i < TAB; i++) {
    tab[i]=(rand()%101)-50;
    printf(" %3.1d |", tab[i]);
  }
  putchar('\n');
  ligne();
  printf("\n-> Entrez une valeur à chercher dans le tableau : ");
  	
  scanf("%d", &val);
  /* i prend la valeur 1 pour parcourir les valeurs du tableau */
  for (i=1; tab[i]!=val && i<TAB; i++); 
  /* Tant que les valeurs du tableau ne sont pas égale à la valeur entrée ET 
  que toutes les positions du tableau n'ont pas encore été parcourues, incrémenter i. */
  if (i==(TAB)){ printf("-1 --> N'existe pas\n"); }
  else{ printf("Le plus petit indice pour cet entier est : %d\n", i); }
  return 0;
}