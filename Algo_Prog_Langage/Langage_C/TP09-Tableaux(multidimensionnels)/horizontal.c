/*
Question 2 : Horizontale
     t1 		       t2 	         		t3
 1 2 3 4 5 		 1  2  3  4  5 			0   0   0   0   0
 1 2 3 4 5		 6  7  8  9  10 		1   0   0   0   0
  			 11 12 13 14 15 		1   2   0   0   0
  	 						1   2   3   0   0
  	 						1   2   3   4   0

Affichez ces tableaux côte-à-côte (comme sur la figure ci-dessus). 
*/

#include <stdio.h>

int main (void){
	int t1[2][5];
	int t2[3][5];
	int t3[5][5];
	int i,x,y,z;
	
        ///////// Paramètrage des tableaux selon t[x][y] /////////
	
	/* Boucles pour ne pas utiliser de if() */
	
	// Pour le tableau 1 //
	for (i = 0; i < 2; ++i){ // Paramètre [x] de t1[x][y}
		y=1;
		for (x = 0; x < 5; ++x){ // Paramètre [y] de t1[x][y]
		      t1[i][x]=y;
		      y++;
		}
	}

	y=1; // Pour le tableau 2 //
	for (i = 0; i < 3; ++i){ // Paramètre [x] de t2[x][y]
              for (x = 0; x < 5; ++x){ // Paramètre [y] de t2[x][y]
	             t2[i][x]=y;
		     y++;
	      }
	}

	y=0; // Pour le tableau 3 // 
	for (i = 0; i < 5; ++i){ // Paramètre [x] de t3[x][y]
		z=0;
		for (x = 0; x < 5; ++x){ // Paramètre [y] de t3[x][y]
			if (y<i && z==0) { y++; }
			else { y=0, z=1; }
			t3[i][x]=y;
		}
	}	
	
	// Pour les trois tableaux //
	printf("%8.st1%16.st2%16.st3\n"); 
	for (i = 0; i < 5; ++i){
            // Tableau 1
	    for (x = 0; x < 5; ++x){
		    if (i<2) { printf("%3d", t1[i][x]); }
		    else { printf("%3.s"); }
		}
		printf("%3.s");
 	
 	    // Tableau 2	
	    for (x = 0; x < 5; ++x){
		if (i<3) { printf("%3d", t2[i][x]); }
		else { printf("%3.s"); }
	    }
	    printf("%3.s");
		
	    // Tableau 3
	    for (x = 0; x < 5; ++x) { printf("%3d", t3[i][x]); }
	    putchar('\n');
	}
        return 0;
}
