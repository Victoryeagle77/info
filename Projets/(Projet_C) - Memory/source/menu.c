#include "jeu.h"

/* Fonction permettant d'effectuer le choix de la difficulté 
(soit la taille de la grille de jeu définit) */
void choix(void){	
  unsigned short int niveau = 0;
  unsigned short int continuer = 1; /* Réinitialisé à vrai */
  /* Définition de la zone cliquable de différents bouton
  - De la position en abscisse par rapport à l'écran. 
  - De la position en abscisse par rapport à l'écran. 
  - De la longueur d'un bouton. 
  - De la hauteur d'un bouton.
  */
  zone facile = {100, 450, 100, 139};
  zone moyen = {450, 450, 100, 141};
  zone difficile = {800, 450, 100, 142};
  
  CopierZone(2, 1, 0, 0, Maxx(), Maxy(), 0, 0);
  ChargerImage("../images/facile.png", 100, 450, 0, 0, 100, 139);
  ChargerImage("../images/moyen.png", 450, 450, 0, 0, 100, 141);
  ChargerImage("../images/difficile.png", 800, 450, 0, 0, 100, 142);

  ChoisirEcran(2);
  EcrireTexte(125, 5*800/6-260, "Facile", 1);
  ChargerImage("../images/facile.png", 100, 450, 0, 0, 100, 139);
  EcrireTexte(105, 5*800/6-25, "16 cartes", 1);

  EcrireTexte(470, 5*800/6-260, "Moyen", 1);
  ChargerImage("../images/moyen.png", 450, 450, 0, 0, 100, 141);
  EcrireTexte(460, 5*800/6-25, "36 cartes", 1);

  EcrireTexte(815, 5*800/6-260, "Difficile", 1);
  ChargerImage("../images/difficile.png", 800, 450, 0, 0, 100, 142);
  EcrireTexte(810, 5*800/6-25, "64 cartes", 1);

  /* Redirige vers l'écran de choix de difficulté */
  CopierZone(2, 0, 0, 0, Maxx(), Maxy(), 0, 0);
    
  while (continuer) { /* Boucle principale d'intégrité du programme */
    SourisPosition(); /* Relève la position ne longueur et en hauteur de la souris */
    if (interaction(_X, _Y, facile)) {
      CopierZone(2, 0, 550, 420, 57/* Difficile_X */, 83/* Difficile_Y */, 550, 420);
      niveau = 1;
    } else if (interaction(_X, _Y, moyen)) {
      CopierZone(2, 0, 650, 420, 55/* Moyen_X */, 82/* Moyen_Y */, 650, 420);
      niveau = 2;
    } else if (interaction(_X, _Y, difficile)) {
      CopierZone(2, 0, 750, 420, _X/* Facile_X */, _Y/* Facile_X */, 750, 420);
      niveau = 3;	
    } else { niveau = 0; }
    /* Empêche d'activer la suite en cliquant ailleurs
    que sur les 3 niveaux de difficultés. */
    if (SourisCliquee() && niveau != 0) { continuer = 0; }
  } 
  FermerGraphique(); /* Fin du menu */
  jeu(niveau); /* Laisse place au jeu */

}

/* Fonction affichant le menu */
void menu(void) {
  zone jouer = {50, 610, 60, 60};
  zone quitter = {850, 605, 60, 60};
  /* continuer est une variable enitère servant de booléens avec 1 --> vrai et 0 --> faux.
  Booléen de continueation du programme dans les boucles while, (boucles d'intégrités) */
  unsigned short int continuer = 1; /* Initialisé à 1, soit vrai. */
  unsigned short int selection = 0;

  ChoisirEcran(1); /* Charge un écran avec des éléments à remplir. */
  ChargerImageFond("../images/fond.png");	
  ChargerImage("../images/logo.png", 380, 50, 0, 0, 300, 160);
  ChargerImage("../images/jouer.png", 50, 610, 0, 0, 120, 120);
  ChargerImage("../images/quit.png", 850 , 620 ,0 , 0, 80 ,80);
  /* Règles du jeu. */
  EcrireTexte(25, 5*800/6-300, 
              "Le memory est un jeu dont le but est de retrouver des paires de cartes dont le joueur peut voir le contenu", 1);
  EcrireTexte(400, 5*800/6-260, "en cliquant dessus.", 1);
  EcrireTexte(40, 5*800/6-220, 
              "Appuyez sur 't' pour passer en mod tricheur, retournant alors toutes les cartes dans un temps limite.", 1);
  /* Deuxième écran à charger. */
  ChoisirEcran(2);
  ChargerImageFond("../images/fond.png");
  ChargerImage("../images/logo.png", 380, 50, 0, 0, 300, 160);
  /* Permet de cliquer sur la zone interactive, les boutons. */
  CopierZone(1, 0, 0, 0, Maxx(), Maxy(), 0, 0); 
  /* Permet la copie d'une zone de l'écran et de l'afficher,
  dans un autre écran virtuel. */	
  /* - Evite de quitter et permet de poursuivre le programme par la suite,
  avec la boucle principale d'intégritée du programme, se mettant à 0 pour ne pas continuer. 
  */
  while (continuer) {
    SourisPosition();
    selection = interaction(_X, _Y, jouer);
    if (!selection) {
      selection = interaction(_X, _Y, quitter);
      if (selection) { selection++; }
    }
    if (SourisCliquee()) {
      if (selection == 1) { continuer = 0; } 
      else if (selection == 2) {
        /* Permet de sortir du jeu avec le bouton de sortie */
        FermerGraphique();
        exit(0);
      }
    }
  }
  choix(); 
}