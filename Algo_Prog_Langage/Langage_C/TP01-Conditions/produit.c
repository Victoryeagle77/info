/*
Question 4 : Produit. 
Écrivez un programme qui demande deux réels, puis affiche le signe de leur produit sans faire la multiplication. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
	int x,y,z;
	printf("Inserez un entier : ");
	scanf("%d", &x);
	printf("Et un deuxieme entier : ");
	scanf("%d", &y);

	printf("Le produit de %d avec %d sera ",x,y);
	// Si pour x négatif
	if (x < 0) {
		// Si y et positif
		if (y > 0)
			printf("negatif\n");
		// Si y est négatif
		else if (y < 0)
			printf("positif\n");
	
	}else if (x > 0){
		if (y > 0)
			printf("positif\n");
		else if (y < 0)
			printf("negatif\n");
	}

	return EXIT_SUCCESS;
}
