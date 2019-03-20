/* 
Question 1 : Curiosité. 

Voici la fonction de MacCarthy :

int f(int n) { 
  if (n>100)
    return n-10;
  else
    return f(f(n+11));
}

Quelles sont les valeurs prises par cette fonction ?
*/

#include <stdlib.h>
#include <stdio.h>

int f(int n) { 
  if (n>100) { return n-10; }
  else { return f(f(n+11)); }
}

int main(int argc, const char * argv[]){
	if(argc =! 2){
		printf("Usage: %s <entier>", argv[0]);
		return -1;
	}
	int n;
	n=strtod(argv[1], NULL);
	n=f(n);
	printf("%d\n",n);
	return 0;
}

/* De 0 à 101, le résultat reste 91, puis il s'incrémente 
de 1 en 1 pour les autres nombres. */