/* Question 1 : Fourmis de Langton */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>

#define HAUT 0
#define GAUCHE 1
#define DROITE 2
#define BAS 3

// Décalration de constantes de coordonnées
int const LARGEUR_CASE = 30, HAUTEUR_CASE = 30;
int const LARGUEUR_FOURMIS = 30, HAUTEUR_FOURMIS = 30;
int const CASE_GRILLE_X = 11, CASE_GRILLE_Y = 11;

 /* Définition de tous les composants nécessaires :
  - La disposition des éléments.
  - La fenetre.
  - Le canvas : zone d'interactivité avec la fourmis.
  - Les couleurs du fond, du tracé de la fourmis et de la fourmis elle-même.
  - Les données de direction
  - La taille d'une cellule (case) en abscisse et en ordonnée
*/
void dessiner(Display * const disposition, Window const fenetre,
                  /* Etat d'avancement des cellules (cases) du tableau de coordonnées */
                  GC const canvas, int etat_cellule[CASE_GRILLE_X][CASE_GRILLE_Y],
                  XColor const X11_argent, XColor const X11_gris, XColor const X11_rouge, 
                  int const direction, int const CASE_X, int const CASE_Y) {
  // Nettoyage de la fenetre par rapport à la disposition
  XClearWindow(disposition, fenetre);
  for (int i = 0; i < CASE_GRILLE_X; i++) {
    for (int j = 0; j < CASE_GRILLE_Y; j++) {
      // Remplir le fond
      XSetForeground(disposition, canvas,
                     (etat_cellule[i][j] == 0) ? X11_gris.pixel : X11_argent.pixel);
      // Remplir la forme (le rectangle)
      XFillRectangle(disposition, fenetre, canvas, i * LARGEUR_CASE,
                     j * HAUTEUR_CASE, LARGEUR_CASE, HAUTEUR_CASE);
    }
  }

  XSetForeground(disposition, canvas, X11_rouge.pixel);
  int position_x, position_y;
  switch (direction) {
    // Direction vers le haut
    case HAUT:
      	position_x = CASE_X * LARGEUR_CASE +
            0.5 * (LARGEUR_CASE - LARGUEUR_FOURMIS);
      	position_y = CASE_Y * HAUTEUR_CASE;
    break;
    // Direction vers la gauche
    case GAUCHE:
      	position_x = CASE_X * LARGEUR_CASE;
      	position_y = CASE_Y * HAUTEUR_CASE +
            0.5 * (HAUTEUR_CASE - HAUTEUR_FOURMIS);
    break;
    // Direction vers la droite
    case DROITE:
      	position_x = (CASE_X + 1) * LARGEUR_CASE - LARGUEUR_FOURMIS;
     	position_y = CASE_Y * HAUTEUR_CASE +
            0.5 * (HAUTEUR_CASE - HAUTEUR_FOURMIS);
    break;
    // Direction vers le bas
    case BAS:
      	position_x = CASE_X * LARGEUR_CASE +
            0.5 * (LARGEUR_CASE - LARGUEUR_FOURMIS);
      	position_y = (CASE_Y + 1) * HAUTEUR_CASE - HAUTEUR_FOURMIS;
    break;
  }
  /* Remplissage d'un rectangle et ceci :
  Permet de réadapter la fenètre en fonction des constantes */
  XFillRectangle(disposition, fenetre, canvas, 
    position_x, position_y, LARGUEUR_FOURMIS, HAUTEUR_FOURMIS);
  XFlush(disposition);
  // FLuidité de l'animation
  usleep(10000);
}

int main(void){
  Display * const disposition = XOpenDisplay(NULL);
  int const x11Screen = DefaultScreen(disposition);
  Window const fenetre = XCreateSimpleWindow(disposition, 
    RootWindow(disposition, x11Screen), 0, 0, 
    LARGEUR_CASE * CASE_GRILLE_X, HAUTEUR_CASE * CASE_GRILLE_Y, 1,
    BlackPixel(disposition, x11Screen), WhitePixel(disposition, x11Screen));

  XSelectInput(disposition, fenetre, ExposureMask | KeyPressMask);
  XMapWindow(disposition, fenetre);
  
  Colormap const coloration = DefaultColormap(disposition, 0);
  GC const canvas = XCreateGC(disposition, fenetre, 0, 0);

  XColor X11_argent;
  XColor X11_gris;
  XColor X11_rouge;
  /* Coloration correpondant aux constantes */
  // Gris Foncé
  XParseColor(disposition, coloration, "#555555", &X11_gris);
  // Gris clair
  XParseColor(disposition, coloration, "#999999", &X11_argent);
  // Rouge 
  XParseColor(disposition, coloration, "#F00000", &X11_rouge);
  // Coloration de map
  XAllocColor(disposition, coloration, &X11_gris);
  XAllocColor(disposition, coloration, &X11_argent);
  XAllocColor(disposition, coloration, &X11_rouge);

  int etat_cellule[CASE_GRILLE_X][CASE_GRILLE_Y];
  for (int i = 0; i < CASE_GRILLE_X; i++) {
    for (int j = 0; j < CASE_GRILLE_Y; j++) 
      etat_cellule[i][j] = 1;
  }
  // Centrer la fourmis
  int CASE_X = CASE_GRILLE_X / 2;
  int CASE_Y = CASE_GRILLE_Y / 2;
  // Donne la direction à la fourmis 
  int direction = GAUCHE;
  // Dessiner et mettre en pause
  dessiner(disposition, fenetre, canvas, etat_cellule, 
    X11_argent, X11_gris, X11_rouge, 
    direction, CASE_X, CASE_Y);
  // Commencement de l'animation
  int x = 0;
  while (1) {
    /* Avance seulement la simulation de HAUT vers le nombre
     spécifié du temps des étapes franchies */
    if (x < 200) {
      // Rotation
      switch (direction) {
        case HAUT:
            direction = (etat_cellule[CASE_X][CASE_Y] == 0) 
            ? GAUCHE : DROITE;
        break;
        case GAUCHE:
            direction = (etat_cellule[CASE_X][CASE_Y] == 0) 
            ? BAS : HAUT;
        break;
        case DROITE:
            direction = (etat_cellule[CASE_X][CASE_Y] == 0) 
            ? HAUT : BAS;
        break;
        case BAS:
            direction = (etat_cellule[CASE_X][CASE_Y] == 0) 
            ? DROITE : GAUCHE;
        break;
      }
      dessiner(disposition, fenetre, canvas, etat_cellule, 
        X11_argent, X11_gris, X11_rouge, 
        direction, CASE_X, CASE_Y);
      
      etat_cellule[CASE_X][CASE_Y] =
        (etat_cellule[CASE_X][CASE_Y] == 0) ? 1 : 0;

      dessiner(disposition, fenetre, canvas, etat_cellule, 
        X11_argent, X11_gris, X11_rouge, 
        direction, CASE_X, CASE_Y);
  
      // Déplacement
      switch (direction) {
        // Recule de une case en case vers la haut
        case HAUT: CASE_Y--;
          break;
        // Recule de une case en case vers la gauche
        case GAUCHE: CASE_X--;
          break;
        // Avance de une case en case vers la droite
        case DROITE: CASE_X++;
          break;
        // Avance de une case en case vers le bas  
        case BAS: CASE_Y++;
          break;
      }
      dessiner(disposition, fenetre, canvas, etat_cellule, 
        X11_argent, X11_gris, X11_rouge, 
        direction, CASE_X, CASE_Y);
      x++;
    }
  } 
  return 0;
}