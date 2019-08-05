/*
Question 1 : Privilège
En informatique, les droits d'accès sont numéroté jusqu'à 777, accordant tous les droits.
Ce qui correspond à r, w et x soit droits de lecture, d'écriture et d'exécution.
Le symbole - symolise l'abscence de droits. 

[bob@box ~]$
-rwxr-xr-x a.out

Faite un programme qui montre, pour un nombre donné, les droits correspondant comme ci dessous :

[bob@box ~]$ ./a.out 
Numéro de privilèges : 777
rwxrwxrwx
*/

#include <stdio.h>
#include <stdlib.h>

/* Droit d'écriture */
char read(int x){
  if (x==1) printf("r");
  else printf("-");
  return 0;
}

/* Droit de lecture */
char write(int x){
  if (x==1) printf("w");
  else printf("-");
  return 0;
}

/* Droit d'éxecution */
char execute(int x){
  if (x==1) printf("x");
  else printf("-");
  return 0;
}


int main(void){
  int r, w, x, i, u, tab[3];
  printf("Numéro de privilèges entre [0 --- 777] : \n");
  scanf("%d", &u);
	
  while(u > 777 || u < 0){
    printf("Droits non-valides, entrer une autre valeur : ");
    scanf("%d", &u);
  }

  /* Tableau comportant la valeur des privilèges */
  tab[0] = u / 100;
  tab[1] = (u-tab[0]*100) / 10;
  tab[2] = u % 10;
  /* Calcul par opération bit à bit des droits */
  for (int i = 0; i < 3; ++i){
    /***** Calcul du droit d'écriture *****/
    r=tab[i] >> 2; /* Décalage bit à bit à droite par 2 */
    read(r);
    /***** Calcul du droit de lecture *****/
    w = tab[i] >> 1; /* Décalage bit à bit à droite par 1 */
    w = w & 0001; /* Opération "et" bit à bit par la série de bit 0001 */
    write(w);
    /***** Calcul du droit d'exécution *****/
    x = tab[i] & 001;
    execute(x);
  }
  putchar('\n');
  return 0;
}