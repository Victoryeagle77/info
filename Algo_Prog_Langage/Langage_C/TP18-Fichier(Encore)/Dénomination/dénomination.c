#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/****************  Définition d'une structure ******************/
typedef struct compteMot
{
  char * mot;
  int nbOcc;
}CompteMot;

/********************   Les constantes   ************************/
enum {MAXLONGUEUR = 200};

/* Le tableau où seront rangées les structures de type CompteMot */
CompteMot *tableau;

/* Le nombre de mots*/
int nbMots = 0;

/* La taille du tableau contenant les mots */
int tailleTableau = 50;

char indicage(char *, int *);
char placer(char *, int);

int main(int argc, char **argv){
  char ligne[MAXLONGUEUR], *s, *mot;
  int indice;
  FILE *fichier;
  int i;
  
  if (argc > 1)  fichier = fopen(argv[1], "r");
  else {
      fichier = stdin;
      printf("Indiquez votre texte\n");
  }
  tableau = (CompteMot *) malloc(tailleTableau * sizeof(CompteMot));
  if (tableau == NULL) {
      printf("problème d'allocation\n");
      exit(1);
  }
  while (fgets(ligne, MAXLONGUEUR, fichier) != NULL){
      s = ligne;
      while ((mot = strtok(s, " []{}\\\n{}()*/\"#.;:,\t'?!-<>&%+=")) != NULL) {
           if (!indicage(mot, &indice)) placer(mot, indice);
           else tableau[indice].nbOcc++;
           s = NULL;
        }
  }
  fclose(fichier);
  printf("\n");
  for (i = 0; i < nbMots; i++)
     printf("%s : %d fois\n", tableau[i].mot, tableau[i].nbOcc); 
  return 0;
}

char indicage(char *mot, int *adrIndice){
  int gauche = 0,  droite = nbMots - 1;
  int milieu;
  int compare;
  
  while (gauche <= droite){
      milieu = (gauche + droite) / 2;
      compare = strcmp(mot, tableau[milieu].mot);
      if (compare < 0) droite = milieu - 1;
      else if (compare > 0) gauche = milieu + 1;
      else {
          *adrIndice = milieu;
         return 1;
        }
    }
  *adrIndice = gauche;
  return 0;
}

char placer(char  *mot, int indice){
  int i;
  char *leMot; 

  leMot = (char *) malloc((strlen(mot) + 1)*sizeof(char));
  if (leMot == NULL) {
      printf("problème d'allocation\n");
      exit(1);
    }
  strcpy(leMot, mot); 
  if (nbMots == tailleTableau) {    
      printf("Le tableau est plein, nous reallouons\n");
      tailleTableau += 50;
      tableau = (CompteMot *) realloc(tableau,
                      tailleTableau * sizeof(CompteMot));
      if (tableau == NULL)  {
           printf("problème d'allocation\n");
           exit(1);
       }
  }
  for (i = nbMots; i > indice; i--)  tableau[i] = tableau[i - 1];
  tableau[indice].mot = leMot;
  tableau[indice].nbOcc = 1;
  nbMots++;
  return 1;
}