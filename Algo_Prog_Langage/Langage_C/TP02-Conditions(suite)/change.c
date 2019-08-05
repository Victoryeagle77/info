/*
Question 4 : Change.
Écrivez un programme qui permet de passer de l'euro à la livre sterling et vice-versa.
° l'utilisateur saisit le taux de change de l'euro,
° l'utilisateur choisit ensuite le sens de la conversion,
° l'utilisateur saisit enfin la somme à convertir,
° le programme affiche le résultat de la conversion.
*/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  double entre, sorti, taux;
  int choix;

  printf("Inserez le montant que vous voulez convertir : ");
  scanf("%lf", &entre);
  printf("Quel est le taux de change de l'euro ? : ");
  scanf("%lf", &taux);
  printf("Pour convertir les euros en livres tapez 1, et inversement tapez 2 : ");
  scanf("%d",&choix);

  if (choix == 1){
    sorti = taux*entre;
    printf("%.2f livres\n", sorti);
  }else if (choix == 2){
    sorti = (1-(taux-1)*entre);
    printf("%.2f euros\n", sorti);
  }else{
    printf("Une erreur est survenue, relancer le programme.\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}