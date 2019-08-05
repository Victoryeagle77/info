/*
Question 2.5 : Essais
Faites un programme qui compare deux entier entrés en argument de commande.
Utiliser la librairie assert pour effectuer des actions de tests comparatifs.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h> /* Librairie de test */

int rang(int min, int max) {
  int res;
  /* Fonction de test conditionnel */
  assert(min < max);
  res = min + rand()%(max + 1 - min);
  assert((min <= res) && (res < max));
  return res;
}

int main(int argc, char *argv[]){
  int min, max, res;
  if (argc != 3){
    printf("Usage <int> <int>");
    return -1;
  }
  min=(int)strtol(argv[1], NULL, 10);
  max=(int)strtol(argv[2], NULL, 10);
  /* Comparaison */
  res=rang(min,max);
  printf("%d\n", res);
  return 0;
}