#include "../header/interface.h"
#include "../header/analyse.h"

#define MAX_X 90.0
#define MAX_Y 110.0

extern volatile uint8_t donnee[5];

/**
* @function fx
*/
static const float fx(volatile float x, volatile float y){
    return -x + y;
}

/**
* @function tracer_repere
* Permet de tracer un repere orthonorme quadrille,
* ou seront presentes les courbe de temperature et humidite.
* @param abscisse : axe des abscisses
* @param ordonnee : axe des ordonnees
* @param i : segments de l'axe abscisse
* @param j : segments de l'axe des ordonnees
* @param *d : Disposition de la fenetre
* @param f : Fenetre contenant le repere
*/
static void tracer_repere(unsigned int abscisse, unsigned int ordonnee, 
                            volatile short int i, volatile short int j, Display *d,
                            const Window f){
    static char str[30];

    /* Axe des abscisses */
    XDrawLine(d, f, GC(d), 0, ordonnee/2, abscisse, ordonnee/2.0);
    /* Legende de l'axe de temperature */
    sprintf(str, "%s%d C (%.1f F)", "Temperature : ", donnee[2], (donnee[2] * 9.0 / 5.0 + 32));
    XDrawString(d, f, style(d, 0xffaaaa), 30, ((1 - (10.0/MAX_Y))*ordonnee/2.0), str, strlen(str));

    for(volatile short int x=-MAX_X; x<MAX_X; x+=10){
        /* Segmentation de l'axe des abscisses */
        if((x>-MAX_X) && (x<MAX_X)){
            i = (1 + (x/MAX_X)) * abscisse/2.0;
            /* Quadrillage en abscisse */
            XDrawLine(d, f, style(d, 0x303030), i, 0, i, ordonnee/2.0 + 5);
            /* Segments */
            XDrawLine(d, f, GC(d), i, ordonnee/2.0 - 5, i, ordonnee/2.0 + 5);
            /* Indice de l'echelle */
            sprintf(str, "%hd", x);
            XDrawString(d, f, style(d, 0xffaaff), i-5, ordonnee/2.0 + 20, str, strlen(str));
        }
    }

    /* Axe des ordonnees */
    XDrawLine(d, f, GC(d), abscisse/2.0, ordonnee/2.0, abscisse/2.0, 0);
    /* Legende de l'axe de l'humidite */
    sprintf(str, "%s%d%%", "Humidity : ", donnee[0]);
    XDrawString(d, f, style(d, 0xaaccff), abscisse/2+30, 30, str, strlen(str));

    for(volatile unsigned short int y=0; y<=MAX_Y; y+=10){
        /* Segmentation positive de l'axe des ordonnees */
        if((y>0) && (y<MAX_Y)){
            j = (1 - (y/MAX_Y))*ordonnee/2.0;
            /* Quadrillage en abscisse */
            XDrawLine(d, f, style(d, 0x303030), 0, j, abscisse, j);
            /* Segments */
            XDrawLine(d, f, GC(d), abscisse/2.0 - 5, j, abscisse/2.0 + 5, j);
            /* Indice de l'echelle */
            sprintf(str, "%hd", y);
            XDrawString(d, f, style(d, 0xffaaff), abscisse/2.0 - 40, j+5, str, strlen(str));
        }
    }
}

extern void tracer_fonction(Display *d, const Window f){
    /* Fenetre racine (principale) */
    static Window racine;

    /* Parametres dimensionnels et de coordonnees */
    static int i, j;
    static volatile short int x, y;
    static unsigned int abscisse, ordonnee, bordure, profondeur;

    /* Recentrage des elements dans la fenetre racine */
    XGetGeometry(d, f, &racine, &i, &j, &abscisse, &ordonnee,
                    &bordure, &profondeur);

    ordonnee *= 1.5;
    /* On trace le repere du graphique */
    tracer_repere(abscisse, ordonnee, x, y, d, f);
    
    for(x=0; x<abscisse; x++){
        volatile float a = (x*2.0/abscisse - 1.0)*MAX_X;
        volatile float y1 = ((1.0 - (fx(a, donnee[0])/MAX_Y))*(ordonnee/2.0));
        /* Courbe d'enthalpie */
        XDrawLine(d, f, style(d, 0x80ccaa), x, y1, x, y1);
    }
}
