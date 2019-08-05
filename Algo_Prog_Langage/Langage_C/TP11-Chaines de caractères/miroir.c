/*
Question 5 : Miroir. 
Écrivez un programme qui affiche sa propre ligne de commande, mais en inversant l'ordre des caractères :

bob@box:~$ ./a.out toto 456
654 otot tuo.a/.
*/

#include <stdio.h>

int main(int argc, char const *argv[]){
  int i, j, k;
  /* Boucle inversant l'ordre des arguments */
  for(i = (argc-1); i >= 0; i--){
    /* Boucle avec un compteur j qui s'incrémentent.
    - Il est placé dans la deuxième dimension de la chaine argv, 
    car il s'agit de la longueur de la chaine, qui est un tableau par définition.
    - La première dimension correspond aux arguments entrés à partir de l'exécutable. */
    for(j = 0; argv[i][j] != '\0'; j++); 
    /* Permet d'inverser l'odre de j pour inverser les caractères. */
    for(k = j; k >= 0; k--)    
      printf("%c", argv[i][k]); /* Les arguments + leurs caractères. */
    putchar(' '); /* Espace entre chaque argument. */
  }
  putchar('\n');
  return 0;
}