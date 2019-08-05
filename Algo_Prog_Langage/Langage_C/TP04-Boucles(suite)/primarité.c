/*
Question 2.5 : Primarité. 
Écrivez un programme qui demande à l'utilisateur un entier naturel puis indique si cet entier est premier.
----------
|Remarque| Un entier est premier si et seulement si il admet exactement deux diviseurs stricts : 1 et lui-même.
----------
*/

#include <stdio.h>
#include <stdlib.h>

int main(void){
  unsigned int nombre, i, premier=1;
  do{
    printf("Entrez un entier STRICTEMENT POSITIF : ");
    scanf("%u", &nombre);
  } while(nombre <= 0);
  /* Décrémentation de la valeur i quand :
  * i vaut la valeur - 1,
  * i est différent de 1,
  La boucle calcule ainsi pour la valeur entrée 2 diviseurs : 1 et elle-même. */
  for(i = nombre-1; i != 1 ; i--){
    /* Si le reste de la division euclidenne entre i et la valeur est 0, le nombre n'est pas premier. */
    if(nombre % i == 0) { premier = 0; }
  }
  /* Si premier == 1 */
  if(premier) { printf("Premier !\n"); }
  else { printf("Non premier !\n"); }
  return 0;
}