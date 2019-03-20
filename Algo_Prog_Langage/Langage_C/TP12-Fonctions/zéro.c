/*
Question 3 : Zéro. 
Voici une fonction qui met une variable à zéro, dans un programme qui illustre son usage :
void zero(double a) {
  a = 0.0;
}
 
int main(void) {
  double x=37.5;
  printf("avant : %f\n", x);
  zero(x);
  printf("après : %f\n", x);
  return EXIT_SUCCESS;
}

Testez cet exemple. Est-ce que la fonction fait son travail ? Pouvez-vous expliquer pourquoi ? 
Modifiez la définition de la fonction et son appel pour que cela marche comme prévu. 
*/

#include <stdio.h>
#include <stdlib.h>

void zero(double *a) {
   *a = 0.0;
}
 
int main(void) {
  double x = 37.5;
  printf("avant : %.1f\n", x);
  zero(&x); // Récupération de l'adresse
  printf("après : %.1f\n", x);
  return EXIT_SUCCESS;
}

/* 
Dans ce programme, la fonction "zero" n'agit pas,
car le chiffre censé devenir 0 après le passage de la fonction reste le même avant et après. 
./a.out 
avant : 37.500000
après : 37.500000
La fonction est corrcete, il suffit de faire de la variable "a" un pointeur,
afin de pouvoir récupérer son adresse dans zero(&x), soit sa valeur en tant que variable donc 0.0.
*/
