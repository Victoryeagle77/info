#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include "accueil.h"

/* Menu d'accueil */
void AfficheAccueil(void){
  int taille;
  couleur noir = CouleurParComposante(0,0,0);
  couleur vert = CouleurParComposante(100,200,100);
  EffacerEcran(CouleurParComposante(100,100,100));
  ChoisirCouleurDessin(noir);
	
  taille = TailleChaineEcran("=== GENERATION DE TERRAIN ===", 1);
  EcrireTexte(400-taille/2,120,"=== ======================== ===", 1);
  EcrireTexte(400-taille/2,150,">>>  GENERATION DE TERRAIN  <<<", 1);
  EcrireTexte(400-taille/2,180,"=== ======================== ===", 1);
  /* Légende des touches définies à utiliser */
  ChoisirCouleurDessin(CouleurParComposante(200,200,200));
  RemplirRectangle((400-taille/2)-15,350-25,taille+30,40);
  ChoisirCouleurDessin(noir);
  DessinerRectangle((400-taille/2)-15,350-25,taille+30,40);
  taille = TailleChaineEcran(">>>>>> Touches predefinies <<<<<<",1);
  EcrireTexte(400-taille/2,350,">>>>>> Touches predefinies <<<<<<",1);
  /* Bouton de commencement */
  taille = TailleChaineEcran("Lancer la generation",1);
  ChoisirCouleurDessin(vert);
  RemplirRectangle((150-taille/2)-15,750-25,taille+30,40);
  ChoisirCouleurDessin(noir);
  DessinerRectangle((150-taille/2)-15,750-25,taille+30,40);
  EcrireTexte(150-taille/2,750,"Lancer la generation",1);
  /* Bouton quitter */
  taille = TailleChaineEcran("Quitter le programme",1);
  ChoisirCouleurDessin(vert);
  RemplirRectangle((650-taille/2)-15,750-25,taille+30,40);
  ChoisirCouleurDessin(noir);
  DessinerRectangle((650-taille/2)-15,750-25,taille+30,40);
  EcrireTexte(650-taille/2,750,"Quitter le programme",1);

  MenuTouches();
}

/* Séléction des actions dans le menu */
int selection(void){
  while(1){
    if(SourisCliquee()){
      /* Bouton de lancement */
      if(_X >= 40 && _X <= 250 && _Y >= 725 && _Y <= 765)
        return 1;
      /* Bouton de sortie */
      if(_X >= 580 && _X <= 790 && _Y >= 725 && _Y <= 765){
        FermerGraphique();
        return 0;
      }
    }
  }
}

/* Touches d'actions pour la suite de la simulation */
void MenuTouches(void){
  couleur noir = CouleurParComposante(0,0,0);
  couleur c_blanc = CouleurParComposante(255,255,255);
  /* Affichage graphiques des différentes options */
  ChoisirCouleurDessin(c_blanc);
  EcrireTexte(250,470,"'M'",1);
  ChoisirCouleurDessin(noir);
  EcrireTexte(300,470,"Reviens sur le menu",1);

  ChoisirCouleurDessin(c_blanc);
  EcrireTexte(250,500,"'D'",1);
  ChoisirCouleurDessin(noir);
  EcrireTexte(300,500,"Deplacement de la generation",1);

  ChoisirCouleurDessin(c_blanc);
  EcrireTexte(250,530,"'Q'",1);
  ChoisirCouleurDessin(noir);
  EcrireTexte(300,530,"Quitte le programme",1);
}
