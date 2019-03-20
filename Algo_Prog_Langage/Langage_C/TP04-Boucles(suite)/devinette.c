/*
Question 2 : Devinette. 
Écrivez un programme qui donne cinq tentatives à l'utilisateur pour deviner un nombre entre 0 et 100. 
À chaque tentative infructueuse, le programme offrira un indice en affichant + ou -. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TENTATIVES 5

int main(void) {
	unsigned int x, test=101, t=TENTATIVES;
	// Permet une plus grande efficacité de la fonction aléatoire avec initialisation de la graine.
	srand((unsigned int) time(NULL));
	x = rand();
	x %= 101;
	printf("--> Devinez le chiffre <--\n");
	while (test != x && t > 0) {
		printf("Tentez : ");
		scanf("%d", &test);
		t--;
		if (test !=x) {
			while(test < 0 || test > 100){
				printf("Ce n'est pas comris entre 1 et 100 : ");
				scanf("%d", &test);
			}
			if (x>test)
				printf("C'est + ");
			else
				printf("C'est - ");
			printf("> %d chances restantes\n", t);
		}
	}
	if (x==test)
		printf("Bravo, le chiffre est bien %d\n", x);
	else
		printf("Perdu, le chiffre est %d\n", x);
	return EXIT_SUCCESS;
}
