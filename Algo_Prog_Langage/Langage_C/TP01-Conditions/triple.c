/*
Question 3 : Triple.
Écrivez un programme qui demande un entier naturel, puis affiche le multiple de 3 dont il est le plus proche. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
	int x,y;
	printf("Inserez un entier naturel : ");
	scanf("%d", &x);
	// On caste la valeur de y en entier, et round fonction calcule l'arrondi le plus proche de la valeur de x
	y = (int)(round((double)x/3.0))*3;
	printf("Le multiple de 3 le plus proche de %d est %d\n", x, y);

	return EXIT_SUCCESS;
}
