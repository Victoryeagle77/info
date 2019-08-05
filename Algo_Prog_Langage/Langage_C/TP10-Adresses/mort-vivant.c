/*
Question 3 : Mort-vivant. 
Considérez le programme suivant :

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
 
int main(void) {
  int* p;
 
  if(time(NULL)%2) {
    int x = 59;
    p = &x;
  } else {
    int y = 31;
    p = &y;
  }
  /* fragment inactif
  printf("%d", x);
  printf("%d", y); */
	
  printf("%d", *p);
  putchar('\n');
  return EXIT_SUCCESS;
}

Quelle valeur pensez-vous voir s'afficher ? Dans quelle variable cette valeur était-elle stockée au moment de l'affichage ? 
Si vous remettez dans le programme les instructions en commentaire, que constatez-vous ? Avez-vous repéré le mort-vivant ? 
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(void) {
  int* p;
 
  if(time(NULL)%2) {
    int x = 59;
    p = &x;
  } else {
    int y = 31;
    p = &y;
  }
  /* Fragment inactif activé */
  printf("%d", x);
  printf("%d", y);
	
  printf("%d", *p);
  putchar('\n');
  return EXIT_SUCCESS;
}

/*
3) - La condition est valable pour (NULL%2) et non pas (NULL), 
ce qui ne correspond pas au temps de la première exécution du programme.
Au lancement du programme s'écoulera time(NULL) et donc la valeur de y s'affichera soit 31.
- Cette valeur était stocké dans le pointeur p au moment de l'affichage.
- En rajoutant le fragment inactif, c'est la valeur de x qui s'affiche et plus celle de y.
- Donc x est le mort-vivant car il est "mort" pour le pointeur p en tant qu'adresse mais "vivant",
en tant que variable.
*/