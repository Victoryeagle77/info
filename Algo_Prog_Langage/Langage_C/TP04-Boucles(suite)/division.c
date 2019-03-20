/*
Question 1 :  Division. 
Écrivez un programme qui demande à l'utilisateur une valeur entière positive ou nulle, puis une valeur entière strictement positive, 
et qui affiche ensuite le quotient et le reste de la division euclidienne de la première valeur par la deuxième, en utilisant dans vos calculs seulement des additions et des soustractions.

Entrez une valeur >= 0 : 46
Entrez une valeur > 0  : 7
-->  46 = 6 x 7 + 4 
*/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	// c=chiffre, d=diviseur, q=quotien, r=reste
	int i, c, d, q=0, r;
	printf("Entrez une valeur >= 0 : ");
	scanf("%d",&c);
	printf("Entrez une valeur > 0  : ");
	scanf("%d",&d);
	
	i=c;
	while(i > 0){
		i -= d;
		q++;
	}
	if (i < 0){
		i += d;
		r = i;
	}else if (i == 0)
		r = 0;
	else	
		r=i;
	q--;
	printf("%d = %d x %d + %d \n", c, q, d, r);
	return EXIT_SUCCESS;
}
