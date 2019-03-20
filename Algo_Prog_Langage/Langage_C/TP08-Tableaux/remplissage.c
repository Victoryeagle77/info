/*
Question 1 : Remplissage. 
Écrivez un programme qui déclare un tableau de 10 cases de type int, puis le remplit avec des valeurs choisies aléatoirement entre -50 et 50, et enfin affiche le contenu du tableau. 
L'affichage doit ressembler à ceci :

bob@box:~$ ./a.out
+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
|  12 |   0 | -49 |  35 |   8 |  -2 |  50 |  33 | -40 |  -1 |
+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAB 10 
// TAB est ici la taille maximum du tableau, le maximum de valeur que tab[] peut contenir

/* Fonction permettant de redéfinir une série d'instruction
En l'occurrence afficher +-----+ à chaque nombre affiché
*/
void ligne(void){
    putchar('+'); // putchar affiche un seul caractère et prend moins de place que printf
    for(int i=0; i<TAB; i++)
	    printf("-----+");
    putchar('\n');
}

int main(void){
	int i=0;
	int tab[TAB]; // Définition d'un tableau à 10 valeurs
	srand(time(NULL)); // Initialisation de la graine
	ligne(); // Appel de la fonction void ligne(void)
	for (; i<TAB; i++){
		tab[i]=(rand()%101)-50; 
		// Définition aléatoire de tab[i] [aléatoire = (Max*2+1) + Min]
		printf("| %3.1d ", tab[i]);
	}
	printf("|\n");
	ligne();
	return EXIT_SUCCESS;
}
