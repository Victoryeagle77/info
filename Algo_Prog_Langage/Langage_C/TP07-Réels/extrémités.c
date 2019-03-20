#include <stdio.h>
#include <stdlib.h>

int main(void){
    printf("%f\n", +1.0/0.0);
    printf("%f\n", -1.0/0.0);
    printf("%f\n", -0.0/0.0);
    return EXIT_SUCCESS;
}

/*
- Ce programme affiche ceci :

inf
-inf
-nan

Les nombre à virgules flotantes ont des caractéristiques particulière dans leur traduction :
- Au moment de la traduction, le résultat se développe en une expression constante de type float déjà pré-existante
positive (pour +1.0/0.0) ou non signé (pour -1.0/0.0). Celle ci déborde alors sans trouver 
de valeur précise. 
- Nan signifie "pas un nombre (not a number)", le résultat de cette opération est ici indéfini. 
Il s'agit également une expression constante de type float non signé (car -0.0).   
*/
