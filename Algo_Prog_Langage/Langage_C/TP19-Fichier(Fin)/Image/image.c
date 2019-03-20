/*
Question 1 : Image. 
Afficher une fenêtre qui contienne seulement le quart inférieur droit de l'image 'image.bin'. 
Le programme ne devra pas lire dans le fichier d'information dont il n'a pas besoin. 
*/

#include <stdlib.h>
#include <stdio.h>
#include <graph.h>

int main(void){
	FILE* flux;
	int largeur, i;
	int hauteur, j;
	long deplacement;
	couleur pixel;

	flux = fopen("image.bin", "r");
	fread(&largeur,4,1,flux);
	fread(&hauteur,4,1,flux);

	InitialiserGraphique();
    CreerFenetre(10,10,largeur/2,hauteur/2);
    deplacement=sizeof(couleur)*largeur/2+sizeof(couleur)*hauteur/2;

    for(i=0;i<largeur;i++){
    	for(j=0;j<hauteur;j++){
    		if (i>largeur/2 && j>hauteur/2) {
    			fread(&pixel,sizeof(couleur),1,flux);
	    		ChoisirCouleurDessin(pixel);
	    		DessinerPixel(i-largeur/2,j-hauteur/2);
    		} else
    			fseek(flux,(long)(sizeof(couleur)), SEEK_CUR);
    	}
    }
    while(1);
	fclose(flux);
    return EXIT_SUCCESS;
}