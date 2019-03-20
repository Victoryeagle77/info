/*
    Question 5 : Magique. 
    Un carré magique est une grille de trois lignes et trois colonnes contenant tous les chiffres de 1 à 9. 
    Si on additionne les trois chiffres sur une ligne, une colonne ou une diagonale, on obtient toujours la même valeur.

    8  3  4
    1  5  9
    6  7  2

    Écrivez un programme qui demande à l'utilisateur la valeur à mettre dans chacune des neuf cases, puis indique si le carré est magique. On s'attachera à vérifier que :

        ° chaque valeur est comprise entre 1 et 9,
        ° aucune valeur n'est répétée,
        ° les sommes des lignes sont identiques,
        ° les sommes des colonnes sont identiques (à la somme trouvée plus haut),
        ° les sommes des diagonales sont identiques (à la somme trouvée plus haut).
*/

#include<stdio.h>

int main(void) {
       int taille = 3;
       int carre[3][3];
       int ligne, colonne = 0;
       int somme_diagonales, somme_lignes, somme_colonnes;
       int test = 0; // Valeur de test déterminant si un carré est magique
     
       printf("\n***** CARRE MAGIQUE *****\n");

       printf("\n-> Carre de taille : %dx%d <-\n", taille, taille);
       
       for (ligne = 0; ligne < taille; ligne++) {
          for (colonne = 0; colonne < taille; colonne++){
            do{ // Chaque valeur est comprise entre 1 et 9
               printf("Entrer la valeur de position -> [%d][%d] : ", ligne, colonne); 
               scanf("%d", &carre[ligne][colonne]);
            }while((carre[ligne][colonne] < 0) || (carre[ligne][colonne] > 9));
          }
       }
       // Affiche le carré
       for (ligne = 0; ligne < taille; ligne++) {
          printf("\n");
          for (colonne = 0; colonne < taille; colonne++)
               printf("%4.1d ", carre[ligne][colonne]);
       }
     
       // Pour les diagonales
       somme_diagonales = 0;
       for (ligne = 0; ligne < taille; ligne++) {
          for (colonne = 0; colonne < taille; colonne++) {
             if (ligne == colonne) { somme_diagonales = somme_diagonales + carre[ligne][colonne]; }
          }
       }
     
       // Pour les lignes
       for (ligne = 0; ligne < taille; ligne++) {
          somme_lignes = 0;
          for (colonne = 0; colonne < taille; colonne++)
               somme_lignes = somme_lignes + carre[ligne][colonne];
          if (somme_diagonales == somme_lignes) { test = 1; }
          else { test = 0; }
       }
     
       // Pour les colonnes
       for (ligne = 0; ligne < taille; ligne++) {
          somme_colonnes = 0;
          for (colonne = 0; colonne < taille; colonne++)
          	   somme_colonnes = somme_colonnes + carre[colonne][ligne];
          if (somme_diagonales == somme_colonnes) { test = 1; }
          else { test = 0; }
       }
       putchar('\n');
       if (test == 1) printf("\n--> Le carre est magique !\n");
       else printf("\n--> Le carre n'est pas magique !\n");
     
       return 0;
}
