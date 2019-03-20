#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "generation.h"
#include <graph.h>

terrain** Creation(terrain** tableau,int k, int l){
	int i,j;
	for(i=0;i<k;i++){
		for(j=0;j<l;j++){
			tableau[i][j].x=i;
			tableau[i][j].y=j;
		}
	}
	return tableau;
}

terrain** Nettoyage(terrain** tableau, int k, int l, int c){
	int i, j;
	if(c==0) { return tableau; }
        for(i=1;i<(k-1);i++){
            for(j=1;j<(l-1);j++){
                if(tableau[i][j].niveau < c){ 
                /* Si le niveau est inferieur a celui indiquee alors le niveau deviens égal 
                à la moyenne des 4 cases autour de lui */
                    tableau[i][j].niveau = (tableau[i-1][j].niveau +
                                            tableau[i+1][j].niveau +
                                            tableau[i][j-1].niveau +
                                            tableau[i][j+1].niveau) / 4;
                }
            }
        }
	return Nettoyage(tableau,k,l,c-1);
}

terrain** Remplissage(terrain** tableau, int k, int l){
	int i, j;
	float random;
	srand(time(NULL));
	for(i=0;i<k;i++){
		for(j=0;j<l;j++){
			if((i==0)||(j==0))
				tableau[i][j].niveau = 0; 
				/* Ligne superieur et colonne de gauche sont de l'eau */
			else{
				random = (float)rand()/(float)(RAND_MAX/10); 
				/* reel random entre 0 et 10 */
				if(random < 9) /* 90% de chance */
					tableau[i][j].niveau = (tableau[i][j-1].niveau + tableau[i-1][j].niveau) / 2; 
					/* Moyenne des niveaux de la case a gauche et de la case au dessus */
				else
					tableau[i][j].niveau = (tableau[i][j-1].niveau + tableau[i-1][j].niveau) / 2 + 2; 
					/* Moyenne des niveaux + 2 */		
				if(tableau[i][j].niveau > 11)
					tableau[i][j].niveau = 11; /* Niveau max = 11 */
			}
		}
	}
	Nettoyage(tableau, k, l, 8); 
	/* "Nettoyage" ou "lissage" des niveaux pour un peu plus de coherence */
	return tableau;
}