/*
Question 2 : Jeu de la vie
Réaliser un programme ou un algorithme de propagation change les coordonnées d'un point,
en fonction des voisins de celui-ci.
*/

#include <stdlib.h>
#include <string.h> 
#include <stdio.h> 
#include <X11/Xlib.h> 

/* Etat initiaux des cellules */
int cellules[8][2] = {
  {-1, 1},{0, 1},{1, 1},
  {-1, 0},{1, 0},{-1,-1},
  {0,-1},{1,-1}
};

void etat(int *actuel, int *suivant, int dimension) {
  int x, y, i, voisin;
  /* Ecrit l'état suivant du tableau */
  for (y=0; y<dimension; y++) {
    for (x=0; x<dimension; x++) {
      voisin = 0;
      for (i=0; i<8; i++) {
        /* Pour générer la grille cellulaire avec la génération des points,
        on effectue le modulo de chaque case par la dimension de l'écran,
        en prenant en compte leur disposition en ordonnée et en abscisse.
        La propagation se fait ainsi en fonction des voisin de chaque point. */
        if (actuel[((y + cellules[i][1] + dimension) % dimension) 
                   * dimension + ((x + cellules[i][0] + dimension) % dimension)]) 
          voisin++;
      }
      suivant[y * dimension + x] = 0;
      if ((actuel[y * dimension + x] && voisin==2) || voisin==3) {
        suivant[y * dimension + x] = 1;
      }
    }
  }
}


int main(int argc, const char *argv[]) {
  int i;
  /* Conversion des arguments en entier non signé */
  unsigned short int dimension;
  if(argc != 2){
    printf("Usage : %s <int>\n", argv[0]);
    return EXIT_FAILURE;
  }
  dimension = (unsigned short int)strtod(argv[1],NULL);
  if((dimension < 100) || (dimension > 700)) {
    printf("Usage : %s <int [100-700]>\n", argv[0]);
    return EXIT_FAILURE;
  }
  /* Mettre en place la fenêtre */
  Display* disposition;
  disposition = XOpenDisplay(NULL);
  int ecran = DefaultScreen(disposition);
  /* Création de la fenêtre avec ses paramètre :
  - D'éléments à disposer
  - De dimension
  - D'écran à remplir */
  Window fenetre = XCreateSimpleWindow(disposition,
                                       RootWindow(disposition, ecran),
                                       0, 0, dimension, dimension, 0,
                                       /* Coloration en blanc du fond et en noir des cellules */
                                       BlackPixel(disposition, ecran), WhitePixel(disposition, ecran));
  /* Ecriture du nom dans la fenetre */
  XStoreName(disposition, fenetre, "Jeu de la Vie");

  XSelectInput(disposition, fenetre, StructureNotifyMask);
  XMapWindow(disposition, fenetre);
  while (1) {
    /* Instauration d'un événement d'action,
    réutilisable pour la création des éléments graphique du jeu de la vie. */
    XEvent evenement;
    XNextEvent(disposition, &evenement);
    if (evenement.type == MapNotify) { break; }
  }
  /* Initialisation de la taille grille en fonction de la dimension */
  size_t taille = sizeof(int) * dimension * dimension;
  /* Allocation dynamique déterminant que actuel et suivant sont définies par [largeur * dimension] */
  int *actuel = (int *)malloc(taille);
  int *suivant = (int *)malloc(taille);
  /* Remplir les cellules de la grille */
  for (i=0; i<dimension*dimension; i++)
    actuel[i] = rand() % 2;

  /* Animation des points par les pixels */
  int x, y, n;
  XPoint points[dimension * dimension];
  while (1) {
    XClearWindow(disposition, fenetre);
    n = 0;
    /* XPoints détermine et traite dans le tableau toutes les cellules,
    dont les points sont encore actif */
    for (y=0; y<dimension; y++) {
      for (x=0; x<dimension; x++) {
        if (actuel[y * dimension + x]) {
          points[n].x = x;
          points[n].y = y;
          n++;
        }
      }
    }
    /* Dessine les points cellulaires */
    XDrawPoints(disposition, fenetre, XCreateGC(disposition, fenetre, 0, NULL), 
                points, n, CoordModeOrigin);
    XFlush(disposition);
    /* Prépare la nouvelle génération suivante à l'actuelle */
    etat(actuel, suivant, dimension);
    /* Copie `suivant` dans `actuel` pour reboucler le processus */
    memcpy(actuel, suivant, taille);
  }
}