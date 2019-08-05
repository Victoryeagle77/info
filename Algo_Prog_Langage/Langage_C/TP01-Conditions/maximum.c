/*
Question 5 : Maximum. 
Écrivez un programme qui demande trois entiers relatifs, puis affiche seulement le plus grand d'entre eux.
Réécrivez ensuite (si nécessaire) ce programme pour qu'il utilise seulement deux variables.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
  int a,b,c,max;
  printf("Inserez un premier entier relatif : ");
  scanf("%d",&a);
  printf("Inserez un deuxieme entier relatif : ");
  scanf("%d",&b);
  printf("Inserez un troisieme entier relatif : ");
  scanf("%d",&c);
  max=a;
  /* Si b > a et b > c */
  if ((b>a) && (b>c)) { max=b; }
  else if((c>a) && (c>b)) { max=c; }
  printf("%d", max);
  return EXIT_SUCCESS;
}
