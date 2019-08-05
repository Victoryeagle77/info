/*
Question 1 : Singletons. 
Écrivez un programme qui reçoit une liste de réels et affiche uniquement les valeurs
présentes une seule fois dans la liste.

Le programme demandera d'abord à l'utilisateur combien de réels il souhaite rentrer, 
puis il demandera un à un tous les réels. 
Il affichera ensuite, sur une seule ligne, les valeurs qui n'ont pas été répétées.
*/

#include<stdio.h>
#include<stdlib.h>

int main(void){
  int nombre, test=0;
  double* liste = NULL;
	
  printf("Nombre de reels voulu : ");
  scanf("%d",&nombre);
	
  /* Allocation dynamique multiplié par le nombre choisi de réel à saisir
  pour réserver l'espace mémoire du tableau 'liste' */
  liste = (double*)malloc(nombre*sizeof(double));
	
  printf("-> Entrez les reels <- \n");
  for(int i=0; i<nombre; i++){
    printf("Reel : ");
    scanf("%lf", &liste[i]);
  }
	
  printf("Singletons : ");
  /* Récupération des valeurs saisies. */
  for(int j=0; j < nombre; j++){
    for(int k=0; k < nombre; k++){
      /* Si le nombre de la liste j est différent de celle de k. */
      if(k!=j)
        if(liste[j]==liste[k]) { test+=1; }
    }
    /* Pour afficher le nombre tel qu'il est saisie, on choisie un long double (%lg) */
    if(test==0) { printf("%lg ", liste[j]); }
    test=0;
  }
  putchar('\n');
  free(liste);

  return EXIT_SUCCESS;
}