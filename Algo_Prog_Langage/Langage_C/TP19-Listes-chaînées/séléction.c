/* Question 3 : Sélection. 

Écrivez une fonction qui ordonne une liste par la méthode du tri par sélection. 
Pour cela, la liste de départ sera considérée comme la «liste non triée». 
On crée une nouvelle liste dite «liste triée», qui est initialement vide.

  On retire le plus grand élément de la liste non triée,
  On ajoute cet élément au début de la liste triée,
  On recommence jusqu'à avoir vidé la liste non triée.

Écrivez un programme qui teste cette fonction sur une liste générée comme au premier exercice. 
*/

#include <stdio.h>
#include <stdlib.h>
 
typedef struct tri{
  int data;
  struct tri *suivant;
} tri;

tri *liste_insertion(tri *liste, int x){
  tri *nouveau = malloc(sizeof *nouveau);
  if (nouveau == NULL){ exit(0); }
  else {
    tri *tmp = NULL;
    tri *element = liste;
    nouveau->data = x;
    while (element != NULL && element->data <= x){
      tmp = element;
      element = element->suivant;
    }
    nouveau->suivant = element;
    if (tmp != NULL){ tmp->suivant = nouveau; }
    else{ liste = nouveau; }
  }
  return liste;
}

void liste_free(tri **liste){
  while (*liste != NULL){
    tri *tmp = (*liste)->suivant;
    free(*liste), *liste = NULL;
    *liste = tmp;
  }
}
 
int main(void){
  system("clear");
  tri *liste = NULL;
  /* Liste de nombre entier */
  int tab[] = {2, 27, -32, 1, -92, 321};
  for (int i = 0; i < sizeof tab / sizeof tab[0]; i++)
    liste = liste_insertion(liste, tab[i]);
  /* Affichage de la liste */
  while (liste != NULL){
    printf("%d ", liste->data);
    liste = liste->suivant;
  }
  putchar('\n');
 
  liste_free(&liste);
  exit(0);
}