/*
Question 1 : Progressions. 
Écrivez un programme où les tableaux t1, t2 et t3 contiennent les valeurs suivantes : 

    t1             t2               t3
 1 2 3 4 5    1  2  3  4  5      0 0 0 0 0
 1 2 3 4 5    6  7  8  9  10     1 0 0 0 0
              11 12 13 14 15     1 2 0 0 0
                                 1 2 3 0 0
                                 1 2 3 4 0

Utilisez des boucles (pas des listes) pour placer ces valeurs dans les tableaux. 
Affichez les tableaux les uns au-dessus des autres. Puis affichez-les à nouveau, 
en inversant lignes et colonnes. 
*/

#include <stdio.h>

int main (void){
  int t1[2][5];
  int t2[3][5];
  int t3[5][5];
  int i, x, y, z;

  /**** Paramètrage des tableaux selon t[x][y] ****/
        
  /* Boucles pour ne pas utiliser de conditions if() */

  /* Pour le tableau 1 */
  for (i=0; i<2; ++i){ /* Paramètre [x] de t1[x][y] */
    y=1;
    for (x=0; x<5; ++x){ /* Paramètre [y] de t1[x][y] */
      t1[i][x]=y;
      y++;
    }
  }
  /* Pour le tableau 2 */
  y=1;
  for (i=0; i<3; ++i){ /* Paramètre [x] de t2[x][y] */
    for (x=0; x<5; ++x){ /* Paramètre [y] de t2[x][y] */
      t2[i][x]=y;
      y++;
    }
  }
  /* Pour le tableau 3 */
  y=0;
  for (i=0; i<5; ++i){ /* Paramètre [x] de t3[x][y] */
    z=0;
    for (x=0; x<5; ++x){ /* Paramètre [y] de t3[x][y] */
      if (y<i && z==0){ y++; }
      else { y=0, z=1; }
      t3[i][x]=y;
    }
  }

  /* Tableau 1 */
  printf("%8.st1\n");
  for (i=0; i<2; ++i){
    for (x=0; x<5; ++x) { printf("%3d", t1[i][x]); }
    printf("\n");
  }
  printf("\n");
  /* Tableau 2 */
  printf("%8.st2\n");
  for (i=0; i<3; ++i){
    for (x=0; x<5; ++x) { printf("%3d", t2[i][x]); }
    printf("\n");
  }
  printf("\n");
  /* Tableau 3 */
  printf("%8.st3\n");
  for (i=0; i<5; ++i){
    for (x=0; x<5; ++x) { printf("%3d", t3[i][x]); }
    printf("\n");
  }	
  printf("\n");

  /**** Tableaux inverses ****/
	
  /* Tableau 1 inverse */
  printf("t1 inverse\n");
  for (i=0; i<5; ++i){
    for (x=0; x<2; ++x) { printf("%4d", t1[x][i]); }
    printf("\n");
  }
  printf("\n");
  /* Tableau 2 inverse */
  printf("t2 inverse\n");
  for (i=0; i<5; ++i){
    for (x=0; x<3; ++x) { printf("%3d", t2[x][i]); }
    printf("\n");
  }
  printf("\n");
  /* Tableau 3 inverse */
  printf("%3.st3 inverse\n");
  for (i=0; i<5; ++i){
    for (x=0; x<5; ++x) { printf("%3d", t3[x][i]); }
    printf("\n");
  }
  return 0;
}