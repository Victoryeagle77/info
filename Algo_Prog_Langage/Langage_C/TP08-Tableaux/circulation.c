/*
Question 6 : Circulation. 
Modifiez le programme du premier exercice pour qu'il avance les valeurs du tableau de 4 indices (les valeurs à la fin se retrouveront au début). 
Vous afficherez le tableau avant et après permutation pour vérifier votre travail.
----------
|Remarque| La valeur 4 est arbitraire. Faites-en une constante nommée et assurez-vous que le programme marche aussi pour d'autres valeurs de décalage. 
----------
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAB 10
#define DECALAGE 4

void ligne(void){
   putchar('+');
   for(int i=0; i < TAB; i++)
       printf("-----+");
   putchar('\n');
}

int main (void){ 
    int i;
    int tab[TAB];
    srand(time(NULL));
    ligne();
    putchar('|');
    for(i = 0; i < TAB; i++) {
     	tab[i]=(rand()%101)-50;
      	printf(" %3.1d |", tab[i]);
    }
    putchar('\n');
    ligne();
        
    printf("--> Tableau permutant par %d <--\n", DECALAGE);
    ligne();
    putchar('|');
    for (i=0; i < TAB; i++) { /* i avec les nombres */
        if ((i + DECALAGE) < TAB)
             printf(" %3.1d |", tab[i + DECALAGE]); 
             // indice i + le décalage = indice de décalage
        else
            printf(" %3.1d |", tab[i - TAB + DECALAGE]); 
            // Permet de reparcourir la suite du tableau quand la capacité de celui-ci est dépassé par le décalage.                         
    }
    putchar('\n');
    ligne();
    return EXIT_SUCCESS;
}
