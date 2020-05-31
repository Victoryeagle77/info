#include "../header/interface.h"
#include "../header/analyse.h"

#define MAX_X 100.0
#define MAX_Y 100.0

extern volatile uint8_t donnee[5];

static const float fonction(const float x, const float y){
    return -x + y;
}

static void tracer_repere(unsigned int abscisse, unsigned int ordonnee, volatile short int i, 
                            volatile short int j, Display *d, const Window f){

    static char str[5];
    volatile GC gc = style(d, "fixed", 0xffccff);

    /* Axe des abscisses */
    XDrawLine(d, f, GC(d), 0, ordonnee/2, abscisse, ordonnee/2);
    
    for(volatile short int x=-MAX_X; x<=0; x+=10){
        /* Segmentation negative de l'axe des abscisses */
        if(x<0){
            i = (1.0 + (x/MAX_X)) * abscisse/2.0 /* + 10 */;
            XDrawLine(d, f, GC(d), i, ordonnee/2-5, i, ordonnee/2+5);
            /* Indice de l'echelle */
            sprintf(str, "%hd", x);
            XDrawString(d, f, gc, i-5, ordonnee/2+20, str, strlen(str));
        }
    }

    for(volatile unsigned short int x=0; x<=MAX_X; x+=10){
        /* Segmentation positive de l'axe des abscisses */
        if(x>0){
            i = (1.0 + (x/MAX_X)) * abscisse/2.0 /* - 10*/;
            XDrawLine(d, f, GC(d), i, ordonnee/2-5, i, ordonnee/2+5);
            /* Indice de l'echelle */
            sprintf(str, "%3.hd", x);
            XDrawString(d, f, gc, i-25, ordonnee/2-10, str, strlen(str));
        }
    }

    /* Axe des ordonnees */
    XDrawLine(d, f, GC(d), abscisse/2, 0, abscisse/2, ordonnee);
    
    for(volatile short int y=-MAX_Y; y<=0; y+=10){
        /* Segmentation negative de l'axe des ordonnees */
        if(y<0){
            j = (1.0 - (y/MAX_Y))*ordonnee/2.0 /*- 10*/;
            XDrawLine(d, f, GC(d), abscisse/2-5, j, abscisse/2+5, j);
            /* Indice de l'echelle */
            sprintf(str, "%hd", y);
            XDrawString(d, f, gc, abscisse/2+15, j+5, str, strlen(str));
        }
    }
    
    for(volatile unsigned short int y=0; y<=MAX_Y; y+=10){
        /* Segmentation positive de l'axe des ordonnees */
        if(y>0){
            j = (1.0 - (y/MAX_Y))*ordonnee/2.0 /*+ 10*/;
            XDrawLine(d, f, GC(d), abscisse/2-5, j, abscisse/2+5, j);
            /* Indice de l'echelle */
            sprintf(str, "%3.hd", y);
            XDrawString(d, f, gc, abscisse/2-40, j+5, str, strlen(str));
        }
    }
}

static void rafraichissement(Display *d, const Window f, volatile unsigned short int largeur, 
                            volatile unsigned short int hauteur){
    static volatile uint8_t tmp[5] = {0};
    static Bool validation;
    for(volatile unsigned short i=0; i<5; i++){
        if(donnee[i] != tmp[i]){
            tmp[i] = donnee[i];
            validation = 1;
        }else{ validation = 0; }
    }
}

extern void tracer_fonction(Display *d, const Window f, volatile unsigned short int largeur, 
                            volatile unsigned short int hauteur){
    static Window racine;

    static int x, y;
    static volatile unsigned short int i, j;
    static unsigned int abscisse, ordonnee, bordure, profondeur;

    XGetGeometry(d, f, &racine, &x, &y, &abscisse, &ordonnee, 
                    &bordure, &profondeur);

    tracer_repere(abscisse, ordonnee, i, j, d, f);

    for(i=0; i<abscisse; i++){
        static char str[2];
        volatile float x1 = (i*2.0/abscisse - 1.0)*MAX_X;
        volatile float x2 = (i*2.0/abscisse - 1.0)*MAX_X;

        /* Legende de la courbe de l'humidite */
        sprintf(str, "%s%d%%", "Humidity : ", donnee[0]);
        XDrawString(d, f, GC(d), abscisse/2+45, ordonnee/2-45, str, strlen(str));
        /* Courbe de l'humidite */
        XDrawLine(d, f, style(d, "fixed", 0xffccaa), i, 
                    (1.0 - (fonction(x1, donnee[0])/MAX_Y))*ordonnee/2.0, i, 
                    (1.0 - (fonction(x2, donnee[0])/MAX_Y))*ordonnee/2.0);

        /* Legende de la courbe de temperature */
        sprintf(str, "%s%d *C", "Temperature : ", donnee[2]);
        XDrawString(d, f, GC(d), 15, ordonnee/2+45, str, strlen(str));
        /*  Courbe de temperature */
        XDrawLine(d, f, style(d, "fixed", 0xaaccff), i, 
                    (1.0 - (fonction(x1, donnee[2])/MAX_Y))*ordonnee/2.0, i, 
                    (1.0 - (fonction(x2, donnee[2])/MAX_Y))*ordonnee/2.0);
    }
    rafraichissement(d, f, largeur, hauteur);
}
