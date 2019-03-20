/*
Question 5 : Tables. 
Écrivez un programme qui affiche plusieurs tables de multiplication. 
Avant l'affichage de chaque table, le programme demandera à l'utilisateur sur quel entier baser la table. S'il répond -1, le programme s'arrêtera sans rien afficher de plus. 
*/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int x,i,res;
	while (x != -1){
		printf("entrez un entier (-1 pour stopper le programme) : ");
		scanf("%d", &x);
		
		if (x != -1) {
			for (i=1; i<=10;i++) {
				res = x*i;
				printf("%3d x %2d = %4d\n", x, i, res);
			}
		}
		
	}	
}