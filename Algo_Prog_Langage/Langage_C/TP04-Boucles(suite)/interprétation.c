/*
Question 5 : Interprétation. 
Écrivez un programme qui demande un entier naturel, puis en affiche le carré. 
Pour cet exercice, vous ne devez pas utiliser scanf (mais il vous reste getchar).
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
  int i = 0, power;
  char car, premier_car;
  printf("Entrez un entier : ");
  car = premier_car = getchar();
  /* Tant que les caractères entrés ne sont pas un saut de ligne */
  while (car != '\n') {
    if(car >= '0' && car <= '9')
      i = 10 * i + (car - '0');
    car = getchar();
  }
  /* Pour les nombres négatifs, le premier caractère entré est un - */
  if(premier_car == '-') { i *= -1; }
  power = pow(i, 2);
  printf("Votre entier (%d)^2 = %d\n", i, power);
  return EXIT_SUCCESS;
}