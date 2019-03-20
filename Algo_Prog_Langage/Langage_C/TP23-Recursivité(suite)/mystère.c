#include <stdio.h>
#include <stdlib.h>

unsigned int mystere(unsigned int a, unsigned int b) { 
	unsigned int x;
	if (b==1)
		return a;
	else
		x = mystere(a,b-1);
		return a + x;
}

int main(int argc, const char *argv[]){
	unsigned int a, b;
	if (argc != 3){
		printf("Usage : %s ", argv[0]);
		return -1;
	}
	a = strtoul(argv[1],NULL,10);
	b = strtoul(argv[2],NULL,10);
	printf("%u\n", mystere(a,b));
	return 0;
}

/* Multiplie a par b */