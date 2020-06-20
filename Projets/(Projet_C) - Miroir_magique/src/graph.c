#include "../header/interface.h"

#define MAX_X 90.0
#define MAX_Y 110.0

/**
* @function e
* Permet de calculer la fonction exponentielle selon :
* @param x : le nombre a calculer 
* @return somme : valeur de l'exponentielle de x.
*/
static const float e(volatile float x){
    /* Initialisation de la serie de Taylor */
    static volatile float somme = 1.0;
    /* Calcul de la somme des n termes */
    for(volatile uint_fast8_t i=MAX_Y; i>0; i--)
        somme = 1 + x*somme/i;
    return somme;
}

/**
* @function tracer_repere
* Permet de tracer un repere orthonorme avec quadrillage des axes,
* segmentations et indice numerotes par echelle de 10.
* @param *d : Disposition de la fenetre
* @param f : Fenetre contenant le repere
* @param abscisse : axe des abscisses
* @param ordonnee : axe des ordonnees
* @param i : segments de l'axe abscisse
* @param j : segments de l'axe des ordonnees
*/
static void tracer_repere(Display *d, const Window f, unsigned int abscisse, 
                            unsigned int ordonnee, volatile short int i, volatile short int j){
    static char str[30];
    /* Tableau de donnee de temperature et humidite */
    extern volatile uint8_t donnee[5];

    /* Axe des abscisses */
    XDrawLine(d, f, GC(d), 0, ordonnee/2, abscisse, ordonnee/2.0);
    /* Legende de l'axe de temperature */
    sprintf(str, "%s%d C (%.1f F)", "Temperature : ", donnee[2], (donnee[2] * 9.0 / 5.0 + 32));
    XDrawString(d, f, style(d, 0xffaaaa), 20, ((1 - (10.0/MAX_Y))*ordonnee/2.0)+100, str, strlen(str));

    for(volatile short int x=-MAX_X+10.0; x<MAX_X; x+=10){
        /* Segmentation de l'axe des abscisses */
        i = (1 + (x/MAX_X)) * abscisse/2.0;
        /* Quadrillage en abscisse */
        XDrawLine(d, f, style(d, 0x102010), i, 0, i, ordonnee/2.0 + 5);
        /* Segments */
        XDrawLine(d, f, style(d, 0xaaaaaa), i, ordonnee/2.0 - 5, i, ordonnee/2.0 + 5);
        /* Indice de l'echelle */
        sprintf(str, "%hd", x);
        XDrawString(d, f, style(d, 0xffaaff), i-5, ordonnee/2.0 + 20, str, strlen(str));
    }

    /* Axe des ordonnees */
    XDrawLine(d, f, GC(d), abscisse/2.0, ordonnee/2.0, abscisse/2.0, 0);
    /* Legende de l'axe de l'humidite */
    sprintf(str, "%s%d%%", "Humidity : ", donnee[0]);
    XDrawString(d, f, style(d, 0xaaccff), abscisse/2+30, 30, str, strlen(str));

    for(volatile uint_fast8_t y=10; y<MAX_Y; y+=10){
        j = (1 - (y/MAX_Y))*ordonnee/2.0;
        /* Quadrillage en abscisse */
        XDrawLine(d, f, style(d, 0x102010), 0, j, abscisse, j);
        /* Segments */
        XDrawLine(d, f, style(d, 0xaaaaaa), abscisse/2.0 - 5, j, abscisse/2.0 + 5, j);
        /* Indice de l'echelle */
        sprintf(str, "%3.hd", y);
        XDrawString(d, f, style(d, 0xffaaff), abscisse/2.0 - 30, j + 5, str, strlen(str));
    }
}

/**
* @function tracer_fonction
* Permet de tracer une fonction et un curseur la localisant
* selon les parametre
* @param donnee[0] : l'humidite en ordonnee
* @param donnee[2] : la temperature en abscisse
* @param *d : Disposition de la fenetre
* @param f : Fenetre contenant le repere
* @param abscisse : axe des abscisses
* @param ordonnee : axe des ordonnees
* @param i : segments de l'axe abscisse
* @param j : segments de l'axe des ordonnees
*/
static void tracer_fonction(Display *d, const Window f, volatile unsigned short int x,
                            unsigned int abscisse, unsigned int ordonnee){
    /* Tableau de donnee de temperature et humidite */
    extern volatile uint8_t donnee[5];

    for(x=0; x<abscisse; x++){
        volatile float a = (x*2.0/abscisse - 1.0)*2.0;
        /* Curseur de differentiel temperature - humidite */
        XDrawPoint(d, f, style(d, 0x808080), ((1.0 + (donnee[2]/MAX_X))*(abscisse/2.0)), x*2);
        XDrawPoint(d, f, style(d, 0x808080), x*2, ((1.0 - (donnee[0]/MAX_Y))*(ordonnee/2.0)));
        /* Courbe de differentiel temperature - humidite */
        XDrawPoint(d, f, style(d, 0x00ff00), ((1.0 + ((e(-a) * donnee[2])/MAX_X))*(abscisse/2.0)), 
                    ((1.0 - ((e(a) * donnee[0])/MAX_Y))*(ordonnee/2.0)));
        /* Courbe maximale du differentiel humidite-temperature */
        XDrawPoint(d, f, style(d, 0xff0000), ((1.0 + ((e(-a) * parametre[0])/MAX_X))*(abscisse/2.0)), 
                    ((1.0 - ((e(a) * parametre[1])/MAX_Y))*(ordonnee/2.0)));
    }
}

/**
* @function tracer_graph
* Permet de tracer le repere du graphique et la fonction,
* et les redimensionner en fonction de la fenetre qui les contient.
*/
extern void tracer_graph(Display *d, const Window f){
    /* Fenetre racine (principale) */
    static Window racine;

    /* Parametres dimensionnels et de coordonnees */
    static int hauteur, largeur;
    static volatile short int x, y;
    static unsigned int abscisse, ordonnee, bordure, profondeur;

    /* Recentrage des elements dans la fenetre racine */
    XGetGeometry(d, f, &racine, &hauteur, &largeur, &abscisse, &ordonnee,
                    &bordure, &profondeur);
    ordonnee *= 1.5;
    
    /*XClearArea(d, f, 0, 0, x/2, y/2, 1); 
    XFlush(d);
    usleep(10000);*/

    /* On trace le repere du graphique */
    tracer_repere(d, f, abscisse, ordonnee, x, y);
    /* On trace la fonction du graphqiue */
    tracer_fonction(d, f, x, abscisse, ordonnee);

    /*XFlush(d);
    sleep(1);*/
}
