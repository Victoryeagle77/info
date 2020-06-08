#include "../header/interface.h"

/**
* @function *date
* Permet de relever la date actuelle :
* Annee, moi, jour, heures et minutes.
* Le tout est converti en chaine de caractere dans :
* @param str : La chaine recuperant la date
* @return str : La chaine convertie
*/
extern volatile unsigned char *date(char *str){
    time_t temps = time(NULL);
    volatile struct tm tm = *localtime(&temps);
    sprintf(str, "%02d/%02d/%d - %02d:%02d", tm.tm_mday, 
                tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);
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

/**
* @function quitter
* Permet de liberer les elements alloues dans l'espace memoire
* @param data : type de pointeur vers elements
*/
extern void quitter(void *data){
   Sortie *e = (Sortie*)data;
   /* Fermeture du flux generant la police */
   XFreeFont(e->d, e->font);
   /* Destruction de tous les elements */
   DestroyAll;
   /* Fermeture des fenetres */
   XCloseDisplay(e->d);
   exit(0);
}
