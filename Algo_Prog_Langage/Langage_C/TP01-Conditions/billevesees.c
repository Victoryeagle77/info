/*
Question 2 : 
Billevesées. Compilez et exécutez le programme suivant. Pouvez-vous expliquer ce qui se passe ? 

int main(void) {
  int x=3;               
 
  if (x=2)
    printf("%s", "x vaut 2\n");   
  else
    printf("%s", "x est different de 2\n");              
 
  printf("%d", x);                                          
  printf("%c", '\n');                                          
 
  if (x=0)
    printf("%s", "x vaut 0\n");                                         
  else
    printf("%s", "x est different de 0\n");          
 
  printf("%d", x);                                          
  printf("%c", '\n');                                          
 
  return EXIT_SUCCESS;
}
*/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int x=3;               
	printf("%s", (x=2) ? "x vaut 2\n" : "x est different de 2\n");              
	printf("%d", x);                                          
	printf("%c", '\n');                                          	 
	
	printf("%s", (x=0) ? "x vaut 0\n" : "x est different de 0\n");         	 
	printf("%d", x);                                          
	printf("%c", '\n');

	return EXIT_SUCCESS;
}

/* 
2) On affecte à x la valeur 2 
Donc x > 0 ce qui est vrai
Et on affecte à x 0 donc x == 0 ce qui est faux 
*/