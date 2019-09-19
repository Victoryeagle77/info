/*
Question 1 : Maximum
Ecrivez un programme créant une liste contenant 10 eniter de type "unsigned short" choisis
aléatoirement entre 111 et 999, et qui affiche ensuite le contenu de la liste, 
puis (à part) le plus grand élément qu'elle contient.

La création (et destruction) de la liste, son affichage et la recherche de son plus grand élément devront 
prendre la forme de fonctions distinctes.
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define ENTIER 10

/* Structure définissant le maillon de la liste "maximum" */
struct maximum {
  unsigned short valeur;
  struct maximum* suivant;
};
typedef struct maximum* maximum;

void generer_liste(maximum courant) {
  int random;
  srand(time(NULL));
  for (int i=0; i<ENTIER; i++) {
    courant->suivant = (struct maximum*)malloc(sizeof(struct maximum));
    random=rand()%(999 - 111 + 1) + 111;
    courant->valeur=random;
    courant=courant->suivant;
  }
  courant->suivant = NULL;
}

unsigned short maximum_absolu(maximum debut) {
  unsigned short position;
  maximum courant;
  courant = debut;
  position = debut->valeur;

  for (int i=0; i < ENTIER; i++) {
    if (courant->valeur > position)
      position = courant->valeur;
    courant=courant->suivant;
  }
  return position;
}

void remplacer_liste(maximum debut) {
  maximum courant;
  courant=debut;
  for (int i=0; i<ENTIER; i++) {
    courant=courant->suivant;
    free(courant);
  }
}

void main(void) {
  system("clear");
  struct maximum max;
  maximum debut;
  debut = &max;
  generer_liste(debut);
  /* Affichage de la liste */
  maximum courant;
  for (courant=debut; courant->suivant != NULL; courant=courant->suivant)
    printf("Valeur : %hu\n", courant->valeur);
	
  printf("Le maximum est : %hu\n", maximum_absolu(debut));
  remplacer_liste(debut);
}