/*
Question 2 : Alphabet. 
Sans l'exécuter, prédisez ce que ce programme va afficher :

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  char min, maj;
  char *p = NULL;
 
  for(min = 'a', maj = 'A'; maj <= 'Z'; min++, maj++) {
    p = (p == &min) ? &maj : &min;
    putchar(*p);
  }
  putchar('\n');
  return EXIT_SUCCESS;
}

Une fois votre prédiction couchée par écrit, exécutez ce programme pour vérifier votre raisonnement.
*/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  char min, maj;
  char *p = NULL;
 
  for(min = 'a', maj = 'A'; maj <= 'Z'; min++, maj++) {
    p = (p == &min) ? &maj : &min;
    putchar(*p);
  }
  putchar('\n');
  return EXIT_SUCCESS;
}

/*
2) - La variable p est un pointeur est initialisé 0, 
et son type (void*) est converti vers n'importe quel type d'adresse.
L'opérateur * permet de manipuler p à travers son adresse plutôt que son nom.
- Le programme possède une boucle ou les variable min et maj correspondent respectivement,
à la lettre 'a' en minuscule et 'A', en majuscule.
Ces deux variables sont incrémentées tant que 'A' est dans l'alphabet, avant la lettre 'Z' en majuscule.
- La condition "p = (p == &min) ? &maj : &min;" correspond à :
if (p == &min)
    p = &maj;
  else
    p = &min; 
Soit, si l'adresse de p vaut l'adresse de min, alors l'adresse de p correspond à l'adresse de maj, 
sinon l'adresse de p vaut l'adresse de min.

-> Donc on peut conclure que ce programme à pour but d'afficher l'alphabet avec des majuscules et des minuscules.
-> Or sachant que l'adresse de p est 0 (NULL), 
elle ne correspondra pas à l'adresse de la variable min de type char,
et la première lettre sera alors une minuscule.
-> L'adresse de p ne sera plus 0 mais aura pris celle de min donc une majuscule s'affichera.
-> Et ainsi de suite ... 
-> Donc le programme affichera à l'exécution l'alphabet avec une lettre sur deux en minuscule puis en majuscule, 
ce qui donnera ceci : 
aBcDeFgHiJkLmNoPqRsTuVwXyZ
*/