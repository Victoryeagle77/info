#include "objets.h"

/* Enumération de la validité ou non d'une couleur */
enum color { valide };  

/* Zone d'intercation cliquable à la souris selon les coordonées 
de celle-ci par rapport à l'écran */
int interaction(int x, int y, int position[]) {
	if (x > position[0] && (x < position[0] + position[2])) {
		if (y > position[1] && (y < position[1] + position[3]))
			return 1;
	}
	return 0;
}

void verification(int case_choisie[], int correction[], int resultat[]) {
	unsigned short int test[4];
	unsigned short int i;
	for (i = 0; i < 4; i++) { test[i] = correction[i]; }
	/* Vérification de la présence d'une ou plus couleurs présentes et bien placées */
	for (i = 0; i < 4; i++) { 
		if(case_choisie[i] == test[i]){
			resultat[i] = 1;  /* 1 sert de booléen correspondant à une couleur bien placée */
			case_choisie[i] = valide; /* dans le tableau nous remplacons par valide quand la couleur a été vérifiée */
			test[i] = valide;
		} else { resultat[i] = 0; } /* 0 correspond ici à une couleur mal palcée */
	}
	/* Vérification de la place d'une ou plusieurs couleurs présentes mais mal placées */
	for (i = 0; i < 4; ++i){ 
		if (resultat[i] != 1){
			unsigned short int j;
			for (j = 0; j < 4; ++j){
				if (case_choisie[i] == test[j]){
					resultat[i] = 2;
					case_choisie[i] = valide;
					test[j] = valide;
				}
			}
		}
	}
}
/* Cercles de couleurs à placer */
void couleur_bouton(int position[]) {
	ChoisirCouleurDessin(CouleurParComposante(position[4], 
		position[5], position[6]));
	DessinerRectangle(position[0], position[1], position[2], position[3]);
}
/* Cases dans lequelles on placera les cercle de couleurs */
void case_bouton(int position[]) {
	ChoisirCouleurDessin(CouleurParComposante(position[4], 
		position[5], position[6]));
	DessinerArc(position[0], position[1], position[2], position[3], 90, 360);
}

void coloration(int positionDest[], int positionSource[]) {
	ChoisirCouleurDessin(CouleurParComposante(positionSource[4], 
		positionSource[5], positionSource[6]));
	RemplirArc(positionDest[0], positionDest[1], positionDest[2], positionDest[3], 90, 360);
}

/* Recharge l'apperçu de validation à droite des cases avec les indices */
void rafraichir(int case_1[], int case_2[], int case_3[], int case_4[]) {
	unsigned short int i;
	couleur_bouton(case_1);
	couleur_bouton(case_2);
	couleur_bouton(case_3);
	couleur_bouton(case_4);
	for(i=4; i<7; i++){
		case_1[i] = case_2[i] = case_3[i] = case_4[i] = 200;
		case_1[i] = case_2[i] = case_3[i] = case_4[i] = 100;
	}
}

/* Position, définition et couleur des cercles de couleurs à séléctionner */
Bouton bouton[7] = {
	{100, 600, 30, 30, 0, 0, 0, 0}, 
	{100, 50, 30, 30, 255, 255, 0, 0}, /* Jaune */
	{100, 100, 30, 30, 0, 255, 0, 0}, /* Vert */
	{100, 150, 30, 30, 0, 0, 255, 0}, /* BLeu */
	{100, 200, 30, 30, 255, 0, 0, 0}, /* Rouge */
	{100, 250, 30, 30, 255, 255, 255, 0}, /* Blanc */
	{100, 300, 30, 30, 0, 0, 0, 0} /* Noir */
};

/* Permettera d'afficher à côté des cases intéractives du jeu,
les indices montrant si une couleurs et bien placé ou non ou abscente. */
void indice(int placement[], int cases[]) {
	unsigned short int vrai = placement[0];
	unsigned short int faux = placement[1];
	cases[0] += 20;
	cases[1] += 20;
	ChoisirCouleurDessin(CouleurParComposante(0,0,0));
	DessinerArc(cases[0]-(cases[2]/6), cases[1]-(cases[3]/6),
	 10, 10, 90, 360);
	DessinerArc(cases[0]+(cases[2]/6), cases[1]-(cases[3]/6),
	 10, 10, 90, 360);
	DessinerArc(cases[0]-(cases[2]/6), cases[1]+(cases[3]/6),
	 10, 10, 90, 360);
	DessinerArc(cases[0]+(cases[2]/6), cases[1]+(cases[3]/6),
	 10, 10, 90, 360);
	
	/* Si la couleur placée est correpsonde bien à une couleur choisie aléatoirement, 
	l'indice affiché est de couleur blanche. */
	if (vrai > 0) {
		vrai--;
		ChoisirCouleurDessin(CouleurParComposante(255,255,255)); /* RGB = Blanc */
		RemplirArc(cases[0]-(cases[2]/6), cases[1]-(cases[3]/6), 
			10, 10, 90, 360);
	/* Sinon il est de couleur noire. */
	} else if (faux > 0) { 
		faux--;
		ChoisirCouleurDessin(CouleurParComposante(0,0,0)); /* RGB = Noir */
		RemplirArc(cases[0]-(cases[2]/6), cases[1]-(cases[3]/6), 10, 10, 90, 360);
	}
	/* Afficher 4 fois pour les 4 cases à compléter */
	if (vrai > 0) {
		vrai--;
		ChoisirCouleurDessin(CouleurParComposante(255,255,255));
		RemplirArc(cases[0]+(cases[2]/6), cases[1]-(cases[3]/6), 10, 10, 90, 360);
	} else if (faux > 0) {
		faux--;
		ChoisirCouleurDessin(CouleurParComposante(0,0,0));
		RemplirArc(cases[0]+(cases[2]/6), cases[1]-(cases[3]/6), 10, 10, 90, 360);
	}
	if (vrai > 0) {
		vrai--;
		ChoisirCouleurDessin(CouleurParComposante(255,255,255));
		RemplirArc(cases[0]-(cases[2]/6), cases[1]+(cases[3]/6), 10, 10, 90, 360);
	} else if (faux > 0) {
		faux--;
		ChoisirCouleurDessin(CouleurParComposante(0,0,0));
		RemplirArc(cases[0]-(cases[2]/6), cases[1]+(cases[3]/6), 10, 10, 90, 360);
	}
	if (vrai > 0) {
		vrai--;
		ChoisirCouleurDessin(CouleurParComposante(255,255,255));
		RemplirArc(cases[0]+(cases[2]/6), cases[1]+(cases[3]/6), 10, 10, 90, 360);
	} else if (faux > 0) {
		faux--;
		ChoisirCouleurDessin(CouleurParComposante(0,0,0));
		RemplirArc(cases[0]+(cases[2]/6), cases[1]+(cases[3]/6), 10, 10, 90, 360);
	}
}