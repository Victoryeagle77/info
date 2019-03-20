#include "objets.h"
#include <unistd.h>
#include <time.h>

#define SELECTION 0

int jeu(void){
	srand(time(NULL));
	unsigned short int i;
	unsigned short int choix;
	unsigned short int continuation = 1;
	unsigned short int tampon = 0;
	unsigned short int index;
	ChargerImageFond("../images/fond.png");
	int correction[4];
	int combinaison[4];
	Bouton commencer = {50, 520, 50, 50, 0, 0, 0, 0};
	ChargerImage("../images/jouer.png",50, 520, 0, 0, 50, 50);
	Bouton sortie = {900, 520, 50, 50, 0, 0, 0, 0};
	ChargerImage("../images/quitter.png", 900, 520, 0, 0, 50, 50);
	Bouton couleur = {0, 0, 250, 800, 0, 0, 0, 0};
	Bouton grille = {450, 0, 300, 800, 0, 0, 0, 0};
	ChargerImage("../images/logo.png",360, 70, 0, 0, 300, 144);
	 /* Règles du jeu. */
  	EcrireTexte(30, 5*800/6-330, 
              "Le MasterMind est un jeu dont le but est de retrouver une combinaison aleatoire de 4 couleurs parmis 6", 1);
    EcrireTexte(200, 5*800/6-280, "couleurs. Vous placerez les couleurs dans les cases en 10 essais.", 1);
	for (i = 0; i < 4; i++) { combinaison[i] = (rand()%6)+1; }
    
	while (continuation) {
		choix = 0;
		SourisPosition();
		choix = interaction(_X, _Y, commencer);
		if (!choix) {
			choix = interaction(_X, _Y, sortie);
			if (choix) { choix++; }
		}
		if (SourisCliquee()) {
			if (choix == 1) { continuation = 0; } 
			else if (choix == 2) {
				FermerGraphique();
				return EXIT_SUCCESS;
			}
		}
		if (choix > 0) { ChoisirCurseur(0); } 
		else { ChoisirCurseur(2); }	
	}
	FermerGraphique();

	/* Fin du menu => Place au jeu */
	InitialiserGraphique();
	CreerFenetre(0, 0, 950, 800);
	ChargerImageFond("../images/fond.png");
    /* Position, définition et couleur des cercles de couleurs à séléctionner */
	Bouton bouton[7] = {
		{100,600,30,30,0,0,0,0}, 
		{100,50,30,30,255,255,0,0}, /* Jaune */
		{100,100,30,30,0,255,0,0}, /* Vert */
		{100,150,30,30,0,0,255,0}, /* BLeu */
		{100,200,30,30,255,0,0,0}, /* Rouge */
		{100,250,30,30,255,255,255,0}, /* Blanc */
		{100,300,30,30,0,0,0,0} /* Noir */
	};
    
	case_bouton(bouton[SELECTION]);
	for (i = 1; i < 7; i++)	{ case_bouton(bouton[i]); }

	Bouton cases[10][5];

	for (i = 0; i < 10; i++) {
		int j;
		for (j = 0; j < 5; j++)	{
			if (j%5 == 4)
				cases[i][j][0] = 480 + 50*j+ j*10 +50; 
			else
				cases[i][j][0] = 480 + 50*j + j*10;

			cases[i][j][1] = 100 + 50*i + i*10; 
			cases[i][j][2] = 50; 
			cases[i][j][3] = 50; 
			if (j%5 == 4) {
				cases[i][j][4] = 100;						
				cases[i][j][5] = 100;
				cases[i][j][6] = 100;						
			} else { 
			/* Distingue l'aperçu de la correction avec les cases de jeu */
				cases[i][j][4] = 130;						
				cases[i][j][5] = 130; 
				cases[i][j][6] = 130;						
			}
			cases[i][j][7] = 0;
			couleur_bouton(cases[i][j]);
		}
	}
    /* Chargement d'un nouvel écran */
	ChoisirCurseur(2);
	continuation = 1;
	choix = 0;
	index = 0;
	rafraichir(cases[index][0], cases[index][1], 
		cases[index][2], cases[index][3]);
	while (continuation) {
		tampon = 0;
		SourisPosition();
		if (SourisCliquee()) {
			if (interaction(_X, _Y, couleur)) {
				for (i = 1; i < 7; i++)	{
					if (interaction(_X, _Y, bouton[i]))	{
						tampon = i;
						choix = i;
					}
				}
				if (tampon != 0) {
					for (i = 4; i < 7; i++)
						bouton[SELECTION][i] = bouton[tampon][i];
					case_bouton(bouton[SELECTION]);
				}
			} else if (interaction(_X, _Y, grille)) {
				if (choix != 0) {
					for (i = 0; i < 4; i++) {
						if (interaction(_X, _Y, cases[index][i])) {
							cases[index][i][7] = choix;
							coloration(cases[index][i], bouton[SELECTION]);
						}
					}
				}
			}
		}
		if (ToucheEnAttente()) {
			if (Touche() == XK_Return) {
				if (cases[index][0][7] != 0 && cases[index][1][7] != 0 
					&& cases[index][2][7] != 0 && cases[index][3][7] != 0) {
					
					unsigned short int k;
					for(k=0; k<4; k++)
						correction[k] = cases[index][k][7];

					int tab[4];
					verification(correction, combinaison, tab);
					int validation_case[2] = {0, 0};

					for (i = 0; i < 4; i++) {
						if (tab[i] == 1) { validation_case[0]++; }
						else if (tab[i] == 2) { validation_case[1]++; }
					}
					indice(validation_case, cases[index][4]);
					index++;
					if (validation_case[0] == 4) {
						index = -1;
						ChargerImage("../images/victoire.png", 100, 360, 0, 0, 250, 220);
						sleep(3);
						FermerGraphique();
						exit(0);
					} else if (index >= 10) {
						ChargerImage("../images/perdu.png", 140, 380, 0, 0, 180, 180);
						sleep(3);
						FermerGraphique();
						exit(0);
					}
				}
			}
		}
	}
	continuation = 0;
	return 0;
}