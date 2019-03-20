/*
Question 1 : Mention.
Écrivez un programme qui demande la moyenne du Bac et affiche la mention correspondante. 
*/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	double moyenne=0;
	printf("Entrez votre moyenne : ");
	scanf("%lf", &moyenne);
	if (moyenne < 10.0 || moyenne > 20.0) {
		printf("Note non valide");
		return EXIT_FAILURE;
	}
	if (moyenne < 12.0)
		printf("Aucune mention.\n");
	else {
		printf("Avec une moyenne de %.2f, vous obtenez la mention ", moyenne);
		if (moyenne < 14.0)
			printf("Assez Bien.\n");
		else if (moyenne < 16.0)
			printf("Bien.\n");
		else
			printf("Tres Bien.\n");
	}
	return EXIT_SUCCESS;
}