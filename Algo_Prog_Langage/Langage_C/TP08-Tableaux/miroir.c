/*
Question 5 : Miroir. 
Modifiez le programme de l'exercice "remplissage" pour que le programme affiche normalement les valeurs, 
puis de la dernière à la première dans le sens d'apparition des valeurs du tableau normale sans inverser l'ordre.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAB 10

void ligne(void){
  putchar('+');
  for(int i=0; i<TAB; i++)
    printf("-----+");
  putchar('\n');
}

int main (void){ 
  int i;
  int tab[TAB];
  srand(time(NULL));
  ligne();
  putchar('|');
  for(i = 0; i < TAB; i++) {
    tab[i]=(rand()%101)-50;
    printf(" %3.1d |", tab[i]);
  }
  putchar('\n');
  ligne();
    
  printf("--> Tableau inverse <--\n");
  ligne();
  putchar('|');
  /* Boucle partant de 10 et décrémentant la valeur de i à chaque valeur inférieur ou égale à 1. */
  for(i = (TAB-1); i>=0; i--)
    printf(" %3.1d |", tab[i]);
  putchar('\n');
  ligne();
  return EXIT_SUCCESS;
 }