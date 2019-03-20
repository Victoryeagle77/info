/*
Question 4 : Balayage.
Faite un programme faisaint un triangle de Pascal en utilisant un tableau à une seule dimension !

1
1   1
1   2   1
1   3   3   1
1   4   6   4   1
*/

#include <stdio.h>

int main(void){

    int pascal[30], triangle[30];
    int i, j, str; 
    // i = lignes, j = colonne, str = structure du triangle
    int taille;        
    
    printf("**** Triangle de Pascal [utilisant un tableau à une dimension !] ****\n");
    do{
       printf("--> Entrer la taille du triangle : ");
       scanf("%d", &taille);
   }while((taille <= 0) || (taille > 30));

    triangle[0] = 1; // Servira de tampon
    pascal[0] = 1;
    printf("\n 1\n");

    for (i = 1; i < taille; i++){

        for (j = 1; j < taille; j++)
            pascal[j] = triangle[j - 1] + triangle[j];      
        pascal[i] = 1;

        for (str = 0; str <= i; str++){
            printf(" %d ", pascal[str]);
            triangle[str] = pascal[str];
        }
        putchar('\n');
    }
    return 0;
}
