/* Question 5 : Cases. 
Compilez (avec l'option -lgraph) et testez-le pas à pas. 
Vous constaterez que les cases du bord gauche réagissent lorsqu'on clique juste à côté (à l'extérieur de la grille). 
Utilisez le débogueur pour identifier et régler le problème. 
*/

// fichier debogueur2.c : exemple a deboguer 

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#define ESPACE        40    /* espace autour de la grille  */
#define CASE          20    /* cote d'une case             */
#define TAILLE_MAX    20    /* taille maximum de la grille */
#define TAILLE_MIN     2    /* taille minimum de la grille */

#define FOND_R       190    /* composante rouge du fond    */
#define FOND_G       140    /* composante verte du fond    */
#define FOND_B       190    /* composante bleue du fond    */

#define CASE_R       160    /* composante rouge des cases  */
#define CASE_G       210    /* composante verte des cases  */
#define CASE_B       160    /* composante bleue des cases  */

/* fonction demandant la taille de la grille */
/* il n'y a pas d'erreur ici */
unsigned short demander_taille() {
  unsigned short taille = 0;
  int scan_ok = 0;

  while(1) {
    printf("Entrez la taille de la grille ");
    printf("(entre %d et %d) : ", TAILLE_MIN, TAILLE_MAX);

    scan_ok = scanf("%hu", &taille) == 1;

    if (scan_ok&&(taille>=TAILLE_MIN)&&(taille<=TAILLE_MAX))
      return taille;

    printf("Réponse erronée !\n");

    while (getchar() != '\n');
  }
}

/* fonction qui dessine une case */
/* il n'y a pas d'erreur ici */
void dessin_case(unsigned short l, unsigned short c, couleur coul) {
  ChoisirCouleurDessin(coul);
  RemplirRectangle(ESPACE+c*CASE, ESPACE+l*CASE,
                   CASE-1, CASE-1);
}

/* fonction qui ouvre et dessine la fenetre */
/* il n'y a pas d'erreur ici */
void dessin_debut(unsigned short taille, couleur *c_fond, couleur *c_case) {
  unsigned short i,j;
  int cote = ESPACE*2 + CASE*taille; /* taille de la fenetre */
  InitialiserGraphique();
  CreerFenetre((Maxx()-cote)/2, (Maxy()-cote)/2, cote, cote);
  /* couleur du fond */
  *c_fond = CouleurParComposante(FOND_R, FOND_G, FOND_B);
  EffacerEcran(*c_fond);
  /* couleur des cases */
  *c_case = CouleurParComposante(CASE_R, CASE_G, CASE_B);
  for(i=0; i<taille; i++)
    for(j=0; j<taille; j++)
      dessin_case(i, j, *c_case);
}

/* fonction principale */
int main(void) {
  unsigned short taille, *grille = NULL;
  int ligne, colonne;
  couleur c_fond, c_case;
  /* obtention de la taille */
  taille = demander_taille();
  /* reservation de la grille avec initialisation */
  grille = (unsigned short*) calloc(taille*taille, sizeof(unsigned short));
  /* ouverture de la fenetre */
  dessin_debut(taille, &c_fond, &c_case);
  /* boucle de changement de la grille */
  while(!ToucheEnAttente())
    if (SourisCliquee()) {
      /* calcul de la case concernee */
      colonne = (_X - ESPACE)/CASE;
      ligne   = (_Y - ESPACE)/CASE;
      /* si la case est dans la grille */
      if ((colonne>=0)&&(colonne<taille)&&
          (ligne>=0)&&(ligne<taille))
        if (grille[taille*ligne + colonne]) {
          grille[taille*ligne + colonne] = 0;
          dessin_case(ligne, colonne, c_case);
        } else {
          grille[taille*ligne + colonne] = 1;
          dessin_case(ligne, colonne, c_fond);
        }
    }

  /* liberation de la memoire de la grille */
  free(grille);
  /* fermeture de la fenetre */
  FermerGraphique();
  return EXIT_SUCCESS;
}

/* fin du fichier debogueur2.c */

/******* DEBOGUAGE *******/

/*
--> Manuel <--
-> breakpoint :    b   <Numéro de la ligne>
Permet de marquer une ligne et de faire suivre l'exécution,
à partir de celle-ci.
-> run :           r
Permet de lancer un programme dans (gdb)
-> print :         p   <Nom de variables>
Permet d'afficher la valeur d'une variable,
à n'importe quel endroit d'un programme après le breakpoint.
-> backtrace :     bt 
-> list :          l   <Numéro de la ligne>
Permet d'afficher une liste de lignes en inscrivant le numéro de la dernière.
-> step :          s
Permet la lecture ligne par ligne depuis le breakpoint.

En lançant le programme, on constate :
- Que les cases du bord gauche réagissent quand on clique, l'équivalent d'une case sur le côté gauche.
- Et les cases du bord supérieur réagissent quand on clique, l'équivalent d'une case au dessus.
*/