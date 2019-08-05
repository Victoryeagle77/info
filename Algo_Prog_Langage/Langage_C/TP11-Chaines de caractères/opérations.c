/*
Question 4 : Opérations.
Écrivez un programme qui affiche le résultat de l'opération basique de ses deux premiers arguments 
(on suppose que ce sont des entiers). 
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]){
  int a, b, res;
  char operateur;
	
  if(argc != 4){
    printf("%s", "Usage : <int> <char> <int>");
    return EXIT_FAILURE;
  }
	
  /* Conversion des arguments en entier de type int */
  a = strtol(argv[1], NULL, 10);
  b = strtol(argv[3], NULL, 10);
	
  /* Entre un caractère pour le deuxième argument après argv[0] */
  operateur = argv[2][0];
	
  /* Equivalent plus optimisé de la condition "else if" */
  switch(operateur){
    case '+': res = a+b; break;
    case '-': res = a-b; break;
    case 'x': res = a*b; break;
    case '/': res = (int)(a/b); break;
    default: res = 0; break;
  }
	
  if(operateur == '+' || operateur == '-' || operateur == 'x' || operateur == '/')
    printf("%d %c %d = %d\n", a, operateur, b, res);
  else{ printf("%s", "Usage : <int> <char> <int>"); }
  return EXIT_SUCCESS;
}