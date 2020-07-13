#ifndef UTILITAIRE_H
#define UTILITAIRE_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
/* Header de la librairie graphique Xlib */
#include <X11/Xlib.h>
#include <X11/Xutil.h>

/**** TYPES DE DEFINITION ET STRUCTURES DE DONNEES ****/

/* Definit la courbe maximum du differentiel pression-temperature. */
volatile uint8_t parametre[2];

/* Structure et type definissant les parametre de sortie */
typedef struct{
    Display *d;
    volatile Window f;
    XFontStruct *font;
} Element;

/**** FONCTIONS UTILITAIRES ****/

/* Fonction retournant la date actuelle et l'affichage. */
extern uint_fast8_t *date(void);
/* Fonctions d'encodage et decodage des caracteres de la police. */
extern const uint_fast8_t encodage(const XChar2b *);
extern const uint_fast8_t decodage(volatile XChar2b *, const uint_fast8_t, 
                                    const char *, const uint_fast8_t);
/* Fonction formatant la saisie et l'affichant dans des zones. */
extern void saisie(Display *d, XEvent *e, const uint_fast8_t id);
/* Determine les actions de sortie du bouton "Exit". */
extern void quitter(void *);

#endif
