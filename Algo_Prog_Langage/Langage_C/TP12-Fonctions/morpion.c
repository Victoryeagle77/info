/*
Question 6 : Morpion.
Réaliser un morpion séparé en plusieurs fonction.
*/

#include <stdio.h>
#define NB_LIG 3
#define NB_COL 3

/* Définition d'un type valeur et boolean. */
typedef enum {VIDE, ROND, CROIX} valeur;
typedef enum {FALSE, TRUE} boolean;
valeur grille[NB_LIG][NB_COL]; /* Grille du morpion valeurs possibles VIDE, ROND ou CROIX. */

/* Indique quel sera le prochain joueur à mettre un pion dans la grille ie soit ROND soit CROIX. */
int prochainJoueur = ROND; 

/* Initiliase la grille du morpion à vide */
void initialisation(void) {
  int i, j;
  for (i=0; i<NB_LIG; i++) {
    for (j=0; j<NB_COL; j++) { grille[i][j] = VIDE; }
  }
}

/*
Affiche la grille du morpion.
-> _ indique une case vide.
-> O le pion joueur 1.
-> X le pion jour 2.
*/
void affichage_grille(void) {
  int i, j;
  for (i=0; i<NB_LIG; i++) {
    for (j=0; j<NB_COL; j++) {
      switch (grille[i][j]) {
        case VIDE: printf("_ "); break;
        case ROND: printf("O "); break;
        case CROIX: printf("X "); break;
      }
    }
    putchar('\n'); /* fin de la ligne. */
  }
}

/* Saisie les coordonnees du nouveau pion a mettre sur la grille. */
void grille(void) {
  int ligne, col;
  boolean saisie = FALSE;
  printf("\n******* Morpion *******\n");
  printf("\nChoisir un numero de ligne et de colonne entre 1 et 3.\n");
  /* Conditionnement pour que les cases soit comprise entre 1 et 3. */
  do {
    printf("N de la ligne : ");
    scanf("%d", &ligne);
    printf("N de la colonne : ");
    scanf("%d", &col);
    printf("\n");
  
    if ((ligne > 0) && (ligne <= NB_LIG) && (col > 0) && (col <= NB_COL)) {
      ligne--; 
      /* Enleve 1 pour être compatible avec le tableau ayant des indices de 0 à NB_LIG-1 */
      col--;
      if (grille[ligne][col] != VIDE) 
	        printf("Case deja remplie ! Saisissez une valeur ENTRE 1 ET 3.\n");
      else {
	        saisie = TRUE;
	        grille[ligne][col] = prochainJoueur;
	        if (prochainJoueur == ROND) { prochainJoueur = CROIX; }
	        else { prochainJoueur = ROND; }
      }
    } else
      printf("Indice de case incorrect ! Saisissez une valeur ENTRE 1 ET 3.\n");
  } while (!saisie);  
}

/* Teste si l'un des joueurs a gagné (ligne, colonne ou diagonale remplit de pions semblables). 
- S'il n'y a pas de gagnant, teste que la grille n'est pas pleine. 
- Si elle est pleine, affiche un message indiquant qu'aucun des joueurs a gagné.
- Retourne TRUE si la grille est pleine ou si un joueur a gagné et FALSE sinon.
*/
boolean partie_finie(void) {
  int i,j;
  int victoire; /* Pour connaitre quel est le gagnant, soit CROIX soit ROND. */
  boolean fin = FALSE;
  /* Teste s'il y a un gagnant :
  - Si la case 1,1 est VIDE, cela signifie que les diagonales,
  la ligne 1 et la colonne 1 ne sont pas gagnantes.
  */
  if (grille[1][1] != VIDE) {
    if (/* colonne 1 */ ((grille[0][1] == grille[1][1]) && (grille[1][1] == grille[2][1])) ||
	/* ligne 1 */ ((grille[1][0] == grille[1][1]) && (grille[1][1] == grille[1][2])) ||
	/* diagonale */ ((grille[0][0] == grille[1][1]) && (grille[1][1] == grille[2][2])) ||
	/* autre diag */ ((grille[0][2] == grille[1][1]) && (grille[1][1] == grille[2][0]))) { 
      victoire = grille[1][1]; /* ROND ou CROIX */
      fin = TRUE;
    }
  }

  /* Si la case 0,0 est vide, cela signifie que la ligne 0 et le colonne 0 ne sont pas gagnantes. */
  if ((!fin) && (grille[0][0] != VIDE)) {
    if ( /* ligne 0 */ ((grille[0][0] == grille[0][1]) && (grille[0][1] == grille[0][2])) ||
	 /* colonne 0*/ ((grille[0][0] == grille[1][0]) && (grille[1][0] == grille[2][0]))) {
      victoire = grille[0][0];
      fin = TRUE;
    }
  }

  /* Si la case 2,2 est vide, cela signifie que la ligne 2 et la colonne 2 ne sont gagnantes. */
  if ((!fin) && (grille[2][2] != VIDE)) {
    if ( /* ligne 2 */ ((grille[2][0] == grille[2][1]) && (grille[2][1] == grille[2][2])) ||
	 /* colonne 2 */ ((grille[0][2] == grille[1][2]) && (grille[1][2] == grille[2][2]))) {
      victoire = grille[2][2];
      fin = TRUE;
    }
  }
  if (fin) {
    if (victoire == ROND) { printf(" VICTOIRE !\n"); }
    else { printf(" PERDU !\n"); }
    return TRUE;
  }
  /* Teste si la grille n'est pas pleine. */
  for (i=0; i<NB_LIG; i++) {
    for (j=0; j<NB_COL; j++) {
      /* Au moins une case est vide donc le jeu n'est pas fini. */
      if (grille[i][j] == VIDE) { return FALSE; }
    }
  }
  return TRUE;
}

/* Initialise la grille à vide puis tant que la grille n'est pas pleine,
ou qu'il n'y a pas un gagnant, saisie les pions des joueurs et affiche la grille. */
void main(void) {
  initialisation();
  do {
    grille();
    affichage_grille();
  } while(!partie_finie());
}