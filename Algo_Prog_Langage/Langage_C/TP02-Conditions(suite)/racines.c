/*
Question 3 : Racines.
Écrivez un programme qui demande à l'utilisateur les trois coefficients réels d'une équation du second degré, 
puis en affiche les éventuelles solutions réelles. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
  double a,b,c, delta;
  double x, x1, x2;

  printf("Ecrivez vos trois coefficients a(x^2) + bx + c:\n");
  printf("Entrez a : ");
  scanf("%lf", &a);
  printf("Entrez b : ");
  scanf("%lf", &b);
  printf("Entrez c : ");
  scanf("%lf", &c);

  delta = pow(b,2) - 4*a*c;

  if (delta < 0)
    printf ("Pour la fonction %.2lf(x^2) + %.2lfx + %.2lf, il n'y a pas de solutions\n", a, b, c);
  else if (delta > 0){
    x1 = (-b-sqrt(delta))/(2*a);
    x2 = (-b+sqrt(delta))/(2*a);
    printf("Il y a 2 solutions reelles : \nx1 = %.2f\nx2 = %.2f\n", x1, x2);
  }else{
    x = -b/(2*a);
    printf("Il y a une solution reelle : \nx = %.2f", x);
  }
  return EXIT_SUCCESS;
}	