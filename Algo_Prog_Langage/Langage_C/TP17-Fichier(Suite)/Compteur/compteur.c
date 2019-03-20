/*
Question 1 : Compteur
Ecrivez un programme qui affiche le nombre de fois qu'il a été exécuté.

bob@box:~$ ./a.out
14
bob@box:~$ ./a.out
15
bob@box:~$ ./a.out
16

*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  FILE * flux;
  int compteur = 0;

  flux = fopen("compte.txt", "r");
  
  if(flux == NULL) { // Création du fichier si inexistant
    fopen("compte.txt", "w"); // Ecriture seule
    fclose(flux); // Ferme le flux
    return 0;
  }

  fread(&compteur, sizeof(int), 1, flux); // Lecture sur l'entrée standard de compteur
  compteur++; // Incrémentation 
  printf("%d\n", compteur);

  fclose(flux);

  flux=fopen("compte.txt", "w");
  // Ecriture sur l'entrée standard du compteur incrémenté
  fwrite(&compteur, sizeof(int), 1, flux); 
  fclose(flux);
  return 0;
}
