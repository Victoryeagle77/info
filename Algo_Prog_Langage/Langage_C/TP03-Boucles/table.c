/*
Question 4 : Table. 
Écrivez un programme qui demande un entier, puis affiche la table de multiplication correspondante.

entrez un entier : 5
  5 x  1 =    5
  5 x  2 =   10
  5 x  3 =   15
  5 x  4 =   20
  5 x  5 =   25
  5 x  6 =   30
  5 x  7 =   35
  5 x  8 =   40
  5 x  9 =   45
  5 x 10 =   50

Notez l'alignement des colonnes. Pour obtenir ce résultat, vous pouvez vous inspirer de la technique ci dessous : 
printf("%9.4f", 10.25);
*/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int x,i,res;
	printf("entrez un entier : ");
	scanf("%d", &x);

	for (i=1; i<=10;i++) {
		res = x*i;	
		printf("%3d x %2d = %4d\n", x, i, res);
	}
	return EXIT_SUCCESS;
}