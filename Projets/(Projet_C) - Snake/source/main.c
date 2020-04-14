#include "jeu.h"

extern void main(void){
	system("clear");
	srand(time(NULL));
	initialiser();
	InitialiserGraphique();
	CreerFenetre(0, 0, LARGEUR, LONGUEUR);
	jeu();
}