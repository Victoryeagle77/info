/*
Question 5.5 : Lagrange. 
Un théorème dû à Lagrange affirme que tout entier naturel peut s'écrire comme la somme de quatre carrés. 
Par exemple :

28=25+1+1+1
28=16+4+4+4
28=9+9+9+1

Ou encore :

10=9+1+0+0
10=4+4+1+1

Écrivez un programme qui demande un entier naturel, et affiche toutes ses décompositions,
sous la forme d'une somme de 4 carrés 
(attention, chaque décomposition ne doit apparaître qu'une seule fois). 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void){
  /*
  - On introduit un système d'équation à définir avec des boucles :
  Pout tout n > 0 = (x^2)+(y^2)+(z^2)+(t^2) avec x,y,z,t entiers naturels.
  - Et il existe un système d'équation à 4 inconnues entières.
                       {n = (x)^2
  Pour tout entier n   {n = (y)^2
  strictement positif  {n = (z)^2
                       {n = (t)^2
  On utilise alors les paramètres x, y, z, t comme variables.
  Puis on effectue des boucles dans l'ordre des paramètres.
  */
  unsigned int nombre, racine, x, y, z, t;
  printf("Entrez un nombre strictement positif : ");
  scanf("%u", &nombre);
  do{
    printf("Entrez un nombre NON-NULL ou POSITIF : ");
    scanf("%u", &nombre);
  }while(nombre <= 0);
  /* On calcule la racine carré du nombre saisie car en résolvant une partie du systèmes 
  d'équation, on obtient :
  {n = (x)^2  <=>  x = racine carré (n)
  {n = (y)^2  <=>  y = racine carré (n)
  {n = (z)^2  <=>  z = racine carré (n)
  {n = (t)^2  <=>  t = racine carré (n)
  Soit E((x,y,z,t)^2) = n  <=>  racine carré (n). */
	
  /* On effectue des boucles successives dans l'ordre des paramètres donnés. */
	
  /* Paramètre x initialisé à 1 pour éviter les décompositions en 0^2. */
  for(x=1; x <= sqrt(nombre); x++){
    /* Paramètre y. */
    for(y=x; y <= sqrt(nombre); y++){
      /* Paramètre z initialisé à 0. */
      for(z=0; z <= sqrt(nombre); z++){
        /* Paramètre t. */
        for(t=z; t <= sqrt(nombre); t++){
          /* Si le théroème de Lagrange est vérifié. */
          if(nombre == (pow(x,2) + pow(y,2) + pow(z,2) + pow(t,2))){
            /* Si z et t valent 0, décomposition en deux facteurs au carré. */
            if(z==0 && t==0)
              printf("%u = %u + %u\n", nombre, x*x, y*y);
            /* Si z=0 et t est différent de 0, décomposition en 3 facteurs aux carré. */
            if(z==0 && t!=0)
              printf("%u = %u + %u + %u\n", nombre, x*x, y*y, z*z);
            /* Si z et t sont différents de 0, décomposition en 4 facteurs au carré. */
            if(z!=0 && t!=0)       
              printf("%u = %u + %u + %u + %u\n", nombre, x*x, y*y, z*z, t*t);     
          }
        }
      }
    }
  }
  return 0;
}