/*
Question 1 : Conversion
Faite un programme permettant de convertir un nombre entier en héxadécimal, en octale, et en binaire. 
*/

#include <stdio.h>
 
int main(void) {
  int x, rep, i;
  printf("-> Base <-\nChoisir un entier : ");
  scanf("%d", &x);
  printf("* L'entier en base 10 (decimale) est : %d\n", x);
  /* %o affiche directement en octale */
  printf("* L'entier en base 8 (octale) est : %o\n", x);
  /* %x affiche directement en héxadécimale */
  printf("* L'entier en base 16 (hexadecimale) est : %x\n", x);
  printf("* L'entier en base 2 (bianire) est : ");
  rep = x;
  /* Méthode par opérateur bit à bit pour convertir en binaire */
  for (i = rep-1; i >= 1; i--)
  /* >> est un décalage bit à bit vers la droite 
  & est un l'opérateur "et" bit à bit */
    printf("%d", (x >> i) & 1);
  printf("%d\n", x&1);
  return 0;
}