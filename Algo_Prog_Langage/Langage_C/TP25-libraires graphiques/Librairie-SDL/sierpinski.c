/*
Question 3 : Sierpinski
Dessiner le carré de sierpinski
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>

SDL_Surface* ecran; // Définition pointé de la surface à remplir
Uint32 color; // Système coloration 32 bit
// Constante définissant l'action de sortie de la fenêtre  
SDL_Event keypress;

void coloration(int r, int g, int b){
    // Adressage structurelle vers un format de coloration
    color = SDL_MapRGB(ecran->format, r, g, b);
}

void carre(int x, int y, int taille){
    SDL_Surface *pixel = NULL;
    SDL_Rect parametre;
    // structure de la taille en largeur
    parametre.w = taille;
    // structure de la taille en hauteur
    parametre.h = taille;
    parametre.x = x;
    parametre.y = y;
    // SDL_HWSURFACE => Surface de l'écran en hauteur et largeur 
    pixel = SDL_CreateRGBSurface(SDL_HWSURFACE, parametre.w,
    	parametre.h, 32, 0, 0, 0, 0);
    SDL_FillRect(pixel, NULL, color);
    SDL_BlitSurface(pixel, NULL, ecran, &parametre);
    // Libération de l'espace mémoire prise
    SDL_FreeSurface(pixel);
}

void sierpinski(int x, int y, int k){
    int niveau;
    if(k==1) { carre(x + 5/2, y + 5/2, 1); }
    else {
        niveau = pow(3, k-1);
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

int main(int argc, char* argv[]){
    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(26*10,26*10, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Carre de Sierpinski", NULL);
    coloration(0,150,150);
    sierpinski(5,5,5);
    SDL_Flip(ecran);
    while(1){
        SDL_WaitEvent(&keypress);
        if(keypress.type == SDL_QUIT) break;
    }
    SDL_Quit();
    return 0;
}