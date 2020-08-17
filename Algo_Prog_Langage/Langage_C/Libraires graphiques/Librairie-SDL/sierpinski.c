/*
Question 3 : Sierpinski
Dessiner le carré de sierpinski, en passant sa dimension à la ligne de commande (entre 4 et 5).
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>

SDL_Surface* ecran; /* Définition pointé de la surface à remplir */
Uint16 color; /* Système coloration 16 bit */
/* Constante définissant l'action de sortie de la fenêtre */
SDL_Event keypress;

static void coloration(int r, int g, int b){
  /* Adressage structurelle vers un format de coloration */
  color = SDL_MapRGB(ecran->format, r, g, b);
}

static void carre(int x, int y, int taille){
  SDL_Surface *pixel = NULL;
  SDL_Rect parametre;
  /* structure de la taille en largeur */
  parametre.w = taille;
  /* structure de la taille en hauteur */
  parametre.h = taille;
  parametre.x = x;
  parametre.y = y;
  /* SDL_HWSURFACE => Surface de l'écran en hauteur et largeur */
  pixel = SDL_CreateRGBSurface(SDL_HWSURFACE, parametre.w,
                               parametre.h, 16, 0, 0, 0, 0);
  SDL_FillRect(pixel, NULL, color);
  SDL_BlitSurface(pixel, NULL, ecran, &parametre);
  /* Libération de l'espace mémoire prise */
  SDL_FreeSurface(pixel);
}

static void sierpinski(int x, int y, int k){
  int niveau;
  if(k==1) { carre(x + 3, y + 3, 1); }
  else {
    niveau = pow(3, k-1);
    /* Forme à définir */
    carre(x+niveau, y+niveau, niveau);
    sierpinski(x, y, k-1);
    sierpinski(x, y+niveau, k-1);
    sierpinski(x, y+2*niveau, k-1);
    sierpinski(x+niveau, y+2*niveau, k-1);
    sierpinski(x+2*niveau, y+2*niveau, k-1);
    sierpinski(x+2*niveau, y+niveau, k-1);
    sierpinski(x+2*niveau, y, k-1);
    sierpinski(x+niveau, y, k-1);
  }
} 

extern const unsigned short int main(unsigned short int argc, const char* argv[]){
  int continuer = 1;
  if(argc != 2){
    printf("Usage : %s <int [4 - 6]>\n", argv[0]);
    return EXIT_FAILURE;
  }

  unsigned short int x = (unsigned short int)strtol(argv[1], NULL, 10);

  if(x < 4 || x > 5) { 
    printf("Usage : %s <int [4 - 6]>\n", argv[0]);
    return EXIT_FAILURE;
  }
  /* Initialisation du mode video */
  SDL_Init(SDL_INIT_VIDEO);
  ecran = SDL_SetVideoMode(26*10,26*10, 16, SDL_HWSURFACE);
  SDL_WM_SetCaption("Carre de Sierpinski", NULL);
  coloration(150, 150, 50);
  sierpinski(x, x, x);
  SDL_Flip(ecran);
  /* Boucle évenementielle */
  while(continuer){
    SDL_WaitEvent(&keypress);
    if(keypress.type == SDL_QUIT) {
      continuer = 0;
      return 0;
    }
  }
  SDL_Quit();
  return 0;
}