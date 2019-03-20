/*
Question 2 : Image
Le fichier image.bin contient une image dans un format spéciale. On y trouve:

° un int représentant la largeur de l'image en pixels,
° un int représentant la hauteur de l'image en pixels,
° la couleur du pixel supérieur gauche de l'image,
° la couleur du pixel immédiatement en dessous,
° et ainsi de suite, de haut en bas puis colonne par colonne.

Ecrivez un programme qui affiche l'image dans une fenêtre graphique.
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <graph.h> // Bibliothèque graphique

int main(void){
	FILE * flux;
	int longueur,hauteur;
	int i, j;
	couleur coloris; // Type de définition
	flux = fopen("image.bin", "r");
	if(flux==NULL){
		perror("flux");
		exit(0);
	}
	fread(&longueur, sizeof(int), 1, flux);
	fread(&hauteur, sizeof(int), 1, flux);
	// Création d'une fenêtre graphique
	InitialiserGraphique();
    CreerFenetre(0,0,longueur,hauteur);
 	
 	for(i=0; i<longueur; i++){
		for(j=0; j<hauteur; j++){
			
			// Lecture de l'inmage en continue avec la taille du type 'couleur'
			if(fread(&coloris, sizeof(coloris), 1, flux));
			
			ChoisirCouleurDessin(coloris);
			DessinerPixel(i, j); // Dessiner en fonction de la hauteur et de la longueur
		}
	}

    Touche(); // Empêche que la fenêtre se ferme après avoir lu le flux
    fclose(flux);
    FermerGraphique();
    return 0;
}
