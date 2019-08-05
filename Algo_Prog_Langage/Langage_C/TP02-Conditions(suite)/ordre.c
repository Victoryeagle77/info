/*
Question 2 : Ordre. 
Écrivez un programme qui demande trois valeurs entières, puis les affiche dans l'ordre croissant.
Combien de comparaisons faut-il au maximum à votre programme pour trouver le bon ordre ? 
Améliorez votre code de façon à ne jamais en utiliser plus de trois par exécution.
*/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int a,b,c;
  printf("Ecrivez 3 entiers :\n");
  printf("Entier 1 : ");
  scanf("%d", &a);
  printf("Entier 2 : ");
  scanf("%d", &b);
  printf("Entier 3 : ");
  scanf("%d", &c);
  if (a < b && a < c) {
    if (b < c) { printf("%d < %d < %d\n", a, b, c); }
    else { printf("%d < %d < %d\n", a, c, b); }
		
  }else if (b < a && b < c){
    if (a < c) { printf("%d < %d < %d\n", b, a, c); }
    else { printf("%d < %d < %d\n", b, c, a); }
		
  }else if (c < a && c < b){
    if (a < b) { printf("%d < %d < %d\n", c, a, b); }
    else { printf("%d < %d < %d\n", c, b, a); }	
  }
  return EXIT_SUCCESS;
}