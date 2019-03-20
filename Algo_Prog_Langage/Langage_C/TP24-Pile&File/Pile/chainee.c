/* Question 1 : Chaînée. 
Nous allons avoir besoin de stocker des caractères dans une pile pour le troisième exercice. 
Afin de préparer le terrain, nous allons réaliser une telle pile à l'aide d'une liste chaînée et la tester.

Écrivez la définition d'un maillon, et la définition de trois fonctions 
qui représentent les opérations push, pop et empty. Dans un autre fichier, 
écrivez un programme de test qui permet à son utilisateur de donner une suite d'ordres à une pile.

bob@box:~$ ./a.out
La pile attend vos ordres
> +J
Le caractère J a été ajouté
> -
Le caractère J a été supprimé
> -
La pile est vide !
> +X
Le caractère X a été ajouté
> ++
Le caractère + a été ajouté
> -
Le caractère + a été supprimé
> q
Au revoir
*/

#include <stdio.h>
#include <stdlib.h>

#include "pile.h"

void main(void) {
	pile p=NULL;
	char instruction;
	char stock;
	printf("La pile attend vos ordres\n");
	while (instruction != 'q') {
		printf("> ");
		instruction = getchar();
		if (instruction=='+') {
			stock=getchar();
			push(&p, stock);
			printf("Le caractère %c a été ajouté\n", stock);
		}
		if (empty(p))
			printf("La pile est vide\n");
		else {
			if (instruction=='-') {
				stock=pop(&p);
				printf("Le caractère %c a été supprimé\n", stock);	
			} else if (instruction=='t') {
				stock=top(p);
				printf("Le caractère au sommet de la pile est %c\n", stock);
			} else if (instruction=='c') {
				clear(&p);
				printf("La pile a été vidé\n");
			}
		}

		getchar();
	}
	printf("Au revoir\n");
}