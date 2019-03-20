/*
Question 4 : Échange. 
Écrivez une fonction qui intervertit les valeurs de deux variables. 
*/
#include <stdio.h>

void permutation(int *a, int *b){ 
	/* Tampon pointé récupérant directement les valeurs de a et b, 
	évitant de créer une variable tampon. */
	*a += *b; // *a = *a + *b
	*b = *a - *b;
	*a -= *b; // *a = *a - *b
	printf("-> Permutation (a, b)\na = %d et b = %d\n", *a, *b);
}

int main(void){
    int a, b;
    printf("\n*** Entrer deux valeurs ***\n");
    printf("Valeur [a] = ");
    scanf("%d", &a);
    printf("Valeur [b] = ");
    scanf("%d", &b);
    permutation(&a, &b);
    return 0;
}
