#include "menu.h"

int main(void) {
  system("clear");
  InitialiserGraphique();
  /* Création d'une fenètre de longueur 1000px, 
  et de hauteur 700px. */
  CreerFenetre(0, 0, 1000, 700);
  menu(); /* Affiche le menu */
  FermerGraphique();
  return 0;
}