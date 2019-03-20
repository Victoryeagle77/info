#include <time.h>
#include <graph.h>
#include "generation.h"
#include "affichage.h"

int ToucheApresPartie(void){
	int t;
	while(1){
		if(ToucheEnAttente()){
			t = Touche();
			if(t == XK_q){ return 0; }
			if(t == XK_d){ return 1; }
			if(t == XK_m){ return 2; }
		}
	}
}

void AfficheCarte(terrain** tableau, int k, int l){
	int i, j;
	couleur montagne, herbe, sable, eau, coloration;
	eau = CouleurParComposante(25,75,180);
	sable = CouleurParComposante(180,180,0);
	herbe = CouleurParComposante(0,120,0);
	montagne = CouleurParComposante(200,100,0);
	for(i=0; i<k; i++){
		for(j=0; j<l; j++){
			if(tableau[i][j].niveau < 4)
				coloration = eau;
			else {
				if(tableau[i][j].niveau < 5)
					coloration = sable;
				else {
					if(tableau[i][j].niveau < 9)
						coloration = herbe;
					else{ coloration = montagne; }
				}
			}
			ChoisirCouleurDessin(coloration);
			DessinerPixel(i,j);
		}
	}
}
