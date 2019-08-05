/* 
Question 2 : Statistiques. 
Écrivez un programme qui lit une ligne de texte (ne dépassant pas 200 caractères) 
et la stocke dans une chaîne de caractères, puis affiche :

   le nombre de 'e' qu'elle contient,
   le nombre de caractères différents qu'elle contient.
*/

#include <stdlib.h>
#include <stdio.h>

int main(void){
  char chaine[201];
  char lecture[201];
  int i, e=0, j, taille=0, char_found;
    
  printf("Entrez du texte (200 caracteres maximum): ");
 	  
  /* Lecteur de caractère adapté au chaine contrairement au "scanf()" s'arrétant au espace. */
  fgets(chaine, 201, stdin);

  for (i = 0; '\n' != chaine[i]; i++){
    if (chaine[i]=='e'){ e++; } /* Compteur de e */
    
    /* Variable de caractère différent */
    char_found=0;
    for (j = 0; '\0' != lecture[j]; j++){
      if (lecture[j] == chaine[i]){ char_found=1; }
    }
    if (char_found == 0){
      lecture[taille]=chaine[i];
      taille++; /* Compteur de caractères différents */
    } 
  }
  printf("-> Nombre de lettre 'e' = %d\n", e);
  printf("-> Chaine de %d caracteres differents\n", taille);	
  return EXIT_SUCCESS;
}