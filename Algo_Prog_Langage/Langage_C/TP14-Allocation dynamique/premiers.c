/* Question 4 : Premiers. 
Écrivez un programme qui demande en boucle un nombre n strictement positif et affiche le n-ième nombre premier. Taper 0 permet de quitter le programme.

Pour commencer, définissez une fonction qui détermine si un entier est premier ou pas.

À l'aide de cette fonction, vous pourrez remplir un tableau avec tous les premiers nombres premiers en ordre croissant. 
Si le rang demandé est déjà connu, la réponse ne demande aucun calcul. 
Si le rang demandé n'a pas encore été obtenu, on remplit le tableau jusqu'à ce rang (si le rang demandé dépasse la capacité du tableau, il est redimensionné). 
*/

#include <stdio.h>
#include <stdlib.h>

int prime(int nombre){ // Fonction vérifiant la primarité d'un nombre
    unsigned int i, premier=1;
    /* Décrémentation de la valeur i quand :
     * i vaut la valeur - 1,
     * i est différent de 1,
    La boucle calcule ainsi pour la valeur entrée 2 diviseurs : 1 et elle-même. */
    for(i = nombre-1; i != 1 ; i--){
        // Si le reste de la division euclidenne entre i et la valeur est 0, le nombre n'est pas premier.
        if(nombre > 1){
          if((nombre % i == 0))
            premier = 0;
        }
    }
    if(premier) { // Si premier == 1
      printf("%d\n", nombre);
    }
   return 0;
}

int main(void){
  int* liste = NULL;
  int value;
  // Allocation dynamique de liste castée en double pour entrer autant de valeurs que l'on souhaite.
  liste = (int*)malloc(1*sizeof(int));
  printf("Entrez des entiers positifs (et '0' pour quitter): \n");
  
  for(value=0; ; value++){
        printf("Entiers : ");
        scanf("%d", &liste[value]);
        /* Réallocation de la taille du tableau si dépassée */
        liste = (int*)realloc(liste, (value+2)*sizeof(int));
        // Récupération des valeurs inscrites.
        if(liste[value]==0){
            printf("\nPremiers :\n"); 
            for(int i=0; i < (value); i++)
              prime(liste[i]);
            exit(0);
        }
  }
  // Libération de l'espace mémoire pris lors d'une allocation dynamique.
  free(liste);
  return EXIT_SUCCESS;
}