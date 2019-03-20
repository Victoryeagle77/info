/*
Question 3.5 : Écrivez un programme qui affiche la table de multiplication.

  X  |   0   1   2   3   4   5   6   7   8   9  10
-----+--------------------------------------------
  0  |   0   0   0   0   0   0   0   0   0   0   0
  1  |   0   1   2   3   4   5   6   7   8   9  10
  2  |   0   2   4   6   8  10  12  14  16  18  20
  3  |   0   3   6   9  12  15  18  21  24  27  30
  4  |   0   4   8  12  16  20  24  28  32  36  40
  5  |   0   5  10  15  20  25  30  35  40  45  50
  6  |   0   6  12  18  24  30  36  42  48  54  60
  7  |   0   7  14  21  28  35  42  49  56  63  70
  8  |   0   8  16  24  32  40  48  56  64  72  80
  9  |   0   9  18  27  36  45  54  63  72  81  90
 10  |   0  10  20  30  40  50  60  70  80  90 100

Utilisez dans votre programme une constante nommée pour représenter la taille de la table (10 dans l'exemple ci-dessus). 
Votre programme devra encore fonctionner si on choisit une taille différente en changeant la valeur de cette constante. 
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10
#define MIN_SIZE 0

int main(void){
    int y=-1, x=-1, i, hauteur, longueur = MIN_SIZE, res;
    
    printf(" %1.sX  |");
    for (longueur = MIN_SIZE; longueur <= MAX_SIZE; longueur++){
    	y++;
    	printf("%3d ", y);	
    } 	
    putchar('\n');
    
    printf("-----+");
    
    for(int i=0; i<(MAX_SIZE*4)+3; i++)
    	printf("-");

    putchar('\n');
    
    for(hauteur = MIN_SIZE; hauteur <= MAX_SIZE; hauteur++){
	    x++;
	    printf("%3d  |", x);
	    
	    for (longueur = MIN_SIZE; longueur <= MAX_SIZE; longueur++) {
		    res = x*longueur;	
		    printf("%3d ", res);
	    }
	    
	    putchar('\n');
	}
	return EXIT_SUCCESS;
}
