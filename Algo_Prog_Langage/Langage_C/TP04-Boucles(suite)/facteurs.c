/*
Question 6 : Lagrange. 
Ecrivez un programme qui demande un entier naturel non-null, et affiche sa décomposition en facteurs, 
qui seront des nombres premiers

280=2*2*2*5*7

Remarque : Pour tous les entiers, le plus petit diviseur autre que 1 est nécessairement premier.
*/

#include <stdio.h>

int main(void){
  unsigned int nombre, facteur=2; /* facteur initialisé à 2	*/
  do{
    printf("Entrez un entier NON-NULL ou POSITIF : ");
    scanf("%u", &nombre);
  }while (nombre <= 0);
        
  printf("%u = ", nombre);
  while(nombre > 1){
    /* Tant que le reste de la division euclidenne de la valeur saisie par 2 vaut 0 */
    while(nombre % facteur == 0){
      printf("+ %u ", facteur);
      nombre /= facteur; /* nombre = nombre / facteur */
    }
    facteur++; /* facteur = facteur + 1 */
  }
  putchar('\n');
  return 0;
}