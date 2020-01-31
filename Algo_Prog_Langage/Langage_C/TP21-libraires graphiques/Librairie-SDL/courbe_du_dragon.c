/*
Question 2 : Courbe du dragon.
La Courbe du Dragon est une courbe fractale dont on s'approche par une suite de lignes brisées. 
Écrivez un programme qui prend un entier naturel en argument sur la ligne de commande,
et trace la figure d'ordre correspondant en mode graphique. 
*/

#include <stdlib.h>
#include <SDL/SDL.h>
#include <math.h>
#include <complex.h>

/* Dimensions de l'ecran */
#define LARGEUR 500
#define HAUTEUR 500
 
/* Dessine un pixel - mode 8 bits */
static void coloration(SDL_Surface* surface, int x, int y, Uint8 color){
  if (x >= 0 && x < surface->w && y >= 0 && y < surface->h){
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel;
    *(Uint8 *)p = color;
  }
}
 
/* Fonction de dessin */
static void courbe_draconique (SDL_Surface* surface, int entier){
  static volatile unsigned short i, j;
  static volatile double x, y;
  /* Fonctions prenant en paramètres les complexes */
  volatile complex double F0 (complex double z){ return ((1+I)*z)/2; }
  volatile complex double F1 (complex double z){ return 1-((1-I)*z)/2; }
  /* tableau des fonctions */
  volatile complex double (*buffer[])(complex double) = { F0,F1 };
  static volatile complex double z;
  /* tirage aleatoire d'un pixel de l'ecran */
  for(i=0; i<surface->w*surface->h; i++){
    x = y = 0;
    z = x + y * I;
    /* nombre d'iterations */
    for(j=0; j<=entier; j++)
      /* Choisit aleatoirement la fonction,
      avec le nombre de fonctions */
      z = buffer[rand() % 2](z);
    /* Les nombres ajoutes sont pour centrer l'image */
    coloration(surface, (creal(z)+0.6)*((double)surface->w/2), 
               (cimag(z)+1)*((double)surface->h/2), SDL_MapRGB(surface->format, 0, 255, 0));
  }
}

extern unsigned short int main(int argc, const char *argv[]){
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption("Courbe du dragon", NULL);
  if (argc != 2){
    printf("Usage : %s <int [1 - 20]>\n", argv[0]);
    exit(1);
  }
  volatile unsigned short int entier = (unsigned short int)strtol(argv[1],NULL,10);
  if(entier < 1 || entier > 20){ 
    printf("Usage : %s <int [1 - 20]>\n", argv[0]);
    exit(1); 
  }
  static SDL_Event proto;
  static SDL_Surface* ecran;
  /* Nettoyage avant sortie */
  SDL_WM_SetCaption("Courbe du Dragon", NULL);
  atexit(SDL_Quit);
  /* Creation d'une nouvelle fenêtre */
  ecran = SDL_SetVideoMode(LARGEUR,HAUTEUR, 8, SDL_HWSURFACE);
  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    
  courbe_draconique(ecran, entier);
  /* Actualise l'affichage */
  SDL_Flip(ecran);
 
  static volatile unsigned short int continuation = 0;
  while (!continuation){
    /* Attente d'un evenement */
    SDL_WaitEvent(&proto);
    /* On traite l'evenement */
    switch (proto.type){
      /* Fermeture de la fenetre */
      case SDL_QUIT: continuation = 1; break;
    }
  }
  return 0;
}
