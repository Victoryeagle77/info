/*
Question 6 : Filtre. 
Reprenez le programme de l'exercice "remplissage".
Après avoir affiché le tableau, retirez-en toutes les valeurs négatives (sans changer l'ordre des autres valeurs) puis affichez-le à nouveau. 
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define TAB 10

void ligne(int contenance){
    putchar('+');
    for(int i=0; i<contenance; i++)
	    printf("-----+");
    putchar('\n');
}

int main(void){
	int i, positif = 0;
	int tab[TAB];
	srand(time(NULL));
	ligne(TAB);
	putchar('|');
	for (i=0; i<TAB; i++){
		tab[i]=(rand()%101)-50;
		printf(" %3.1d |", tab[i]);
		if(tab[i] >= 0)
		      positif ++; // Compte les entiers positifs.
	}
	putchar('\n');
	ligne(TAB);
	printf("-> Entiers positifs du tableau :\n");
	ligne(positif);
	putchar('|');
	for(i=0; i<TAB; i++){
	      if(tab[i] >= 0) // N'affiche que les entiers positifs ou nuls
	            printf(" %3.1d |", tab[i]);
	}
	putchar('\n');
	ligne(positif);
	return EXIT_SUCCESS;
}
