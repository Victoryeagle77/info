/*
Question 2 : Tailles. 
Écrivez un programme qui affiche la taille en octets d'un enregistrement contenant trois champs de type char. Êtes-vous surpris ?

Modifiez le programme pour que le deuxième champ soit un int. Comment expliquez-vous la nouvelle taille ? 
Placez ce champ en premier dans la définition de la structure. Qu'est-ce qui change ?
*/

#include "stdlib.h"
#include "stdio.h"

struct taille{	
	char a;
	char b;
	char c;
}; // Strucutre de 3 char de 1 octet

struct taille_2{
	char d;
	int e;
	char f;
}; // Strcture de 2 char de 1 octet et de 1 int de 4 octets.

struct taille_3{
	int i;
	char j;
	char k;
}; // Structure de 2 char de 1 octet et de 1 int de 4 octets.

int main(void){
	// Tailles respectives en octets des structure précédente avec sizeof().
	printf("Structure de types <-> 1 char + 1 char + 1 char = %d octets\n", sizeof(struct taille));
	printf("Structure de types <-> 1 char + 1 int + 1 char = %d octets \n", sizeof(struct taille_2));
	printf("Structure de types <-> 1 int + 1 char + 1 char = %d octets \n", sizeof(struct taille_3));
}

/* La taille change selon la position des types de définition de variables dans la structure. */
