#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

int pi_coloration(int rouge, int bleu, int vert){
    return rouge*256*256 + bleu*256 + vert;
}

void aire(SDL_Surface *surface, int x, int y, Uint16 pixel){
    int octel = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * octel;
    switch(octel){
        case 1: *p = pixel;
            break;
        /* Décalage à droite par 16 en big endian */
        case 3: if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                    p[0] = (pixel >> 16) & 0xff;
            	else { p[0] = pixel & 0xff; }
            break;
        case 4: *(Uint16 *)p = pixel;
            break;
    }
}

int main(int argc, char *argv[]){
    int rouge=250, vert=0, bleu=0;
    int i=0, couleur[150];
    double zoom = 200;
    double camera = zoom/200;
    double x1 = -1.5/camera, x2 = 1.5/camera;
    double y1 = -1.2/camera, y2 = 1.2/camera;
    double x = 0, y = 0;

    SDL_Surface *ecran = NULL;
    SDL_Event evenement;
    
    int continuer = 1;
    int precedent = 0, actuel = 0;
    int max = 150;
    int image_x = (x2 - x1) * zoom;
    int image_y = (y2 - y1) * zoom;
    /* Luminosité de la coloration du fond */
    for (; i<25; i++){
        couleur[i] = pi_coloration(rouge,vert,bleu);
        vert+=10;
    }
    for (; i<50; i++){
        couleur[i] = pi_coloration(rouge,vert,bleu);
        bleu+=10;
    }
    for (; i<75; i++){
        couleur[i] = pi_coloration(rouge,vert,bleu);
        rouge+=10;
    }
    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(600, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Mandelbrot", NULL);
    unsigned int tab[600][480];
    for(int x=0; x < image_x; x++){
        for(int y=0; y < image_y; y++){
            double c_r = x / zoom + x1;
            double c_i = y / zoom + y1;
            double z_r = 0;
            double z_i = 0;
            int i = 0;
            for(; z_r*z_r + z_i*z_i <4 && i < max; i++){
                double tmp = z_r;
                z_r = z_r*z_r - z_i*z_i + c_r;
                z_i = 2*z_i*tmp + c_i;
            }
            if (i < max)
                tab[x][y] = couleur[i%150];
        }
    }
    SDL_EnableKeyRepeat(3, 3);
    while (continuer){
        SDL_PollEvent(&evenement);
        switch(evenement.type){
            case SDL_QUIT: continuer = 0;
                break;
            case SDL_KEYDOWN:
                /* Programmation d'actions faites par les touches du clavier */
                switch (evenement.key.keysym.sym){
                    /* Flèche de gauche ==> bouge la caméra vers la gauche */
                    case SDLK_LEFT: x -= 20/zoom;
                        break;
                    /* Flèche de droite ==> bouge la caméra vers la droite */
                    case SDLK_RIGHT: x += 20/zoom;
                        break;
                    /* Flèche du haut ==> bouge la caméra vers le haut */
                    case SDLK_UP: y -= 20/zoom;
                        break;
                    /* Flèche du bas ==> bouge la caméra vers le bas */
                    case SDLK_DOWN: y += 20/zoom;
                        break;
                    /* Touche espace ==> zoom */
                    case SDLK_SPACE: zoom *= 1.5;
                        break;
                }
                long double camera = zoom/200;
                long double x1 = x - (1.5/camera), x2 = x + 1.5/camera;
                long double y1 = y - (1.2/camera), y2 = y + 1.2/camera;
                int image_x = (x2 - x1) * zoom;
                int image_y = (y2 - y1) * zoom;
                for(int x=0; x<image_x; x++){
                    for(int y=0; y<image_y; y++){
                        long double c_r = x / zoom + x1, 
                        c_i = y / zoom + y1, 
                        z_r = 0, z_i = 0;
                        int i = 0;
                        for(; z_r*z_r + z_i*z_i <4 && i < max; i++){
                            long double tmp = z_r;
                            z_r = z_r*z_r - z_i*z_i + c_r;
                            z_i = 2*z_i*tmp + c_i;
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
        SDL_Flip(ecran);
    }
    SDL_Quit();
    return EXIT_SUCCESS;
}