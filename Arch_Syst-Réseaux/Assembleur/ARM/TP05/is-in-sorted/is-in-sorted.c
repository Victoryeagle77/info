/*
Question 2 : Recherche. 
Faites un programme qui gère un tableau puis après son affichage, que l'utilisateur puisse entrer une valeur. 
Le programme affichera alors le plus petit indice où on peut trouver cette valeur dans le tableau 
(ou -1 si la valeur ne s'y trouve pas). 
On dispose de la fonction memb à qui on passe la valeur de x, la taille et l’adresse d’un tableau d’entiers.
*/

#include <stdio.h>
#include <stdlib.h>

/* Fonction memb */
int memb(int *tab, int taille, int x){
  int i;
  for (i=0; (tab[i] != x) && (i<taille); i++); 
  /* 
  Tant que les valeurs du tableau ne sont pas égale à la valeur entrée,
  ET que toutes les positions du tableau n'ont pas encore été parcourues, 
  incrémenter i.  
  */
  if (i==(taille)) { return -1; }
  else { return i; }
}

int main (void){ 
  int *tab; 
  int taille, i, x;
  /* Saisie des données */
  printf("Dimension du tableau : ");
  scanf("%d", &taille);
  tab = (int*)calloc(taille, sizeof(int));
  /* Lecture du tableau */
  for (i=0; i<taille; i++){
      printf("arg[%d] : ", i);
      scanf("%d", &tab[i]);
  }
  /* Affichage du tableau */
  for (i=0; i<taille; i++)
      printf("| %d ", tab[i]);

  putchar('|');
  putchar('\n');
  /* Recherche de valeur */
  printf("-> Entrez une valeur à chercher dans le tableau : ");
	scanf("%d", &x);
  printf("Valeur %d au niveau tab[%d]\n", x, memb(tab, taille, x));
  return 0;
}
