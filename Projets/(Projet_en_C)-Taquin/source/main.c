/*
*** Paramètres de la librairie "lgraph" utilisés dans le fichier "main.c" ***
- InitialiserGraphique() --> Permet d'initialiser et de préparer une fenêtre graphique.
- CreerFenetre(int, int, int, int) 
--> Permet de construire une fenêtre graphique avec ses dimeension et sa position sur l'écran.
- FermerGraphique() --> Permet de fermer la fenêtre.
*/

/* Appelle de la librairie "lgraph" */
#include "menu.h" /* Appelle du fichier header "menu.h" pour la fonction 
void image_choisie(unsigned short int, unsigned short int) définie dans "menu.c" */

int main(void) {
  /* Initialisation graphique de la fenêtre principale contenant le menu,
  avec ses dimensions en longueur et hauteur. */
  system("clear"); /* Nettoyage des informations dans le shell */
  unsigned short int longueur=1000, hauteur=800;
  InitialiserGraphique();
  CreerFenetre(100, 100, longueur, hauteur);
  /* Permet d'afficher une image en fonction de longueur et la hauteur */
  image_choisie(longueur, hauteur); 
  FermerGraphique();
  return 0;
}
