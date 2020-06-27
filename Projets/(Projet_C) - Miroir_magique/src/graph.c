#include "../header/interface.h"

#define MAX_X 90.0
#define MAX_Y 110.0

static const float e(volatile float x){
    /* Initialisation de la serie de Taylor */
    static volatile float somme = 1.0;
    /* Calcul de la somme des n termes */
    for(volatile uint_fast8_t i=MAX_Y; i>0; i--)
        somme = 1 + x*somme/i;
    return somme;
}

/**** GRAPHIQUE EN TEMPS REEL ****/

static void repere_graph(Display *d, const Window f, unsigned int abscisse, 
                            unsigned int ordonnee, volatile short int i, volatile short int j){
    static char str[30];
    /* Tableau de donnee de temperature et humidite */
    extern volatile uint8_t donnee[5];
    
    XDrawString(d, f, style(d, 0xffffff), 20, 30, "Real Time Analysing Mode", 24);

    /* Axe des abscisses */
    XDrawLine(d, f, GC(d), 0, ordonnee/2.0, abscisse, ordonnee/2.0);
    /* Legende de l'axe de temperature */
    sprintf(str, "%s%d C (%.1f F)", "Temperature : ", donnee[2], (donnee[2] * 9.0 / 5.0 + 32));
    XDrawString(d, f, style(d, 0xffaaaa), 20, ((1 - (10.0/MAX_Y))*ordonnee/2.0)+100, str, strlen(str));

    for(volatile short int x=-MAX_X+10.0; x<MAX_X; x+=10){
        /* Segmentation de l'axe des abscisses */
        i = (1 + (x/MAX_X)) * abscisse/2.0;
        /* Quadrillage en abscisse */
        XDrawLine(d, f, style(d, 0x102010), i, 0, i, ordonnee/2.0 + 5);
        /* Segments */
        XDrawLine(d, f, GC(d), i, ordonnee/2.0 - 5, i, ordonnee/2.0 + 5);
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
        j = (1 - (y/MAX_Y)) * ordonnee/2.0;
        /* Quadrillage en abscisse */
        XDrawLine(d, f, style(d, 0x102010), 0, j, abscisse, j);
        /* Segments */
        XDrawLine(d, f, GC(d), abscisse/2.0 - 5, j, abscisse/2.0 + 5, j);
        /* Indice de l'echelle */
        sprintf(str, "%3.hd", y);
        XDrawString(d, f, style(d, 0xffaaff), abscisse/2.0 - 30, j + 5, str, strlen(str));
    }
}

/**** GRAPHIQUE DE LA BASE DE DONNEES ****/

static void repere_model(Display *d, const Window f, unsigned int abscisse, 
                            unsigned int ordonnee, volatile short int i, volatile short int j){
    static char str[30];
    /* Tableau de donnee de temperature et humidite de la base de donnees */
    extern volatile uint8_t db[3];

    XDrawString(d, f, style(d, 0xffffff), 20, 30, "Database Analysing Mode", 23);

    /* Axe des abscisses */
    XDrawLine(d, f, GC(d), 0, ordonnee/2.0, abscisse/2.0, ordonnee/2.0);
    /* Legende des abscisse */
    XDrawString(d, f, style(d, 0xffccff), 15, ordonnee/2.0 + 30, "Time (in s)", 11);

    for(volatile uint8_t x=10.0; x<(MAX_X-20.0); x+=10){
        /* Segmentation de l'axe des abscisses */
        i = (1 + (-x/(MAX_X-20.0))) * abscisse/2.0;
        /* Quadrillage en abscisse */
        XDrawLine(d, f, style(d, 0x102010), i, 0, i, ordonnee + 5);
        /* Segments */
        XDrawLine(d, f, GC(d), i, ordonnee/2.0 - 5, i, ordonnee/2.0 + 5);
        /* Indice de l'echelle */
        sprintf(str, "%hd", x);
        XDrawString(d, f, style(d, 0xffaaff), i-5, ordonnee/2.0 + 20, str, strlen(str));
    }

    /* Axe des ordonnees */
    XDrawLine(d, f, GC(d), abscisse/2.0, ordonnee, abscisse/2.0, 0);

    for(volatile short int y=-MAX_Y+10.0; y<MAX_Y; y+=10){
        j = (1 - (y/MAX_Y)) * ordonnee/2.0;
        /* Quadrillage en abscisse */
        if(y != 0)
            XDrawLine(d, f, style(d, 0x102010), 0, j, abscisse/2.0, j);
        /* Segments */
        XDrawLine(d, f, GC(d), abscisse/2.0 - 5, j, abscisse/2.0 + 5, j);
        /* Indice de l'echelle */
        sprintf(str, "%3.hd", y);
        XDrawString(d, f, style(d, 0xffaaff), abscisse/2.0 + 20, j + 5, str, strlen(str));
    }

    /* Humidite */
    sprintf(str, "%s%d%%", "Humidity : ", db[0]);
    XDrawString(d, f, style(d, 0xaaccff), 20, ordonnee-20, str, strlen(str));
    /* Temperature */
    sprintf(str, "%s%d C (%.1f F)", "Temperature : ", db[1], (db[1] * 9.0 / 5.0 + 32));
    XDrawString(d, f, style(d, 0xffaaaa), 20, ordonnee-50, str, strlen(str));
}

static void tracer_fonction(Display *d, const Window f, volatile unsigned short int x,
                            unsigned int abscisse, unsigned int ordonnee, const Bool id){
    /* Tableau de donnee de temperature et humidite */
    extern volatile uint8_t donnee[5], db[3];
        
    for(x=0; x<abscisse; x++){
        volatile float a = (x*2.0/abscisse - 1.0) * 2.0;
        if(!(id)){
            /* Curseur de differentiel temperature - humidite */
            XDrawPoint(d, f, style(d, 0x808080), ((1.0 + (donnee[2]/MAX_X))*(abscisse/2.0)), x*2);
            XDrawPoint(d, f, style(d, 0x808080), x*2, ((1.0 - (donnee[0]/MAX_Y))*(ordonnee/2.0)));
            /* Courbe de differentiel temperature - humidite */
            XDrawPoint(d, f, style(d, 0x00ff00), ((1.0 + ((e(-a) * donnee[2])/MAX_X))*(abscisse/2.0)), 
                        ((1.0 - ((e(a) * donnee[0])/MAX_Y))*(ordonnee/2.0)));
            /* Courbe maximale du differentiel humidite-temperature */
            XDrawPoint(d, f, style(d, 0xff0000), ((1.0 + ((e(-a) * parametre[0])/MAX_X))*(abscisse/2.0)), 
                        ((1.0 - ((e(a) * parametre[1])/MAX_Y))*(ordonnee/2.0)));
        }else if(id){
            volatile float a = (x*2.0/abscisse - 1.0) * 2.0;
            XDrawPoint(d, f, style(d, 0xaaccff), ((1.0 + ((e(-a) * -db[2])/(MAX_X-20.0)))*(abscisse/2.0)), 
                        ((1.0 - ((e(a) * db[0])/MAX_Y))*(ordonnee/2.0)));
            XDrawPoint(d, f, style(d, 0xffaaaa), ((1.0 + ((e(-a) * -db[2])/(MAX_X-20.0)))*(abscisse/2.0)), 
                        ((1.0 - ((e(a) * db[1])/MAX_Y))*(ordonnee/2.0)));
        }
    }
}

extern void tracer_graph(Display *d, const Window f, const Bool id){
    /* Fenetre racine (principale) */
    static Window racine;

    /* Parametres dimensionnels et de coordonnees */
    static int hauteur, largeur;
    static volatile short int x, y;
    static unsigned int abscisse, ordonnee, bordure, profondeur;

    /* Recentrage des elements dans la fenetre racine */
    XGetGeometry(d, f, &racine, &hauteur, &largeur, &abscisse, &ordonnee,
                    &bordure, &profondeur);
    /* Graphique en temps reel */
    if(!(id)){
        ordonnee *= 1.5;

        XClearArea(d, f, 0, 0, x/2, y/2, 1); 
        XFlush(d);
        usleep(10000);

        /* On trace le repere du graphique */
        repere_graph(d, f, abscisse, ordonnee, x, y);
        /* On trace la fonction du graphqiue */
        tracer_fonction(d, f, x, abscisse, ordonnee, 0);

        XFlush(d);
        sleep(1);
    /* Graphique de la base de donnees */
    }else if(id){
        abscisse *= 1.5;
        /* On trace le repere du graphique */
        repere_model(d, f, abscisse, ordonnee, x, y);
        /* On trace la fonction du graphqiue */
        tracer_fonction(d, f, x, abscisse, ordonnee, 1);
    }
}
