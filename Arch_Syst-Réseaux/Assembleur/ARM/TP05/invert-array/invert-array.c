/*
Question 3 ] invert-array
On écrit invert-array.s dans lequel on dispose de deux fonctions. 
La fonction disp qui affiche les éléments d’un tableau d’entiers, 
et la fonction invert qui inverse les éléments dans un tableau d’entiers. 
Chacune des deux fonctions reçoit la taille du tableau et l’adresse du début du tableau.

! Contrainte !
On utilisera deux pointeurs : un sur le début du tableau, l’autre sur la fin du tableau. 
On place les valeurs trouvées à ces adresses dans deux variables disons, x, y, respectivement. 
On écrit la valeur de y à l’adresse indiquée par le premier pointeur et on écrit la valeur de x à l’adresse indiquée par le deuxième pointeur. 
Le premier pointeur avance, le deuxième recule et on recommence.
*/


#include <stdio.h>
#include <stdlib.h>

void disp(int *tab, int capacite) {
  /* Premier élément du tableau pointé tab[0] */
  int *pointeur_debut = tab;
  /* Dernier élément du tableau pointé tab[capacité - 1] */
  int *pointeur_fin = tab + (capacite - 1);
  /* Faire en toute circonstance le parcour de l'adresse du talbeau à partir de sa première valeur pointé */
  while(1) {
    /* Sauf si l'adresse du pointeur de début est supérieur à celle de celui de fin, 
    Soit si la position de tab[0] et situé après tab[capacité - 1], on sort*/
    if (pointeur_debut > pointeur_fin) { break; }
    printf("| %d ", *pointeur_debut);
    pointeur_debut++;
  }
  putchar('|');
}

void invert(int *tab, int capacite) {
  int *pointeur_debut = tab;
  int *pointeur_fin = tab + (capacite - 1);
  int y, x;
  while(1) {
    /* Inversion */
    if (pointeur_debut >= pointeur_fin) { break; }
      y = *pointeur_debut;
      x = *pointeur_fin;
      /* y = pointeur premier, x = pointeur d'après */
      *pointeur_debut = x; *pointeur_fin = y;
       pointeur_debut++; pointeur_fin--;
    }
    disp(tab, capacite);
}

int main(void){
  int i, capacite, *tab;
  printf("Taille du tableau: ");
  scanf("%d", &capacite);
  tab = (int*)calloc(capacite, sizeof(int));

  for(i = 0; i < capacite; i++){
    printf("Entrer la valeur de tab[%d]: ", i);
    scanf("%d", &tab[i]);
  }
  invert(tab, capacite);
  putchar('\n');
  return 0;
}