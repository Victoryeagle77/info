/* Question 4 : Mandelbrot 
Faites un programme faisant la figure de mandelbrot, 
avec un mode caméra pour visualiser sous différent angles la figures. */

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

static void aire(SDL_Surface *surface, unsigned short int x, unsigned short int y, Uint16 pixel){
  volatile uint8_t octet = surface->format->BytesPerPixel;
  Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * octet;
  switch(octet){
    case 1: *p = pixel; break;
    /* Décalage à droite par 8 en big endian */
    case 3: if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
      p[0] = (pixel >> 8);
      else { p[0] = pixel; }
      break;
    /* Mode de défintion 8 bit */
    case 4: *(Uint16 *)p = pixel; break;
  }
}

/* Gestion de controle des touches sur la fractale */
static void controle(double position, const unsigned short int *couleur, double x, double y,
              SDL_Surface *ecran, int precedent, int actuel, unsigned int tab[600][480], int max){
  static SDL_Event evenement;
  static volatile unsigned short int continuer = 1;
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
          /* Flèche de evenementdroite ==> bouge la caméra vers la droite */
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
        /* Initialiser le niveau de déplacement de la caméra sur la fenetre */
        volatile long double camera = position/200;
        volatile long double x1 = x - (1.5/camera), x2 = x + 1.5/camera;
        volatile long double y1 = y - (1.2/camera), y2 = y + 1.2/camera;
        /* Afficahge verticale et horizontale après déplacement */
        volatile unsigned short int image_x = (x2 - x1) * position;
        volatile unsigned short int image_y = (y2 - y1) * position;
        for(unsigned short int x=0; x<image_x; x++){
          for(unsigned short int y=0; y<image_y; y++){
            long double camera_x = x / position + x1, 
            camera_y = y / position + y1, 
            complexe_x = 0, complexe_y = 0;
            /* Indice de déplacement */
            int i = 0;
            for(; complexe_x*complexe_x + complexe_y*complexe_y <4 && i < max; i++){
              long double tmp = complexe_x;
              complexe_x = complexe_x*complexe_x - complexe_y*complexe_y + camera_x;
              complexe_y = 2*complexe_y*tmp + camera_y;
            }
            if(i < max){ tab[x][y]=couleur[i%150]; }
            else{ tab[x][y]=0; }
          }
        }
    }
    /* Placement d'un curseur sur la position actuelle sur la figure */
    actuel = SDL_GetTicks();
    if (actuel - precedent > 30){
      precedent = actuel;
      for(unsigned short int i = 0; i < 600; i++){
        for(unsigned short int j = 0; j < 480; j++)
          aire(ecran, i, j, tab[i][j]);
      }
    } else { SDL_Delay(30 - (actuel - precedent)); }
    /* Basculement sur l'écran */
    SDL_Flip(ecran);
  }
}

static void coloration(unsigned short int *couleur){
  static unsigned short int rouge = 0, vert = 0, bleu = 0;
  static unsigned short int i = 0;
  /* Luminosité et couleur de la coloration du fond, et de ses éléments */
  for(; i<25; i++){
    couleur[i] = rouge*256*256 + bleu*256 + vert;
    vert+=10;
  }
  for(; i<50; i++){
    couleur[i] = rouge*256*256 + bleu*256  + vert;
    bleu+=10;
  }
  for(; i<75; i++){
    couleur[i] = rouge*256*256 + bleu*256 + vert;
    rouge+=10;
  }
}

void main(void){
  static unsigned short int couleur[150];
  double position = 200;
  double camera = position/200;
  double x1 = -1.5/camera, x2 = 1.5/camera;
  double y1 = -1.2/camera, y2 = 1.2/camera;
  double x = 0, y = 0;
    
  unsigned short int precedent = 0, actuel = 0, max = 150;
  int image_x = (x2 - x1) * position, image_y = (y2 - y1) * position;
  /* Luminosité de la coloration du fond */
  coloration(couleur);
  static unsigned int tab[600][480];
  /* Coordonnées et dimensions de la figure sur l'écran */
  for(int x=0; x < image_x; x++){
    for(int y=0; y < image_y; y++){
      /* Déplacement de l'image par rapport au déplacement de la caméra */
      double camera_x = x / position + x1;
      double camera_y = y / position + y1;
      double complexe_x = 0;
      double complexe_y = 0;
      unsigned short int i = 0;
      for(; complexe_x*complexe_x + complexe_y*complexe_y <4 && i < max; i++){
        double tmp = complexe_x;
        complexe_x = complexe_x*complexe_x - complexe_y*complexe_y + camera_x;
        complexe_y = 2*complexe_y*tmp + camera_y;
      }
      if(i < max){ tab[x][y] = couleur[i%150]; }
    }
  }
  /* Initialise les composants d'écran à placer dans la fen^tre */
  SDL_Surface *ecran = NULL;
  SDL_Event evenement;
  
  SDL_Init(SDL_INIT_VIDEO);
  ecran = SDL_SetVideoMode(600, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  SDL_WM_SetCaption("Mandelbrot", NULL);
  SDL_EnableKeyRepeat(3, 3);
  controle(position, couleur, x, y, ecran, precedent, actuel, tab, max);
  /* Sortie */
  SDL_Quit();
  
  exit(0);
}
