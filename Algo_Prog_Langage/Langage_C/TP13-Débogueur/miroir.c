/*
Question 4 : Miroir. 
Dans le débogueur, exécutez pas-à-pas ce programme et observez l'évolution du contenu du tableau. 
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

/***** DEBOGUAGE ******/

/* Pour commencer on tape dans l'invite de commande (dans le répertoire de ce fichier) : 

---> Manuel <---
-> breakpoint :    b   <Numéro de la ligne>
Permet de marquer une ligne et de faire suivre l'exécution,
à partir de celle-ci.
-> run :           r
Permet de lancer un programme dans (gdb)
-> print :         p   <Nom de variables>
Permet d'afficher la valeur d'une variable,
à n'importe quel endroit d'un programme après le breakpoint.
-> backtrace :     bt 
-> list :          l   <Numéro de la ligne>
Permet d'afficher une liste de lignes en inscrivant le numéro de la dernière.
-> step :          s
Permet la lecture ligne par ligne depuis le breakpoint.

[bob@box TP13-Débogueur]$ gcc -g <programme>
[bob@box TP13-Débogueur]$ gdb ./a.out
Un fois dans gdb, on attérit dans l'intérface de déboguage.
(gdb) b miroir.c:6
(gdb) r
// Observation d'un tableau
(gdb) s
(gdb) p tableau[valeur]@<capacité du tableau>
Et ainsi de suite pour afficher l'évolution d'un tableau.

- En tapant gdb :
(gdb) p tab[1]@TAB
(gdb) s
Et ainsi de suite on peut observer l'évolution des valeurs dans ce tableau.
*/
