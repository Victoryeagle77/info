/*
Question 3 : Filtrage. 
Reprenez le programme de l'exercice 1 du deuxième sujet sur les conditions. 
Modifiez-le pour que lorsque l'utilisateur rentre une note de bac qui n'est pas comprise entre 10 et 20, on lui repose la question jusqu'à ce qu'il donne une note correcte.
*/


#include <stdio.h>
#include <stdlib.h>

int main(void) {
	double moyenne;

	do{
		printf("Inserez votre moyenne au bac : ");
		scanf("%lf", &moyenne);
	}while (moyenne < 10.0);

	if (moyenne < 12.0) {
		printf("Vous avez passer votre bac mais n'avez obtenue aucune mention.\n");
	}else{
		printf("Avec votre moyenne de %.2f, vous obtenez la mention ", moyenne);
		if (moyenne < 14.0)
			printf("Assez Bien.\n");
		else if (moyenne < 16.0)
			printf("Bien.\n");
		else
			printf("Très Bien.\n");
	}
	return EXIT_SUCCESS;
}