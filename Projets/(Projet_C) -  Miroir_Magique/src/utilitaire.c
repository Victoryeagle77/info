#include "../header/interface.h"

/* Definit la courbe maximum du differentiel pression-temperature. */
extern volatile unsigned short int parametre[2];

/**
* @function *date
* Permet de relever la date actuelle :
* Annee, moi, jour, heures et minutes.
* Le tout est converti en chaine de caractere dans et l'affiche.
* @param *str : Chaine de caracteres a afficher
* @param *e : Evenement d'affichage
* @param x : Taille de l'ecran en largeur
*/
extern void date(unsigned char *str, const XEvent *e, volatile unsigned short int x){
    time_t temps = time(NULL);
    volatile struct tm tm = *localtime(&temps);
    sprintf(str, "%02d/%02d/%d - %02d:%02d", tm.tm_mday, 
                tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);
    XDrawString(e->xany.display, e->xany.window, GC(e->xany.display), 
                (x/2)-90, 130, str, 18);
}

extern const uint_fast8_t encodage(const XChar2b *texte){
   static volatile uint_fast8_t i=0;
   for(i=0; (texte[i].byte1) || (texte[i].byte2); i++);
   return i;
}

extern const uint_fast8_t decodage(volatile XChar2b *affiche, 
                                    const uint_fast8_t debordement, 
                                    const char *saisie, const uint_fast8_t chaine){
   static volatile uint_fast8_t i, j;
   for(i=0, j=0; (i<chaine) && (j<debordement); i++){
      if(saisie[i] < 128){
         affiche[j].byte1 = 0;
         affiche[j].byte2 = saisie[i]; 
         j++;
      }
   }
   return j;
}

extern void saisie(XEvent *e, Display *d, const Window f, const uint_fast8_t id){
    static unsigned char buffer[2], str[5] = " ";

    /* On initialise le maximum a 0 pour le graph */
    parametre[2] = 0;

    /* Encodage des touches */
    static KeySym touche;
    /* Conversion de la touche en code hexadecimal */
    static uint_fast8_t i;
    volatile uint_fast8_t caractere = XLookupString(&e->xkey, buffer, sizeof(buffer), &touche, NULL);

    /* Saisir tant qu'il s'agit de chiffre */
    if(((touche >= 0xffb0) && (touche <= 0xffb9)) ||
            ((touche >= 0x30) && (touche <= 0x39))){
        if(i<2){ i++; }
        /* Chaque chiffre s'enregistre dans la chaine */
        str[i] = *buffer;
    /* Supprimession d'un chiffre */
    }else if(((touche == 0xff08) || (touche == 0xffff)) && (i>0)){
        /* Terminaison de la chaine de caractere */
        str[i] = '\0';
        i--;
    /* Si l'on appuie sur entree */
    }else if(touche == 0xff0d){
        volatile uint_fast8_t tmp = (const unsigned short int)strtol(str, NULL, 10);
        /* On converti la chaine en nombre selon la zone */
        if((id == 0) && (tmp <= 50))
            parametre[0] = (const unsigned short int)strtol(str, NULL, 10);
        else if(id == 1 && ((tmp >= 20) && (tmp <= 80)))
            parametre[1] = (const unsigned short int)strtol(str, NULL, 10);
    /* Si aucune condition ci-dessus est respectee,
    on retourne un code d'erreur 0. */
    }else{ return; }

    /* Ecrire la chaine saisie */
    XClearWindow(e->xany.display, e->xany.window);
    XDrawString(e->xany.display, e->xany.window, style(e->xany.display, 0xffffff), 
                5, 20, str, strlen(str));
}

extern void quitter(void *data){
   Element *e = (Element*)data;

   /* Fermeture du flux generant la police */
   XFreeFont(e->d, e->font);
   /* Termine les requetes non-envoyees */
   XFlush(e->d);
   /* Destruction de tous les elements */
   DestroyAll;
   /* Destructions de la fenetre racine */
   XDestroyWindow(e->d, e->f);
   XKillClient;
   /* Fermeture de la connexion */
   XCloseDisplay(e->d);

   exit(0);
}
