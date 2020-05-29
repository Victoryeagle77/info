#include "../header/interface.h"
#include "../header/analyse.h"

#define MAX_X 100.0
#define MAX_Y 100.0

extern volatile uint8_t donnee[5];

static void tracer_repere(unsigned int abscisse, unsigned int ordonnee, volatile short int i, 
                    volatile short int j, Display *d, Window f){
    static char str[5];
    /* Axe des ordonnees */
    sprintf(str, "%s%d%%", "Humidity : ", donnee[0]);
    XDrawString(d, f, GC(d), abscisse/2+25, 20, str, strlen(str));
    for(volatile short int x=-MAX_X; x<=MAX_X; x+=10){
        i = (1.0 + (x/MAX_X)) * abscisse/2.0;
        XDrawLine(d, f, GC(d), i, ordonnee/2-5, i, ordonnee/2+5);
        if((x<0) || (x>0)){
            sprintf(str, "%hd", x);
            XDrawString(d, f, GC(d), i, ordonnee/2-5, str, strlen(str));
        }
    }
    /* Axe des abscisses */
    sprintf(str, "%s%d *C or %.1f *F", "Temperature : ",
               donnee[2], (donnee[2] * 9.0 / 5.0 + 32));
    XDrawString(d, f, GC(d), 5, ordonnee/2+25, str, strlen(str));
    for(volatile short int y=-MAX_Y; y<=MAX_Y; y+=10){
        j = (1.0 - (y/MAX_Y))*ordonnee/2.0;
        XDrawLine(d, f, GC(d), abscisse/2-5, j, abscisse/2+5, j);
        if((y<0) || (y>0)){
            sprintf(str, "%hd", y);
            XDrawString(d, f, GC(d), abscisse/2+5, j, str, strlen(str));
        }
    }
}

static void config_graph(Display *d, Window racine, volatile unsigned short int x, 
                            volatile unsigned short int y){
    racine = XCreateSimpleWindow(d, racine, x/2+200, y/2+50, x/2+100, 
                                    y/2+100, 2, 0xaa00aa, 0);
    /* Dire au serveur d'affichage quel type d'événements nous voulons avoir */
    XSelectInput(d, racine, ExposureMask | KeyPressMask);
    /* Afficher la fenetre sur l'ecran. */
    XMapWindow(d, racine);
}

extern void tracer_fonction(Display *d, Window f, volatile unsigned short int largeur, 
                            volatile unsigned short int hauteur){
    static Window racine;

    static int x, y;
    static volatile unsigned short int i, j;
    static unsigned int abscisse, ordonnee, bordure, profondeur;

    XGetGeometry(d, f, &racine, &x, &y, &abscisse, &ordonnee, 
                    &bordure, &profondeur);
    XDrawLine(d, f, GC(d), 0, ordonnee/2, abscisse, ordonnee/2);
    XDrawLine(d, f, GC(d), abscisse/2, 0, abscisse/2, ordonnee);

    for(i=0; i<abscisse; i++){
        volatile short int k = i+10;
        volatile float x1 = (i*2.0/abscisse - 1.0)*MAX_X;
        j = (1.0 -((x1*donnee[0])/MAX_Y))*ordonnee/2.0;

        volatile float x2 = (k*2.0/abscisse - 1.0)*MAX_X;
        volatile short int h2 = (1.0 -((x2*donnee[0])/MAX_Y))*ordonnee/2.0;

        XDrawLine(d, f, GC(d), i, j, k, h2);
    }
    
    tracer_repere(abscisse, ordonnee, i, j, d, f);
    config_graph(d, f, largeur, hauteur);
}
