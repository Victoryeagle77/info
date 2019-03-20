/*
Question 2 : Parenthèses. 
Les fichiers sources en langage C contiennent trois formes de parenthèses : {}, () et []. 
Un fichier source qui respecte la grammaire du C ne peut pas contenir ces symboles dans n'importe quel ordre : 
on dit qu'il est bien parenthésé.

Nous allons nous substituer au compilateur et écrire un programme qui vérifie qu'un fichier source est bien parenthésé 
(mais nous ne nous préoccuperons pas des autres aspects de la grammaire du C).

Les parenthèses vont par couple. Si on lit le fichier en ordre séquentiel, on trouvera en premier la parenthèse ouvrante. 
Il faut donc la mémoriser en attendant de trouver la parenthèse fermante qui lui correspond : 
nous avons besoin d'une structure de données. Nous avons de plus besoin de pouvoir ajouter des éléments un par un à cette structure.

Lorsque nous lisons une parenthèse fermante, parmi toutes les parenthèses ouvantes mémorisées, 
c'est forcément la plus récente qui doit lui être associée. 
Notre structure de données doit donc pouvoir nous fournir l'élément le plus récemment ajouté : c'est une pile !

En vous basant sur ces idées et sur l'exemple de pile développé dans les deux exercices précédents, 
écrivez le programme demandé. 
*/

#include <stdio.h>
#include <stdlib.h>

#include "pile.h"

void push(pile* pp, char new) {
	struct maillon* tmp;
	tmp=(struct maillon*)malloc(sizeof(struct maillon));
	tmp->caractere=new;
	tmp->suivant=*pp;
	*pp=tmp;
}

char pop (pile* pp) {
	struct maillon tmp=**pp;
	free(*pp);
	*pp=tmp.suivant;
	return tmp.caractere;
}

int top(pile p) { return p->caractere; }