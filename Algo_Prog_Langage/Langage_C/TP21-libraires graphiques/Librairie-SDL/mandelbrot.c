/* Question 4 : Mandelbrot 
Faites un programme faisant la figure de mandelbrot, 
avec un mode caméra pour visualiser sous différent angles la figures. */

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

int coloration(int rouge, int bleu, int vert){
  return rouge*256*256 + bleu*256 + vert;
}
/* Mode de coloration 32 bit */
void aire(SDL_Surface *surface, int x, int y, Uint16 pixel){
  int octel = surface->format->BytesPerPixel;
  Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * octel;
  switch(octel){
    case 1: *p = pixel; break;
      /* Décalage à droite par 16 en big endian */
    case 3: if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
      p[0] = (pixel >> 16) & 0xff;
      else { p[0] = pixel & 0xff; }
      break;
    case 4: *(Uint16 *)p = pixel; break;
  }
}

/* Gestion de controle des touches sur la fractale */
void controle(int continuer, double position, int couleur[150], double x, double y,
SDL_Surface *ecran, int precedent, int actuel, unsigned int tab[600][480], int max){
    SDL_Event evenement;
  while (continuer){
    /* Remplir la forme avec les paramètre evénementielle*/
    SDL_PollEvent(&evenement);
    switch(evenement.type){
      /* Sortie */
      case SDL_QUIT: continuer = 0; break;
      case SDL_KEYDOWN:
        /* Programmation d'actions faites par les touches du clavier */
        switch (evenement.key.keysym.sym){
          /* Flèche de gauche ==> bouge la caméra vers la gauche */
          case SDLK_LEFT: x -= 20/position; break;
          /* Flèche de droite ==> bouge la caméra vers la droite */
          case SDLK_RIGHT: x += 20/position; break;
          /* Flèche du haut ==> bouge la caméra vers le haut */
          case SDLK_UP: y -= 20/position; break;
          /* Flèche du bas ==> bouge la caméra vers le bas */
          case SDLK_DOWN: y += 20/position; break;
          /* Touche p ==> zoomer */
          case SDLK_p: position *= 1.5; break;
          /* Touche m ==> dézoomer */
          case SDLK_m: position /= 1.5; break;
          /* Touche espace ==> fait une rotation */
          case SDLK_SPACE: position *= -1; break;    
        }
        long double camera = position/200;
        long double x1 = x - (1.5/camera), x2 = x + 1.5/camera;
        long double y1 = y - (1.2/camera), y2 = y + 1.2/camera;
        int image_x = (x2 - x1) * position;
        int image_y = (y2 - y1) * position;
        for(int x=0; x<image_x; x++){
          for(int y=0; y<image_y; y++){
            long double camera_x = x / position + x1, 
            camera_y = y / position + y1, 
            complexe_x = 0, complexe_y = 0;
            int i = 0;
            for(; complexe_x*complexe_x + complexe_y*complexe_y <4 && i < max; i++){
              long double tmp = complexe_x;
              complexe_x = complexe_x*complexe_x - complexe_y*complexe_y + camera_x;
              complexe_y = 2*complexe_y*tmp + camera_y;
            }
            if (i < max) { tab[x][y]=couleur[i%150]; }
            else { tab[x][y]=0; }
          }
        }
    }
    actuel = SDL_GetTicks();
    if (actuel - precedent > 30){
      precedent = actuel;
      for (int i = 0; i < 600; i++){
        for (int j = 0; j < 480; j++)
          aire(ecran, i, j, tab[i][j]);
      }
    } else { SDL_Delay(30 - (actuel - precedent)); }
    /* Basculement sur l'écran */
    SDL_Flip(ecran);
  }
}

void main(void){
  int rouge=250, vert=0, bleu=0;
  int i=0, couleur[150];
  double position = 200;
  double camera = position/200;
  double x1 = -1.5/camera, x2 = 1.5/camera;
  double y1 = -1.2/camera, y2 = 1.2/camera;
  double x = 0, y = 0;

  SDL_Surface *ecran = NULL;
  SDL_Event evenement;
    
  int continuer = 1;
  int precedent = 0, actuel = 0;
  int max = 150;
  int image_x = (x2 - x1) * position;
  int image_y = (y2 - y1) * position;
  /* Luminosité de la coloration du fond */
  for (; i<25; i++){
    couleur[i] = coloration(rouge,vert,bleu);
    vert+=10;
  }
  for (; i<50; i++){
    couleur[i] = coloration(rouge,vert,bleu);
    bleu+=10;
  }
  for (; i<75; i++){
    couleur[i] = coloration(rouge,vert,bleu);
    rouge+=10;
  }
  SDL_Init(SDL_INIT_VIDEO);
  ecran = SDL_SetVideoMode(600, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  SDL_WM_SetCaption("Mandelbrot", NULL);
  unsigned int tab[600][480];
  for(int x=0; x < image_x; x++){
    for(int y=0; y < image_y; y++){
      double camera_x = x / position + x1;
      double camera_y = y / position + y1;
      double complexe_x = 0;
      double complexe_y = 0;
      int i = 0;
      for(; complexe_x*complexe_x + complexe_y*complexe_y <4 && i < max; i++){
        double tmp = complexe_x;
        complexe_x = complexe_x*complexe_x - complexe_y*complexe_y + camera_x;
        complexe_y = 2*complexe_y*tmp + camera_y;
      }
      if (i < max) { tab[x][y] = couleur[i%150]; }
    }
  }
  SDL_EnableKeyRepeat(3, 3);
  controle(continuer, position, couleur, x, y, ecran, precedent, actuel, tab, max);
  /* Sortie */
  SDL_Quit();
  exit(0);
}
