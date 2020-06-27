#include "../header/interface.h"

extern uint_fast8_t *date(void){
    static uint_fast8_t str[2];
    time_t temps = time(NULL);
    volatile struct tm tm = *localtime(&temps);
    sprintf(str, "%02d/%02d/%d - %02d:%02d:%02d", tm.tm_mday, 
            tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, 
            tm.tm_min, tm.tm_sec);
    return str;
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

extern void saisie(Display *d, XEvent *e, const uint_fast8_t id){
    static uint_fast8_t buffer[2], temperature[5] = " ", humidite[5] = " ";
    static uint_fast8_t i, j;

    /* On initialise le maximum a 0 pour le graphique */
    parametre[2] = 0;

    /* Encodage des touches */
    static KeySym touche;
    /* Conversion de la touche en code hexadecimal */
    XLookupString(&e->xkey, buffer, sizeof(buffer), &touche, NULL);

    /* Saisir tant qu'il s'agit de chiffre */
    if(((touche >= 0xffb0) && (touche <= 0xffb9)) ||
            ((touche >= 0x30) && (touche <= 0x39))){
        /* Enregistrement de chaque chiffre dans la chaine correspondante */
        if(id == 0){
            if(i<2){ i++; }
            temperature[i] = *buffer;
        }else if(id == 1){
            if(j<2){ j++; }
            humidite[j] = *buffer;
        }
    /* Suppression d'un chiffre */
    }else if(((touche == 0xff08) || (touche == 0xffff)) && (i>0)){
        /* Terminaison de la chaine de caractere */
        if(id == 0){
            temperature[i] = '\0';
            i--;
        }else if(id == 1){
            humidite[j] = '\0';
            j--;
        }
    /* Si l'on appuie sur entree */
    }else if(touche == 0xff0d){
        static volatile uint_fast8_t tmp[2];
        /* On converti la chaine en nombre selon la zone */
        tmp[0] = (const uint8_t)strtol(temperature, NULL, 10);
        tmp[1] = (const uint8_t)strtol(humidite, NULL, 10);
        /* On verifie les valeurs converties */
        if((tmp[0] <= 50) && (tmp[1] >= 20) && (tmp[1] <= 80)){
            for(volatile uint_fast8_t i=0; i<2; i++)
                parametre[i] = tmp[i];
        }
    /* Si aucune condition ci-dessus est respectee, on ne retourne rien. */
    }else{ return; }

    /* Ecrire la chaine saisie */
    XClearWindow(d, e->xany.window);
    /* Afficher selon la zone */
    if(id == 0)
        XDrawString(d, e->xany.window, style(d, 0xffffff), 5, 20, temperature, strlen(temperature));
    else if(id == 1)
        XDrawString(d, e->xany.window, style(d, 0xffffff), 5, 20, humidite, strlen(humidite));
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
   /* Fermeture de la connexion */
   XCloseDisplay(e->d);
   /* Ferme le programme utilisateur */
   XKillClient;

   exit(0);
}
