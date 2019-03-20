/* Question 3 : Chaînée. 
Faite une file de caractère avec une des structure et un système de maillage, 
en vous aidant des indications suviantes :

Nous allons avoir besoin de stocker des caractères dans une pile pour le troisième exercice. 
Afin de préparer le terrain, nous allons réaliser une telle pile à l'aide d'une liste chaînée et la tester.

Écrivez la définition d'un maillon, et la définition de trois fonctions qui représentent les opérations push, pop et empty. 
Dans un autre fichier, écrivez un programme de test qui permet à son utilisateur de donner une suite d'ordres à une pile.

Certaines piles supportent deux opérations supplémentaires : 
top renvoie la donnée la plus récente mais ne la retire pas de la pile, 
tandis que clear retire toutes les données de la pile et ne renvoie rien. 
Ces opérations peuvent être vues comme des combinaisons des opérations basiques, 
mais en leur donnant leur propre codage on peut en améliorer les performances.

Ajoutez au programme du premier exercice deux fonctions qui représentent ces opérations. 
Imaginez et réalisez de nouveaux ordres pour tester ces fonctions
*/

#include <stdio.h>
#include <stdlib.h>

#include "file.h"

void main(void) {
	file f;
	char instru, stock;
	f.premier=NULL;
	f.dernier=NULL;
	printf("La file attend vos ordres\n");
	while (instru != 'q') {
		printf("> ");
		instru=getchar();
		if (instru=='+') {
			stock = getchar();
			enqueue(&f, stock);
			printf("Le caractère %c a été ajouté\n", stock);
		}
		if (empty(f))
			printf("La file est vide\n");
		else {
			if (instru == '-') {
				stock = dequeue(&f);
				printf("Le caractère %c a été supprimé\n", stock);	
			} else if (instru == 't') {
				stock = top(f);
				printf("Le caractère au sommet de la file est %c\n", stock);
			} else if (instru == 'c') {
				clear(&f);
				printf("La file a été vidé\n");
			}
		}
	}
	printf("Au revoir\n");
}
