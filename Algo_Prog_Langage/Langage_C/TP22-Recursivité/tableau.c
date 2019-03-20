/*
Question 3 : Tableau
Ecrivez une fonction qui prend en argument un tableau de réels et affiche ses éléments séparés par une virgule.
Employez la récursivité plutôt qu'une boucle.

1.25, 47.80, 77.01, 54.23, 895.14

*/

#include <stdio.h>
#include <stdlib.h>

int afficher(double* tab, int compte) {
	if (compte==0) return 0;
	if (compte == 1)
		printf("%.2f", tab[0]);
	else {
		printf("%.2f, ", tab[0]);
		afficher(tab+1, compte-1);
	}
}

int main(int argc, const char * argv[]) {
	double* tab;
	int compte = 0;
	int capacite = 10;
	char argument[BUFSIZ];
	tab = (double*)malloc(capacite*sizeof(double));
	while (1) {
		printf("Inserez un valeur (q pour quitter) : ");
		scanf("%s", argument);
		if (argument[0] == 'q') { return afficher(tab,compte); }
		if (compte == capacite) {
			capacite += 10;
			tab=(double*)realloc(tab,capacite*sizeof(double));
		}
		tab[compte]=strtod(argument, NULL);
		compte++;
	}
	afficher(tab, compte);
	putchar('\n');
	return 0;
}
