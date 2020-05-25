#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>

#define GC(d) DefaultGC(d, DefaultScreen(d))

/* Type definissant les valeurs de retour lors du clique */
volatile typedef void (*Reception)(void *data);

/* Structure et type definissant un bouton */
typedef struct Button Button;
struct Button{
  XChar2b *texte;
  volatile unsigned short int longueur,
    font_ascent, largeur, hauteur;
  volatile unsigned long border, background, foreground;
  void *data;
  volatile Reception relachement;
};

/* Structure et type definissant les actions de sortie */
typedef struct sortie Sortie;
struct sortie {
  Display *d;
  XFontStruct *font;
};

/* Fonctions d'encodage et decodage des caracteres. */
extern const uint_fast8_t encodage(const XChar2b *);
extern const uint_fast8_t decodage(volatile XChar2b *, const uint_fast8_t, 
                                    const char *, const uint_fast8_t);
/* Determine les actions de sortie du bouton "Exit". */
extern void quitter(void *);
/* Definit les parametres de creation d'un bouton. */
extern void creer_bouton(Display *, const Window, const char *, 
                           XFontStruct *, const short int, 
                           const short int, const short int, 
                           const short int, const unsigned int, 
                           const unsigned int, const unsigned int, 
                           const XContext, const Reception, void *);
/* Fonctions determinant le changement d'aspect du bouton. */
extern void survol_bouton(const Button *, const XEvent *);
extern void pression_bouton(const Button *, const XEvent *);
/* Fonction principale. */
extern void menu(void);

#endif
