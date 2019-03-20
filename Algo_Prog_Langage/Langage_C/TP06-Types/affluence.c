/**
Question 4 : Affluence. 
- Un magasin est ouvert du lundi au vendredi. Chaque jour, un employé compte le nombre de visiteurs à franchir ses portes, 
afin d'avoir une idée de la fréquentation moyenne. 
- Écrivez un programme qui demande à l'utilisateur le nombre de visiteurs pour chaque jour de la semaine, puis affiche le nombre moyen de visiteurs par jour.  
**/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	int lun, mar, mer, jeu, ven, moyenne;
	if (argc != 6) { // les arguments + 1 car l'exécutable ./a.out est considéré comme un argument
		printf("%s <lundi> <mardi> <mercredi> <jeudi> <vendredi>\n", argv[0]);
		return 1; // Echec ou EXIT_FAILURE
	}
	/* 
	La structure (int)strtol(argv[x],NULL,0) permet de convertir les valeurs données au moment de l'exécution.
	Comme les arguments en ligne de commande sont des chaînes de caractère, cela converti en entier.
	*/
	lun = (int)strtol(argv[1],NULL,0);
	mar = (int)strtol(argv[2],NULL,0);
	mer = (int)strtol(argv[3],NULL,0);
	jeu = (int)strtol(argv[4],NULL,0);
	ven = (int)strtol(argv[5],NULL,0);
	// Moyenne de tous les jours divisés par 5.
	moyenne = (lun+mar+mer+jeu+ven)/5;
	printf("La moyenne des visites durant la semaine est : %d\n", moyenne);
	return 0;
}
