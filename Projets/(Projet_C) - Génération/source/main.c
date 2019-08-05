#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include "generation.h"
#include "affichage.h"
#include "accueil.h"

int main(void){
  int i, choix;
  int taille1 = 1200;
  int taille2 = 1200;
  terrain** relief;
  /* Création de la fenetre et initialisation des variables */
  InitialiserGraphique();
  CreerFenetre(0, 0, 800, 800);
  /* Menu principal */
  AfficheAccueil();
  choix = selection();
  if(choix == 0){ return EXIT_SUCCESS; }
  /* Allocaton dynamique de la première dimension du tableau */
  relief = malloc(taille1 * sizeof(*relief));
  /* Allocation dynamique de la deuxième dimension du tableau */
  for(i=0; i<taille1; i++){
    relief[i] = malloc(taille2 * sizeof(*(relief[i])));
    if(relief[i] == NULL){
      for(i = i-1; i >= 0; i--){ free(relief[i]); }
      free(relief);
      return 2;
    }
  }
  while(1){
    /* Appel des fonctions remplissant les "tuiles" du tableau */
    relief = Creation(relief,taille1,taille2);
    relief = Remplissage(relief,taille1,taille2);
    /* Affichage de la carte generée et commandes */
    AfficheCarte(relief,taille1,taille2);
    choix = ToucheApresPartie();
    if(choix == 0){ break; }
    if(choix == 2){
      AfficheAccueil();
      choix = selection();
      if(choix == 0){ break; }   
    }
  }
  /* Libération de la mémoire allouée dynamiquement */
  for(i=0; i < taille1; i++) { free(relief[i]); }
  free(relief);
  return 0;
}