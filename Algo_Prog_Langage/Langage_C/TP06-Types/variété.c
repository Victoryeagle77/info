/** 
Question 2 : Variété. 
Écrivez un programme qui affiche la valeur 77 autant de fois que possible, 
en utilisant à chaque fois un type différent.
**/

/* Librairie <stdio.h> à importer pour tout programme en C. */
#include <stdio.h>

/* Definition d'une valeur constante, contrairement à une variable toujours temporaire */
#define VALEUR 77

int main(void) {
  /* Tous les types possibles */
  char c = (char)VALEUR;
  signed char sc  = (signed char)VALEUR;
  unsigned char uc = (unsigned char)VALEUR;
  short int si = (short int)VALEUR;
  unsigned short int usi = (unsigned short int)VALEUR;
  unsigned int ui = (unsigned int)VALEUR; 
  int i = (int)VALEUR;
  long int li = (long int)VALEUR;
  unsigned long int uli = (unsigned long int)VALEUR;
  long long int lli = (long long int)VALEUR;
  unsigned long long int ulli = (unsigned long long int)VALEUR;
  float f = (float)VALEUR;
  double d = (double)VALEUR;
  long double ld = (long double)VALEUR;
  /* Affiche juste les types principaux */
  printf("char : %c\nint : %d\nfloat : %.2f\ndouble (notation scientifique) : %.2e\n", c, i, f, d);
  return 0;
}