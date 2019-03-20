/*
Question 2 : Maximum. 
Modifiez le programme de l'exercice "remplissage" pour qu'il identifie le plus grand élément du tableau. 

bob@box:~$ ./a.out
                           |
                           V
+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
|  27 | -33 | -12 | -37 |  48 |  -7 |   0 | -50 |  -3 | -13 |
+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define TAB 10

void ligne(void){
    putchar('+');
    for(int i=0; i<TAB; i++)
	    printf("-----+");
    putchar('\n');
}

int main(void){
	int i=0, max=0;
	int tab[TAB];
	srand(time(NULL));
	
	for(i=0;i<TAB;i++){
	    tab[i]=(rand()%101)-50;
        if(tab[i]>tab[max])
            max=i; // Variable tampon retenant successivement chaque valeurs supérieur à 0
    }
    for(i=0; i<(3*max)+1; i++) // Boucle pour le décalage
        printf("%2.s"); // Espace a répété (3 * maximum) + 1 nombre de fois
    printf(" |\n");
    for(i=0; i<(3*max)+1; i++)
      printf("%2.s");
    printf(" V\n");

    ligne();
    printf("| ");
      for(i=0; i<TAB; i++)
          printf("%3.1d | ", tab[i]);
    putchar('\n');
    ligne();

    return EXIT_SUCCESS;
}
