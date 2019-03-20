/*
Question 2 : Sierpinski. 
Le Triangle de Sierpiński est une fractale dont on s'approche par une suite de figures de complexité croissante.

Écrivez un programme qui prend un entier naturel en argument sur la ligne de commande et trace la figure d'ordre correspondant en mode graphique.
----------
|Remarque| Il est utile de constater que toutes les figures à l'exception de l'ordre 0 sont composées de trois parties identiques.
----------
*/

#include <stdlib.h>
#include <stdio.h>
#include <graph.h>

void sierpinski(int n, int x1, int y1, int x2, int y2, int x3, int y3) {
	if (n==0) {
		return;
	}
	DessinerSegment(x1,y1,x2,y2);
	DessinerSegment(x2,y2,x3,y3);
	DessinerSegment(x3,y3,x1,y1);
	n--;
	sierpinski(n, x1, y1, (x1+x2)/2, (y1+y2)/2, (x3+x1)/2, (y3+y1)/2);
	sierpinski(n, (x3+x1)/2, (y3+y1)/2, x3, y3, (x2+x3)/2, (y2+y3)/2);
	sierpinski(n, (x1+x2)/2, (y1+y2)/2, (x2+x3)/2, (y2+y3)/2, x2, y2);
}

int main(int argc, const char* argv[]) {
	int n, x1, y1, x2, y2, x3, y3;
	if(argc != 2){
		printf("Usage : %s", argv[0]);
		return -1;
	}
	n=(int)strtol(argv[1], NULL, 0);
	if(n < 0 || n > 8){
		printf("Usage : %s int > 0 et < 8", argv[1]);
		return -1;
	}
	x1 = 0;
	y1 = 500;
	x2 = 500/2;
	y2 = 0;
	x3 = 500;
	y3 = 500;
	
	InitialiserGraphique();
	CreerFenetre(0,0,500,500);

	sierpinski(n+1,x1,y1,x2,y2,x3,y3);

	while(!(Touche()));
	FermerGraphique();
}