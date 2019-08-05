/*
Question 1 : Phases. 

Testez la fonction suivante dans gdb :

void exemple(unsigned n) {
  if (n != 0) {
    putchar('>');
    exemple(n-1);
    putchar('<');
  } else
    putchar('O');
}

Placez un point d'arrêt sur les trois lignes qui contiennent putchar, lancez le programme, 
et à chaque fois qu'il atteint un point d'arrêt utlisez la commande bt pour voir la pile des appels. 
Pouvez-vous identifier les phases ascendantes et descendantes ?
*/

#include<stdio.h>
#include<stdlib.h>

void exemple(unsigned n) {
  if (n != 0) {
    /*** Pour n = 4 par exemple ***/
    putchar('>');
    exemple(n-1);
    /* Phases descendantes :
    exemple(4-1)
      exemple(3-1)
        exemple(2-1)
          exemple(1-1)
    */
    putchar('<');
    /* Phases ascendantes :
            exemple(4-1)
         exemple(3-1)
      exemple(2-1)
	exemple(1-1)
    */
  } else 
    /* Phase neutre exemple(1-1) */
    putchar('O');
}

void main(void){
  system("clear");
  unsigned short int n;
  printf("Entrer un entier positif non-nulle : ");
  scanf("%hu", &n);
  exemple(n);
  putchar('\n');
}