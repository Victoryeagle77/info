/*
Question 4 : Complexes. 
Un complexe est un nombre pouvant s'écrire en forme algébrique 
z = x + i.y où i désigne la racine carrée de -1.
On nomme x la partie réelle de z et y sa partie imaginaire. 
Définissez une structure pour représenter un complexe sous forme algébrique.

Écrivez ensuite des fonctions pour calculer le module, le conjugué et l'inverse d'un complexe.
*/

#include <stdio.h>
 
struct complexe { /* Strucutre d'un nombre complexe */
	double reel;	// partie reelle
	double imaginaire;  // partie imaginaire
};
 
/* Type de définition de strcuture, de la structure Complexe. */
typedef struct complexe Complexe;
 
void saisir(Complexe *x){
	printf("\nSaisir Partie reelle (Re) : ");
	// L'opérateur '->' est utilisé pour accéder aux éléments de la structure, en utilisant une variable de pointeur.
	scanf("%lf", &x -> reel); // " x -> reel " revient à faire : " (*x).reel "
	printf("Saisir Partie imaginaire (Im) : ");
	scanf("%lf", &x -> imaginaire); // (*x).imaginaire
}

int main(void){
	Complexe x;
	printf("\n=== Complexe ===\n");
	saisir(&x);
	printf("--> Affichage du complexe : ");
	printf("%lg + %lg i", x.reel, x.imaginaire);
	printf("\n");
	return 0;
}
 
 