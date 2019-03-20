/**** Arthur Chenu ****/

#include "menu.h" /* Appelle du fichier header "menu.h" pour la fonction 
void image_choisie(unsigned short int, unsigned short int) définie dans "menu.c" */

/*
*** Paramètre de la librairie lgraph utilisé ***
--> couleur char[] : Type définit déterminant une couleur.
--> _X : Coordonnées en abscisse relevé au passage du curseur de la souris sur l'écran.
--> _Y : Coordonnées en ordonnée relevé au passage du curseur de la souris sur l'écran.
On compare donc ces deux paramètres avec des couples de coordonnés, à valeur entière, 
définit dans des conditions avec l'opérateur ET.
--> ChargerImageFond(char[]) : Permet de charger une image sur l'ensemble de la fenêtre
en inscrivant en argument son chemin relatif.
--> ChargerImage(char[], int, int, int, int, int, int) : Permet de charger une image,
à partir de son chemin relatif, avec ses dimensions et les coordonnées de sa position sur
une fenêtre graphique.
--> CopierZone(int, int, int, int, int, int, int, int) : Permet de déplacer une zone définie
--> RemplirRectangle(int, int, int, int) : Permet de construire un rectangle avec ses dimensions
et sa position sur la fenêtre.
--> ChoisirEcran(int) : Permet de charger l'écran de fond de la couleur blanche (1) ou noire (0). 
--> CouleurParNom(char[]) : 
--> ChoisirCouleurDessin(couleur) :
--> EcrireTexte(int, int, int, int) :
--> ToucheEnAttente() : Détectera une touche cliquée, tant qu'aucune touche est encore cliquée.
--> Touche() : Défini une touche active.
--> SourisCliquee() : Détecte si on a cliqué sur la souris.
--> SourisPosition() : Relève les coordonnées de la position du curseur de la souris sur l'écran.
*/

couleur coloris;

void modele(unsigned short int img){ /* Affiche l'apperçu de trois images récurentes */
      if(img == 1) 
        ChargerImage("../images/miniature1.png", 800, 250, 0, 0, 150, 150); 
      if(img == 2) 
        ChargerImage("../images/miniature2.png", 800, 250, 0, 0, 150, 150); 
      if(img == 3) 
        ChargerImage("../images/miniature3.png", 800, 250, 0, 0, 150, 150); 
}

    /* Fonction définissant la zone d'un boutton */
void boutton(unsigned short int longueur, unsigned short int hauteur, 
      int joue[longueur][hauteur], int quitte[longueur][hauteur]) {
      unsigned short int clique = 0;
      unsigned short int i;
      for (i = 0; i < longueur; i++) {
        unsigned short int j;
        for (j = 0; j < hauteur; j++) {
          joue[i][j] = clique; /* Boutton pour lancer une partie */
          quitte[i][j] = clique; /* Boutton pour quitter une partie */
          clique++;
        }
      }
}

void melanger(int abscisse, int ordonnee, int tab[abscisse][ordonnee]) {
      unsigned short int res;
      int x, y, x_dimension, y_dimension;
      unsigned short int i;
      for(i = 0; i < abscisse*ordonnee * 100; i++) {
          res = rand() % 4; /* Mélange aléatoire */
          deplacement(abscisse, ordonnee, tab, &x, &y);
          if(res == 0 && y < ordonnee-1) 
            verifie(abscisse, ordonnee, tab, 0, -1, x, y+1);
          else if(res == 1 && y > 0)
           verifie(abscisse, ordonnee, tab, 0, 1, x, y-1);
          else if(res == 2 && x < abscisse-1) 
            verifie(abscisse, ordonnee, tab, -1, 0, x+1, y);
          else if(res == 3 && x > 0) 
            verifie(abscisse, ordonnee, tab, 1, 0, x-1, y);
      }
}

/* Fonction affichant le puzzle d'une image */
void puzzle(int abscisse, int ordonnee, int tab[abscisse][ordonnee], 
      int x_dimension, int y_dimension, int longueur, int hauteur) {
      unsigned short int positionnement, pos_x, pos_y;
      unsigned short int i, j;
      for (i = 0; i < abscisse; i++) {
        for (j = 0; j < ordonnee; j++) {
          if(tab[i][j] == 0) {
            coloris = CouleurParNom("black");
            ChoisirCouleurDessin(coloris);
            RemplirRectangle(i*x_dimension, j*y_dimension, x_dimension, y_dimension);
          }else{
            positionnement = tab[i][j];
            pos_y = positionnement % ordonnee;
            pos_x = positionnement / ordonnee;
            CopierZone(1, 0, pos_x*x_dimension, pos_y*y_dimension, 
              x_dimension, y_dimension, i*x_dimension, j*y_dimension);
          }
        }
      }

      coloris = CouleurParNom("gray");
      ChoisirCouleurDessin(coloris);
      RemplirRectangle(750, 606, 200, 50);

      coloris = CouleurParNom("black");
      ChoisirCouleurDessin(coloris);
      
      EcrireTexte(790, 640, "Abandonner", 1);
      for (i = 1; i < abscisse+1; i++) {
        RemplirRectangle(i*x_dimension, 0, 3, hauteur);
        for (j = 1; j < ordonnee+1; j++)
          RemplirRectangle(0, j*y_dimension, longueur, 3);
      }
}

int clavier(int abscisse, int ordonnee, int grille[abscisse][ordonnee], 
      int x_dimension, int y_dimension, int longueur, int hauteur, int scores) {
      unsigned short int x, y;
      int touche;
      deplacement(abscisse, ordonnee, grille, &x, &y);
      touche = Touche();
      if(touche ==  XK_Down && y < ordonnee-1) 
        scores += verifie(abscisse, ordonnee, grille, 0, -1, x, y+1);
      else if(touche == XK_Up && y > 0) 
        scores += verifie(abscisse, ordonnee, grille, 0, 1, x, y-1);
      else if(touche == XK_Right && x < abscisse-1)  
        scores += verifie(abscisse, ordonnee, grille, -1, 0, x+1, y); 
      else if(touche == XK_Left && x > 0)  
        scores += verifie(abscisse, ordonnee, grille, 1, 0, x-1, y); 
      ChargerImageFond("../images/fond.png");
      puzzle(abscisse, ordonnee, grille, x_dimension, y_dimension, longueur, hauteur);
      return scores;
}

/* Case noire pouvant être déplacée */
int case_vide(int abscisse, int ordonnee, int grille[abscisse][ordonnee], 
      int i, int j, int x_dimension, int y_dimension, int longueur, int hauteur, int scores) {
      scores += verifie(abscisse, ordonnee, grille, -1, 0, i ,j);
      scores += verifie(abscisse, ordonnee, grille, 1, 0, i ,j);
      scores += verifie(abscisse, ordonnee, grille, 0, -1, i ,j);
      scores += verifie(abscisse, ordonnee, grille, 0, 1, i ,j);
      ChargerImageFond("../images/fond.png");
      puzzle(abscisse, ordonnee, grille, x_dimension, y_dimension, longueur, hauteur);
      return scores;
}

/* Permet le déplacement d'une case. */
int deplacement(int abscisse, int ordonnee, int grille[abscisse][ordonnee], 
      int* x, int* y){
      unsigned short int i; 
      for(i = 0; i < abscisse; i++){
        unsigned short int j;
        for(j = 0; j < ordonnee; j++){
          if(grille[i][j] == 0){
            *x = i;
            *y = j;
            return 0;
          }
        }
      }
      return 0;
}

int verifie(int abscisse, int ordonnee, int grille[abscisse][ordonnee], 
      int x_dimension, int y_dimension, int x, int y) {
      unsigned short int res;
      if ((x_dimension+x >= 0 && x_dimension+x < abscisse) && 
        (y_dimension+y >= 0 && y_dimension+y < ordonnee) && 
        grille[x_dimension+x][y_dimension+y] == 0) {
          res = grille[x][y];
          grille[x][y] = grille[x_dimension+x][y_dimension+y];
          grille[x_dimension+x][y_dimension+y] = res;
          return 1;
      } else { return 0; }
}

/* Si la partie est gagnée */
int victoire(int abscisse, int ordonnee, int grille[abscisse][ordonnee], 
      int solution[abscisse][ordonnee]) {
      unsigned short int res = 0;
      unsigned short int i;
      for(i = 0; i < abscisse; i++){
        unsigned short int j;
        for(j = 0; j < ordonnee; j++){
          if (grille[i][j] == solution[i][j]) { res++; }
        }
      }
      return (res == abscisse * ordonnee);
}


void jouer(unsigned short int img, unsigned short int miniature, 
      unsigned short int ligne, unsigned short int colonne) {
      unsigned short int abscisse = ligne;
      unsigned short int ordonnee = colonne;
      /* Pointeurs initialisés à NULL */
      unsigned int *resolution = NULL;
      unsigned int *solution = NULL;
      /* Définition de la taille dans la mémoire des tableaux pointés : 
      "resolution" et "solution" */
      resolution = (unsigned int*) malloc(ordonnee * abscisse * sizeof(unsigned int));
      solution = (unsigned int*) malloc(ordonnee * abscisse * sizeof(unsigned int));

      char nombre_score[12] = {"0\0"};
      char score_design[50] = {"Score :"};

      unsigned short int longueur = miniature, hauteur = miniature;
      unsigned short int x_dimension = longueur/ordonnee, y_dimension = hauteur/abscisse;
      unsigned short int score = 0;
      unsigned short int fin = 0;

      ChargerImageFond("../images/fond.png");
      ChoisirEcran(1);
      if(img == 1) { ChargerImage("../images/img1.png", 0, 0, 0, 0, miniature, miniature); }
      if(img == 2) { ChargerImage("../images/img2.png", 0, 0, 0, 0, miniature, miniature); }
      if(img == 3) { ChargerImage("../images/img3.png", 0, 0, 0, 0, miniature, miniature); }
      ChoisirEcran(0);
      modele(img);

      boutton(ordonnee, abscisse, resolution, solution);
      melanger(ordonnee, abscisse, resolution);
      puzzle(ordonnee, abscisse, resolution, x_dimension, 
        y_dimension, longueur, hauteur);

      while(!fin){
        if(ToucheEnAttente()) {
          score = clavier(ordonnee, abscisse, resolution, x_dimension,
           y_dimension, longueur, hauteur, score);
          /* Conserve l'apperçu de l'image résolue au moment du déplacement des cases */
          modele(img);
      }else if (SourisCliquee()){
        unsigned short int i;
        for (i = 0; i < ordonnee; i++) {
          unsigned short int j;
          for (j = 0; j < abscisse; j++) {
            SourisPosition();
            if (_X > i*x_dimension && _X < i*x_dimension+x_dimension 
              && _Y > j*y_dimension && _Y < j*y_dimension+y_dimension){
              score = case_vide(ordonnee, abscisse, resolution, i, j, 
                x_dimension, y_dimension, longueur, hauteur, score);
              modele(img);
            }
            if(_X > 780 && _X < 780+200 && _Y>600 && _Y < 600 + 50) {
              /* Libération de l'espace mémoire prise par les tableaux resolution et solutions */
              free(resolution);
              free(solution);
              image_choisie(1000, 800);
            }
          }
        }
      }
      coloris = CouleurParNom("black");
      ChoisirCouleurDessin(coloris);
      sprintf(nombre_score, "%d", score); /* Affichage graphique du printf */  
      EcrireTexte(50, 750, score_design, 1);
      EcrireTexte(150, 750, nombre_score, 1);
      fin = victoire(ordonnee, abscisse, resolution, solution);
      } 
      
      coloris = CouleurParNom("gray");
      ChoisirCouleurDessin(coloris);
      RemplirRectangle(770, 68, 200, 50);

      coloris = CouleurParNom("black");
      ChoisirCouleurDessin(coloris);
      EcrireTexte(820, 100, "GAGNER !", 1);

      while(1) {
        if(SourisCliquee()){
          SourisPosition();
          if (_X > 830 && _X < 830 + 200 && _Y > 700 && _Y < 700 + 50)
            image_choisie(1000, 800);
        }
      }
      /* Libération de l'espace mémoire prise par les tableaux "resolution" et "solutions" */
      free(resolution);
      free(solution);
}