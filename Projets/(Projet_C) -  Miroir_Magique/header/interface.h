#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
/* Header de la librairie graphique Xlib */
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>

#define GC(d) DefaultGC(d, DefaultScreen(d))

Window zone[2];

/* Definit la courbe maximum du differentiel pression-temperature. */
volatile unsigned short int parametre[2];

/* Type definissant les valeurs de retour lors du clique */
volatile typedef void (*Reception)(void *data);
/* Structure et type definissant un canvas */
typedef struct Zone Zone;
struct Zone{
    XChar2b *texte;
    volatile unsigned short int longueur,
        police, largeur, hauteur;
    volatile unsigned long border, background, foreground;
    void *data;
    volatile Reception relachement;
    volatile uint_fast8_t id;
};
/* Structure et type definissant les parametre de sortie */
typedef struct element Element;
struct element {
    Display *d;
    volatile Window f;
    XFontStruct *font;
};

/**** FONCTIONS UTILITAIRES ****/

/* Fonction retournant la date actuelle et l'affichage */
extern void date(unsigned char *str, const XEvent *e, volatile unsigned short int x);

extern void saisie(XEvent *e, Display *d, const Window f, const uint_fast8_t id);
/* Fonctions d'encodage et decodage des caracteres de la police. */
extern const uint_fast8_t encodage(const XChar2b *);
extern const uint_fast8_t decodage(volatile XChar2b *, const uint_fast8_t, 
                                    const char *, const uint_fast8_t);
/* Determine les actions de sortie du bouton "Exit". */
extern void quitter(void *);

/**** CANVAS ****/

/* Definit les parametres de creation d'un canvas. */
extern void creer_graph(Display *, const Window, const unsigned short int,
                        const unsigned short int, const unsigned short int,
                        const unsigned short int, const unsigned int, 
                           const unsigned int, const XContext);
extern void creer_bouton(Display *, const Window, const char *, 
                          XFontStruct *, const short int,
                          const short int, const short int,
                          const short int, const unsigned int,
                          const unsigned int, const XContext, 
                          const Reception, void *);
/* Fonctions determinant les actions sur un canvas. */
extern void config_canvas(Zone *, const XEvent *);
extern void active_bouton(const Zone *, const XEvent *);
extern void desactive_bouton(const Zone *, const XEvent *);

/**** GRAPHIQUE ****/

/* Fonction tracant le graphique de donnees */
extern void tracer_graph(Display *, const Window);

/**** GRAPHISMES PRINCPAUX ****/
/* Style graphique a definir sur un element dessiner. */
extern const GC style(Display *, const unsigned int);
/* Fonction principale. */
extern void interface(void);

#endif
