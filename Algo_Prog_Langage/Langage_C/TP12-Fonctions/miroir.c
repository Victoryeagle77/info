/*
Question 2 : Miroir. 
Faites un programme affichant des valeurs aléatoires normalement dans un tableau, 
puis de la dernière à la première valeur dans le sens d'apparition des valeurs du tableau normale sans inverser l'ordre.

Définissez une fonction qui affiche le tableau, une fonction qui le remplit de valeurs aléatoires, et une fonction qui inverse le tableau. 
Modifiez la fonction principale pour qu'elle utilise ces trois fonctions. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAB 10

void ligne(void){
    putchar('+');
    for(int i=0; i<TAB; i++)
	printf("-----+");
    putchar('\n');
}

void tableau(int *tab, int i){
	ligne();
	putchar('|');
	for(i = 0; i < TAB; i++) {
  		tab[i]=(rand()%101)-50;
  		printf(" %3.1d |", tab[i]);
    }
	putchar('\n');
	ligne();
}

void inverse(int *tab, int i){
	printf("--> Tableau inverse <--\n");
 	ligne();
	putchar('|');
	// Boucle partant de 10 et décrémentant la valeur de i à chaque valeur inférieur ou égale à 1.
	for(i = (TAB-1); i>=0; i--)
  	   printf(" %3.1d |", tab[i]);
	putchar('\n');
	ligne();
}

int main (void){
    int i, tab[TAB];	
    srand(time(NULL));
    tableau(tab, i);
    inverse(tab, i);
    return EXIT_SUCCESS;
 }
