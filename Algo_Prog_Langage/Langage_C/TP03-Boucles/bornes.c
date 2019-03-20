/*
Question 6 : Bornes. 
Écrivez un programme qui laisse l'utilisateur saisir autant d'entiers naturels qu'il le souhaite. 
Lorsque celui-ci saisit la valeur -1, cela signifie que la saisie est terminée. Le programme affiche alors seulement la plus petite et la plus grande des valeurs saisies. 
*/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int x=0, min=0, max=0;
	while (x != -1){
		printf("entrez un entier positif (-1 pour finir la saisie et le programme) : ");
		scanf("%d", &x);
		if (x != -1) {
			if (x < min)
				min=x;
			else if (x>max)
				max=x;
		}
	}

	printf("Valeur min=%d et max=%d\n", m, max);
	
	return EXIT_SUCCESS;
}