/*
Question 4 : Progression. 
Ecrire un programme qui affiche le nième terme de la suite de Fibonacci, définie par la relation de récurrence suivante :

	U0 = 0
	U1 = 1
	Pour tout n>=2, Un = Un-2 + Un-1
*/

#include <stdio.h>
#include <stdlib.h>

int main(void){
	int n, u, i;
	int u_zero, u_un, fibo;
	u_zero = 0;
	u_un = 1;
	printf("-> Suite de Fibonacci <-\n");
	printf("Entrez le nieme terme que vous voulez afficher : ");
	scanf("%d", &n);
	while(n<0){
		printf("Impossible, il s'agit d'une suite de terme positif.\nEntrez un nouveau n > 0 : ");
		scanf("%d", &n);
	}
	printf("Pour le terme n=%d, la suite de Fibonacci donne : ", n);
	if (n==0 || n==1)
    	printf ("%d", n);
    else{
        for (i=2; i<=n; i++){
            fibo = u_un + u_zero;
            u_zero = u_un;
            u_un = fibo;
        }
        printf("%d", fibo);
	 }
	return EXIT_SUCCESS;
}
