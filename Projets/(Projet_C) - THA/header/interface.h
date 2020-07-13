#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
/* Header de la librairie graphique Xlib */
#include <X11/Xlib.h>

/**** TYPES DE DEFINITION ****/

#define GC(d) DefaultGC(d, DefaultScreen(d))

/**** GRAPHIQUE ****/

/* Fonction tracant le graphique de donnees */
extern void tracer_graph(Display *, const Window, const Bool id);

/**** GRAPHISMES PRINCPAUX ****/
/* Style graphique a definir sur un element dessiner. */
extern const GC style(Display *, const unsigned int);
/* Fonction principale. */
extern void interface(void);

#endif
