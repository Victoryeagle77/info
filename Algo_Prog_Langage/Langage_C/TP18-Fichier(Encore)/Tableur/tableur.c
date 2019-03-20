/*
Question 2 : Tableur. 
Un fichier au format CSV sert à décrire un tableau de valeurs à deux dimensions. 
Les valeurs sont séparées par des virgules (ou parfois des points-virgule en configuration française) 
et forment ainsi des lignes. Les lignes sont bien sûr séparées par des sauts de ligne.

Faites 3 tableaux multidimensionnels et sauvegardez les tableaux dans des fichiers nommés t1.csv, t2.csv, et t3.csv. 
Si vous respectez bien le format, vous devriez pouvoir ouvrir ces fichiers à l'aide d'un tableur. 
*/


#include<stdio.h>
#include<string.h>

///////// Paramètrage des tableaux selon t[x][y] /////////

void t1_csv(char *fichier){
  int t1[2][5];
  int i, x, y, z;
  FILE *flux;
  flux=fopen(fichier, "w+");
  // Pour le tableau 1 //
  for (i = 0; i < 2; ++i){ // Paramètre [x] de t1[x][y]
    y=1;
    for (x = 0; x < 5; ++x){ // Paramètre [y] de t1[x][y]
      t1[i][x]=y;
      y++;
    }
  }
  // Tableau 1 
  fprintf(flux, "%8.st1\n");
  for (i = 0; i < 2; ++i){
    for (x = 0; x < 5; ++x) { fprintf(flux, "%3d,", t1[i][x]); }
    fprintf(flux, "\n");
  }
  fprintf(flux, "\n");

  fclose(flux);
  printf("\nFichier %s cree", fichier);
}

void t2_csv(char *fichier){
  int t2[3][5];
  int i, x, y, z;
  FILE *flux;
  flux=fopen(fichier, "w+");
 
  // Pour le tableau 2 //
  y=1; 
  for (i = 0; i < 3; ++i){ // Paramètre [x] de t2[x][y]
    for (x = 0; x < 5; ++x){ // Paramètre [y] de t2[x][y]
      t2[i][x]=y;
      y++;
    }
  }
  // Tableau 2 
  fprintf(flux, "%8.st2\n");
  for (i = 0; i < 3; ++i){
    for ( x = 0; x < 5; ++x) { fprintf(flux, "%3d,", t2[i][x]); }
    fprintf(flux, "\n");
  }
  fprintf(flux, "\n");

  fclose(flux);
  printf("\nFichier %s cree", fichier);
}

void t3_csv(char *fichier){
  int t3[5][5];
  int i, x, y, z;
  FILE *flux;
  flux=fopen(fichier, "w+");
  
  // Pour le tableau 3 //
  y=0;
  for (i = 0; i < 5; ++i){ // Paramètre [x] de t3[x][y]
    z=0;
    for ( x = 0; x < 5; ++x){ // Paramètre [y] de t3[x][y]
      if (y<i && z==0){ y++; }
      else { y=0, z=1; }
      t3[i][x]=y;
    }
  }
  // Tableau 3 
  fprintf(flux, "%8.st3\n");
  for (i = 0; i < 5; ++i){
    for ( x = 0; x < 5; ++x) { fprintf(flux, "%3d,", t3[i][x]); }
    fprintf(flux, "\n");
  }
  fprintf(flux, "\n");
     
  fclose(flux);
  printf("\nFichier %s cree", fichier);
 
}

int main(){
    char fichier[BUFSIZ];
    printf("\n== Fichier csv ==\n"); 
    t1_csv("t1.csv");
    t2_csv("t2.csv");
    t3_csv("t3.csv");
    putchar('\n');
    return 0;
}
