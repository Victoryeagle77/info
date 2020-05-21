#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>

volatile typedef void (*Reception)(void *data);

/* Structure definissant un bouton */
typedef struct Button Button;
struct Button{
  XChar2b *text;
  volatile unsigned short int text_width,
    font_ascent, width, height;
  volatile unsigned long border, background, foreground;
  void *data;
  volatile Reception buttonRelease;
};

/* Structure definissant les actions de sortie */
typedef struct sortie Sortie;
struct sortie {
  Display *d;
  XFontStruct *font;
};

extern void menu(void);

#endif
