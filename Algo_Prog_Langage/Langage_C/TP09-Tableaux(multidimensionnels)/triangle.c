/*
Question 3 : Triangle. 
Écrivez un programme qui place dans un tableau à deux dimensions un triangle de Pascal de hauteur maximale 20 puis l'affiche. 

1
1   1
1   2   1
1   3   3   1
1   4   6   4   1
1   5  10  10   5   1
1   6  15  20  15   6   1
*/

#include <stdio.h>

int main(void){
 	
 	int pascal[30][30]; // Taille en colonne puis en ligne  
 	int h;              // hauteur du triangle 
 	int i, j;      	    // indices des boucles (i=lignes)  
   
        printf("-> Entrez la hauteur du triangle (max 20) : ");
        scanf("%d", &h);

 	while (h>30 || h<0){
            printf("-> Valeur pas valable : ");
     	    scanf("%d", &h);
 	}
 	/* Construction des lignes 0 à h du triangle :
 	Calcul des composantes du triangle jusqu'à la diagonale principale. */
 	for (i=0; i<=h; i++){
           pascal[i][0] = 1;
           pascal[i][i] = 1;
           for (j=1; j < i; j++) 
              pascal[i][j]=pascal[i-1][j-1]+pascal[i-1][j];
        }

        for (i=0; i<=h; i++){
            for (j=0; j<=i; j++)
                printf(" %d ", pascal[i][j]);
            printf("\n");
        }
        return 0;
}
