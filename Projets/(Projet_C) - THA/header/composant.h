#ifndef COMPOSANT_H
#define COMPOSANT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
/* Header de la librairie graphique Xlib */
#include <X11/Xlib.h>
#include <X11/Xutil.h>

/**** TYPES DE DEFINITION ET STRUCTURES DE DONNEES ****/

/* Type definissant les valeurs de retour lors du clique */
volatile typedef void (*Reception)(void *data);

/* Structure et type definissant un canvas */
volatile typedef struct{
    XChar2b *texte;
    volatile unsigned short int longueur,
        police, largeur, hauteur;
    volatile unsigned long border, background, foreground;
    void *data;
    volatile Reception relachement;
    volatile uint_fast8_t id;
} Zone;

/**** CANVAS ****/

/* Definit les parametres de creation d'un composant. */
extern void creer_graph(Display *, const Window, const unsigned short int,
                        const unsigned short int, const unsigned short int,
                        const unsigned short int, const unsigned int, 
                        const unsigned int, const XContext);
extern void menu_saisie(Display *, const XEvent *, Window *, volatile unsigned short int);
extern void creer_bouton(Display *, const Window, const char *, XFontStruct *, const short int,
                            const short int, const short int, const short int, const unsigned int,
                            const unsigned int, const XContext, const Reception, void *);
/* Fonctions determinant les actions sur un canvas. */
extern void survol_bouton(const Zone *, const XEvent *, const unsigned int nuance);

#endif
