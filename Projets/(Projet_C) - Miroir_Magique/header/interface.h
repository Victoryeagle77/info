#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>

#define DefGC(d) DefaultGC(d, DefaultScreen(d))

/* Type definissant les valeurs de retour lors du clique */
volatile typedef void (*Reception)(void *data);

/* Structure et type definissant un bouton */
typedef struct Button Button;
struct Button{
  XChar2b *text;
  volatile unsigned short int text_width,
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

extern void menu(void);

#endif
