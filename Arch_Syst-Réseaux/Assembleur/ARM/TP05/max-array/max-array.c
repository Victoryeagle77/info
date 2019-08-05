/*
Question 1 : Maximum. 
Faite un programme qui propose deux entier comme données d'un tableau d'entier : 
La capacité d'un tableau et les arguments de position pour remplir le tableau.

La recherche du maximum sera fait dans un programme à part 
*/

#include <stdio.h>
#include <stdlib.h>

/* Fonction max */
int max(int *tab, int taille){
    int maximum, i;
    maximum = *tab;
    /* Recherche du maximum */
    for(i=0; i<taille; i++){
        if(maximum < *(tab+i))
            maximum = *(tab+i);
    }
    return maximum;
}

int main(void){
    int *tab; 
    int taille, i, maximum=0; 
    /* Saisie des données */
    printf("Dimension du tableau : ");
    scanf("%d", &taille);
    tab = (int*)calloc(taille, sizeof(int));
    /* Lecture du tableau */
    for (i=0; i<taille; i++){
        printf("arg[%d] : ", i);
        scanf("%d", &tab[i]);
    }
    /* Affichage du tableau */
    for (i=0; i<taille; i++)
        printf("| %d ", tab[i]);
    putchar('|');
    putchar('\n');
    printf("Maximum : %d\n", max(tab, taille));
    return 0;
}