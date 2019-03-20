/*
Question 2 : Figures.
   
Faite une fonciton construisant un triangle et une autre construisant un carré, puis un programme principale 
affichant un menu permettant de choisir entre quitter, construire un carré ou un triangle

_______________
 t) Triangle
 c) Carré
 q) Quitter
Votre choix ? t

Hauteur ? 4

*
**
***
****
_______________
 t) Triangle
 c) Carré
 q) Quitter
Votre choix ? c

Hauteur ? 5

*****
*   *
*   *
*   *
*****
_______________
 t) Triangle
 c) Carré
 q) Quitter
Votre choix ? q

Au revoir...
*/

#include <stdio.h>
#include <stdlib.h>

// Fonction pour le carré
void carre(unsigned int hauteur) {
	int i, j; // i=colonne, j=ligne
	for (i=0; i<hauteur; i++) {
		for (j=0; j<hauteur; j++) {
			if (i==0 || i==hauteur-1)
				putchar('*');
			else {
				if (j==0 || j==hauteur-1)
					putchar('*');
				else
					putchar(' ');
			}
		}
	putchar('\n');
	}
}
// Fonction pour le triangle
void triangle(unsigned int hauteur){
	int i, j;
	for (i=0; i<hauteur; i++) {
	     for (j=0; j<=i; j++)
		putchar('*');
	putchar('\n');
	}

}
// Fonction principale
int main(void) {
	char caractere;
	unsigned int hauteur;
	do{
		printf("\n___________________________\nt) Triangle\nc) Carré\nq) Quitter\nVotre choix ? ");
		scanf(" %c", &caractere); 
		// Espace pour éviter qu'un saut de ligne reste dans le tampon
		
		if(caractere=='t' || caractere=='c'){
		     printf("\nHauteur ? ");
		     scanf("%u", &hauteur);
		     putchar('\n');
		}                
		if (caractere=='t')
			triangle(hauteur);
		else if (caractere=='c')
			carre(hauteur);
	}while (caractere != 'q');
	
	printf("\nAu revoir...\n");
	
	return 0;
}
