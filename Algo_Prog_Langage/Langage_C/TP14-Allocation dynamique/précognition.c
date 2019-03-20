/*
Question 3 : Précognition. 
Écrivez un programme qui reçoit une liste de réels et affiche uniquement les valeurs présentes une seule fois dans la liste.

Le programme ne demandera pas au préalable à l'utilisateur combien de réels il souhaite rentrer, il devra taper q pour quitter.
Il affichera ensuite, les valeurs qui n'ont pas été répétées. */

#include<stdio.h>
#include<stdlib.h>

int main(void){
  double* liste = NULL;
  char car = '\0'; // Initialisé à caracètre vide.
  int value, test=0;
  // Allocation dynamique de liste castée en double pour entrer autant de valeurs que l'on souhaite.
  liste = (double*)malloc(sizeof(double));
  printf("Entrez des reels (et 'q' pour quitter): \n");
  
  for(value=0; car !='q'; value++){
          printf("Reels : ");
          scanf("%lf", &liste[value]);
          scanf("%c", &car);
          /* Casting d'une réallocation dynamique en type double
          pour intégré également la variable de type de char. */
          liste = (double*)realloc(liste, (value+2)*sizeof(double));
  }
  printf("\nValeurs :\n");
  // Récupération des valeurs inscrites.
  for(int i=0; i < (value-1); i++){
        for(int j=0; j < (value-1); j++){
            if(j != i)
              if(liste[i]==liste[j]) { test += 1; }
        }
        if(test==0) 
          // On utilise ici un long double (%lg) pour afficher les valeurs tel quel sont saisie.
          printf("%lg\n", liste[i]);
        test=0;
  }
  // Libération de l'espace mémoire pris lors d'une allocation dynamique.
  free(liste);

  return EXIT_SUCCESS;
}