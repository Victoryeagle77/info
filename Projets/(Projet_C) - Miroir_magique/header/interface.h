#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
/* Header de la librairie graphique Xlib */
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>

/**** TYPES DE DEFINITION ET STRUCTURES DE DONNEES ****/

#define GC(d) DefaultGC(d, DefaultScreen(d))

/* Definit la courbe maximum du differentiel pression-temperature. */
volatile uint8_t parametre[2];

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
extern void config_canvas(Zone *, const XEvent *);
extern void survol_bouton(const Zone *, const XEvent *, const unsigned int nuance);

/**** GRAPHIQUE ****/

/* Fonction tracant le graphique de donnees */
extern void tracer_graph(Display *, const Window, const Bool id);

/**** GRAPHISMES PRINCPAUX ****/
/* Style graphique a definir sur un element dessiner. */
extern const GC style(Display *, const unsigned int);
/* Fonction principale. */
extern void interface(void);

#endif
