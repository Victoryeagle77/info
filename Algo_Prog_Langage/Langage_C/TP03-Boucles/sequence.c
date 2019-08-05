/*
Question 1 : Séquence. 
Écrivez un programme qui demande deux entiers puis affiche dans l'ordre croissant tous les entiers,
compris entre ces deux valeurs (au sens large). 
Faites trois versions de votre programme, et utilisez une forme de boucle différente pour chaque. 
*/

#include <stdio.h>
#include <stdlib.h>

/* Première version */
int sequence1(void) {
  int a,b,i;

  printf("-> Premiere version\n");
  printf("Entier 1 : ");
  scanf("%d", &a);
  printf("Entier 2 : ");
  scanf("%d", &b);
  printf("Liste d'entier en ordre : ");
	
  for(i=0;i<b-a+1;i++)
    printf("%d ",a+i);
  putchar('\n');
}

/* Deuxième version */
int sequence2(void) {
  int a,b,i;
	
  printf("-> Deuxieme version\n");
  printf("Entier 1 : ");
  scanf("%d", &a);
  printf("Entier 2 : ");
  scanf("%d", &b);
  printf("Liste d'entier en ordre : ");
	
  while(a != b+1) {
    printf("%d ",a);
    a++;
  }
  putchar('\n');
}

/* Troisième version */
int sequence3(void) {
  int a,b,i;
	
  printf("-> Troisieme version\n");
  printf("Entier 1 : ");
  scanf("%d", &a);
  printf("Entier 2 : ");
  scanf("%d", &b);
  printf("Liste d'entier en ordre : ");
	
  do{
    printf("%d ", a);
    a++;
  }while(a != b+1);
  putchar('\n');
}

/* Appel des 3 versions */
int main(void) {
  printf("Entrez deux entier : \n");
  sequence1();
  sequence2();
  sequence3();
}