#include <stdio.h>

/*

int main(void){
   printf("%f\n", 12345.678910111213);
   return EXIT_SUCCESS;
}

- Ce programme n'affiche que 6 chiffres après la virgule.
On en déduit que le format %f correspond à l'extension de maximum 6 chiffres après la virgule.
- L'extension de format de x chiffres (%.xf) permet de rajouter x chiffres après la virgules
de la même manière que sur une chaîne de caractère en rajoutant des esapces. 
*/

int main(void){
   printf("%.12f\n", 12345.678910111213); // 12 chiffres après la virgules.
   printf("%.15f\n", 12345.678910111213); // 15 chiffres après la virgules.
   return 0;
}
