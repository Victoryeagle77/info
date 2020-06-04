#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>

#define GC(d) DefaultGC(d, DefaultScreen(d))

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
    volatile uint_fast8_t validation;
};

/* Structure et type definissant les parametre de sortie */
typedef struct sortie Sortie;
struct sortie {
    Display *d;
    XFontStruct *font;
};

/* Fonctions d'encodage et decodage des caracteres de la police. */
extern const uint_fast8_t encodage(const XChar2b *);
extern const uint_fast8_t decodage(volatile XChar2b *, const uint_fast8_t, 
                                    const char *, const uint_fast8_t);
/* Style graphique a definir sur un element dessiner */
extern const GC style(Display *d, const unsigned int);
/* Definit les parametres de creation d'un bouton. */
extern void creer_bouton(Display *, const Window, const char *, 
                            XFontStruct *, const short int, 
                            const short int, const short int, 
                            const short int, const unsigned int, 
                            const unsigned int, const XContext, const Reception, void *);
extern void creer_graph(Display *, const Window, XFontStruct *, const short int, 
                           const short int, const short int, 
                           const short int, const XContext);
/* Fonctions determinant le changement d'aspect du bouton. */
extern void survol_bouton(const Zone *, const XEvent *);
extern void pression_bouton(const Zone *, const XEvent *);
/* Determine les actions de sortie du bouton "Exit". */
extern void quitter(void *);
/* Fonction tracant le graphique de donnees */
extern void tracer_fonction(Display *, const Window);
/* Fonction principale. */
extern void menu(void);

#endif
