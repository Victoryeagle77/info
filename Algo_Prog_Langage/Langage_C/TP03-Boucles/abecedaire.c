/*
Question 2 : Abécédaire. 
Écrivez un programme qui affiche l'alphabet à l'envers (majuscules puis minuscules). 
*/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  printf("Alphabet inverse en minuscules : ");
  /* A partir de z */
  char a='z';
  while(a >= 'a') {
    printf("%c ", a);
    a --;
  }
  /* Décrémentation pour parcourir l'alphabet à l'envers */
  putchar('\n');

  printf("Alphabet inverse en majuscules : ");
  a = 'Z';
  while(a >= 'A') {
    printf("%c ", a);
    a --;
  }
  putchar('\n');
}