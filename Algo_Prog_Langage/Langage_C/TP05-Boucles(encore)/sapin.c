/*
Question 1  : Sapin. 
Écrivez le programme correspondant à la session suivante :

Hauteur ? 6

     *
    ***
   ***** 
  *******
 *********
***********
*/

#include <stdio.h> 
#include <stdlib.h> 

int main (void) {
   int i, j, hauteur; // i=colonne, j=ligne
   do{
      printf("\nHauteur ? ");
      scanf("%d", &hauteur);
   }while(hauteur<=0);
   putchar('\n');
   for (i=1; i<=hauteur; i++) {
      // Première boucle affichant les étoiles en triangle vers la gauche
      for (j=0;j<hauteur-i;j++)
        printf(" ");
      for (j=0; j<(i*2)-1; j++) 
        // longueur * 2 avec -1 pour afficher l'étoile '*' du haut
        printf("*");

      putchar('\n');
   }
   return 0;
}

