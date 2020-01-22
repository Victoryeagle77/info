/* Question 1 : Le Flocon de Koch 
Il s'agit d'une figure fractale dont on s'approche par une série de polygones. 
Le flocon de l'ordre 0 est un simple triangle équilatéral. Le flocon de l'ordre 1 est une étoile à 6 branches etc. 
On passe d'un ordre à un autre en «brisant» chaque segment en quatre parties pour former une pointe.

On va représenter un flocon par une liste chaînée où chaque maillon contient les coordonnées d'un point. 
Écrivez une fonction qui crée un flocon de l'ordre 0, et une fonction qui affiche un flocon. 
Vérifiez que ces fonctions marchent, puis ajoutez une fonction qui prend un flocon d'ordre n,
et qui renvoie un flocon d'ordre n+1. 
Servez-vous-en pour afficher un flocon d'ordre 10.

ON UTILISE LA LIBRAIRE SDL COMME CECI
Compilation : gcc koch.c -lSDL
*/

#include <SDL/SDL.h>

/* Nombre de transformation de la fractale */
#define TRANSFORMATION 10
/* Vitesse d'animation */
#define TRANSITION 1500.

#define MAX(a, b) (((a)>(b))?(a):(b))
 
void figure(int x, int y, Uint8 coloration){
  /* Définition de la largeur des segments */
  SDL_Rect forme = {x, y, 2, 2};
  SDL_FillRect(SDL_GetVideoSurface(), &forme, coloration);
}
/* Mode 8 bit pour la colorationoration RGB */
void modelisation_figure(int x1, int y1, int x2, int y2, Uint8 coloration){
  double x = x1, y = y1;
  double i = x2 - x1, j = y2 - y1;
  int axe = MAX((((i)<0)?-(i):(i)), (((j)<0)?-(j):(j)));
  i /= axe; j /= axe;
  /* Diminue */
  for(; axe >= 0; axe--){
    figure((unsigned int)x, (unsigned int)y, coloration);
    x += i; y += j;
  }
}

/* Dessin récursif de la fonction point par point */
void fractale(int x1, int y1, int x2, int y2, 
              int niveau, int coloration, float deplacement){
  if(niveau > 0){
    /* Relève les coordonnées et les divises */
    int abscisse = (2*x1 + x2)/3 + ((x1 + 2*x2)/3 - (2*x1 + x2)/3)
      /2 + ((y1 + 2*y2)/3 - (2*y1 + y2)/3)*1.732 /2;
    int ordonnee = (2*y1 + y2)/3 - ((x1 + 2*x2)/3 - (2*x1 + x2)/3)
      *1.732/2 + ((y1 + 2*y2)/3 - (2*y1 + y2)/3) /2;
    if(niveau == 1){
      /* Récupère les coordonnées de chaque vecteurs de déplacement */
      abscisse = (x1 + x2)*(1 - deplacement)/2 + abscisse*deplacement;
      ordonnee = (y1 + y2)*(1 - deplacement)/2 + ordonnee*deplacement;
    }
    /* Récursion permettant la transformation de chaque figure */
    fractale(x1, y1, (2*x1 + x2)/3, (2*y1 + y2)/3, 
             niveau-1, coloration, deplacement);
    fractale((2*x1 + x2)/3, (2*y1 + y2)/3, abscisse, ordonnee, 
             niveau-1, coloration+1, deplacement);
    fractale(abscisse, ordonnee, (x1 + 2*x2)/3, (y1 + 2*y2)/3, 
             niveau-1, coloration+1, deplacement);
    fractale((x1 + 2*x2)/3, (y1 + 2*y2)/3, x2, y2,
             niveau-1, coloration, deplacement);
  } else
    /* Configure le buffer vidéo avec les paramètres de la figure */
    modelisation_figure(x1, y1, x2, y2, SDL_MapRGB(SDL_GetVideoSurface()->format, 
        (255 * coloration/TRANSFORMATION), (255 * niveau/TRANSFORMATION), 
        255 - (255 * coloration/TRANSFORMATION)));
}

void main(void){
  system("clear");
  SDL_Surface *video = NULL;
  SDL_Event evenement;
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption("Flocon de Koch", NULL);
  /* Définition de l'écran en mode vidéo (buffer de frames défilantes) */
  video = SDL_SetVideoMode(640, 500, 32, SDL_DOUBLEBUF | SDL_HWSURFACE);
  while(1){
    while(SDL_PollEvent(&evenement))
      if(evenement.type == SDL_QUIT){
        /* sorite */
        SDL_Quit(); 
        exit(0);
      }
    /* Frames d'animation */
    int niveau = SDL_GetTicks()/TRANSITION;
    if(niveau <= TRANSFORMATION){
      float deplacement = SDL_GetTicks()/TRANSITION - niveau;
      /* Coloration du rectangle de fond consitituant la fenêtre */
      SDL_FillRect(video, NULL, SDL_MapRGB(video->format, 0, 0, 0));
      fractale(320, 60, 520, 340, (niveau+1), 0, deplacement);
      fractale(520, 340, 120, 340, (niveau+1), 0, deplacement);
      fractale(120, 340, 320, 60, (niveau+1), 0, deplacement);
      SDL_Flip(video);
    }
  }
}
