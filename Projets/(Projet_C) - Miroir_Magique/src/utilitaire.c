#include "../header/interface.h"

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

extern void quitter(void *data){
   Sortie *e = (Sortie*)data;
   /* Fermeture du flux generant la police */
   XFreeFont(e->d, e->font);
   /* Fermeture des fenetres */
   XCloseDisplay(e->d);
   free(e);
   exit(0);
}