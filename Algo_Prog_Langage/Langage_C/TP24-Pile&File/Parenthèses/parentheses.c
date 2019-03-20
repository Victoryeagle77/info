/* Question 2 : Parenthèsage

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

En vous basant sur ces idées et sur l'exemple de pile développé dans les deux exercices précédents, écrivez le programme demandé. 
*/

#include <stdio.h>
#include <stdlib.h>

#include "pile.h"

void main (void) {
	pile p=NULL;
	FILE* flux;
	int res;
	char in, out;
	flux=fopen("test.txt", "r");
	if (flux==NULL) return;
	while (1) {
		res=fread(&in,sizeof(char),1,flux);
		if (res!=1) break;
		if (in=='('||in=='{'||in=='[') 
			push(&p,in);
		else if (in==')'||in=='}'||in==']') {
			out=top(p);
			if (out==in) { pop(&p); } 
			else {
				printf("Mauvais parenthesage\n");
				break;
			}
		}
	}
}
