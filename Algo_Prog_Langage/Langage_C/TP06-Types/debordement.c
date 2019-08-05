/*
Question 3 : Débordement. 
- Écrivez un programme qui demande à l'utilisateur un entier, 
le stocke dans une variable de type int puis dans une variable de type char avant de l'afficher.
Testez votre programme en entrant les valeurs 65, -65, 191, puis 321. 
Comprenez-vous comment la conversion fonctionne ?
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("%s <int>\n", argv[0]);
    return 1;
  }
  int valeur = (int)strtol(argv[1],NULL,0);
  /* On caste la variable valeur directement en char au moment de l'afficher */
  printf("Valeur en char : %c\n", (char)valeur);
  return 0;
}

/* 
3) On obtient pour les nombre demandés : 
65 : A
-65 : ┐
191 : ┐
321 : A
Nous obtenons le même résultat pour (65 et 321) et pour (-65 et 191) 
On en déduit que l'encodage est de 256 bits car 321 - 65 = 256  et -65 - 191 = 256
Donc pour la conversion, on en conclue que sa réalisation s'effectue tous les 256 bits par rapport à un nombre donné
*/