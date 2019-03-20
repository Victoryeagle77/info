/*
Question 1 : Simon
Écrivez un programme qui affiche une fenêtre comportant quatre zones séparées. 
Dans la première phase, le programme met graphiquement en valeur durant une seconde une zone choisie au hasard. 
Le choix est mémorisé dans une file. 
Dans la deuxième phase, le joueur choisit dans quelle zone cliquer. 
Son choix est comparé au choix tiré de la file, et le jeu se termine s'il s'est trompé. 
Si la deuxième phase est fidèle à la première phase, on refait une première phase avec un choix de plus. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include "file.h"

int main(void) {
	InitialiserGraphique();
	CreerFenetre(50,50,250,250);
	ChoisirCouleurDessin(CouleurParComposante(150,0,0));
	RemplirRectangle(150,50,50,50);
	ChoisirCouleurDessin(CouleurParComposante(0,0,150));
	RemplirRectangle(150,150,50,50);
	ChoisirCouleurDessin(CouleurParComposante(0,150,150));
	RemplirRectangle(50,150,50,50);
	ChoisirCouleurDessin(CouleurParComposante(0,150,0));
	RemplirRectangle(50,50,50,50);
	Touche();
	FermerGraphique();
}
