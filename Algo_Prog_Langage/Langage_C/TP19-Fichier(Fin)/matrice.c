#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define FNAME "fichier.txt"
 
void saisie_matrice(double **matrice, int m, int n){
    int i,j; 
    // SAISIE DES ELEMENTS DE LA MATRICE
    printf("Enter les elements de la matrice :\n");
    for (i=0; i<m; i++){
        for (j=0; j<n; j++){
            printf("Saisir la valeur de mat[%d][%d] : ", i, j);
            scanf("%lf", &matrice[i][j]);
            printf("\n");
        }
    }
}
 
void affiche_matrice(double **matrice, int m, int n){
    int i,j;
    // AFFICHAGE DE LA MATRICE       
    for (i=0;i<m;i++){
        printf("\n");
        for(j=0;j<n;j++)
            printf("%10lf ", matrice[i][j]);
    }
    printf("\n\n");
}
             
void addition_matrice(double **matrice1, double **matrice2, double **matrice3, int m3, int n3){
    int i,j;
    // ADDITION DE LA MATRICE   
    for (i=0; i<m3; i++){
        for (j=0; j<n3; j++)
            matrice3[i][j]=matrice1[i][j]+matrice2[i][j];
    }
}
     
void produit_scalaire_matrice(double **matrice, double **matrice3, double scalaire, int m, int n){
    int i,j;
    // MULTIPLICATION DE LA MATRICE PAR UN SCALAIRE
    for (i=0; i<m; i++){
        for (j=0; j<n; j++)
            matrice3[i][j]=matrice[i][j]*scalaire;
    }
}
        
int main(void){
    // DECLARATION DES VARIABLES
    FILE *fichier = fopen (FNAME, "w" );
    int i, j, m1, n1, m2, n2, m3, n3;
    double scalaire;
    double **matrice1;
    double **matrice2;
    double **matrice3;
     
    /*** MATRICE 1 ***/
     
    // DECLARATION DE LA TAILLE DE LA MATRICE m * n
    printf("Nombre ligne de la matrice 1: ");
    scanf("%d", &m1);
    printf("\n");
    printf("Nombre de colonne de la matrice 1: ");
    scanf("%d", &n1);
    printf("\n");   
    // CREATION DE m TALBEAU DE n ELEMENTS CHACUN pour la matrice 1
    matrice1 = (double **)malloc(m1*sizeof(double *));
    for (i=0; i<m1; i++){
        matrice1[i]= (double *)malloc(n1*sizeof(double));
    }
    // APPELLE FONCTION SAISIE MATRICE
    saisie_matrice(matrice1, m1, n1);   
    // APPELLE FONCTION AFFICHE MATRICE 7
    printf("\n===> Matrice 1 <===\n");
    affiche_matrice(matrice1, m1, n1);
     
    /*** MATRICE 2 ***/
     
    // DECLARATION DE LA TAILLE DE LA MATRICE m * n
    printf("Nombre ligne de la matrice 2: ");
    scanf("%d", &m2);
    printf("\n");
    printf("Nombre de colonne de la matrice 2: ");
    scanf("%d", &n2);
    printf("\n");   
    // CREATION DE m TALBEAU DE n ELEMENTS CHACUN pour la matrice 1
    matrice2 = (double **)malloc(m2*sizeof(double *));
    for (i=0; i<m2; i++)
        matrice2[i]= (double *)malloc(n2*sizeof(double));
     
    // APPELLE FONCTION SAISIE MATRICE
    saisie_matrice(matrice2, m2, n2);   
    // APPELLE FONCTION AFFICHE MATRICE
    printf("\n===> Matrice 2 <===\n");
    affiche_matrice(matrice2, m2, n2);
     
     
    /*** ADDITION MATRICE ***/     
     
    //VERIFICATION POUR L'ADDITION
    if ((m1 == m2) && (n1 == n2)){    
        n3=n1;
        m3=m1;   
    // CREATION DE m TALBEAU DE n ELEMENTS CHACUN pour la matrice 1
        matrice3 = (double **)malloc(m3*sizeof(double *));
        for (i=0; i<m3; i++)
            matrice3[i]= (double *)malloc(n3*sizeof(double));      
    // APPELLE FONCTION ADDITION
        addition_matrice(matrice1, matrice2, matrice3, m3, n3);   
    }       
    // SI ADDITION IMPOSSIBLE   
    else
        printf("Vous ne pouvez pas additionner les deux matrices\n");       
    // APPELLE FONCTION AFFICHE MATRICE
    printf("\n===> Matrice 3 <===\n");
    affiche_matrice(matrice3, m3, n3);
        
    /*** PRODUIT SCALAIRE MATRICE ***/
     
    n3=n1;
    m3=m1;
    // CREATION DE m TALBEAU DE n ELEMENTS CHACUN pour la matrice 1
    matrice3 = (double **)malloc(m3*sizeof(double *));
    for (i=0; i<m3; i++)
        matrice3[i]= (double *)malloc(n3*sizeof(double));  
    // APPELLE FONCTION PRODUIT SCALAIRE
    printf("Quelle est le votre scalaire : ");
    scanf("%lf", &scalaire);
    printf("\n");
    produit_scalaire_matrice(matrice1, matrice3, scalaire, m1, n1);
    // APPELLE FONCTION AFFICHE
    printf("\n===> Matrice 3 <===\n");
    affiche_matrice(matrice3, m3, n3);   
    system("PAUSE"); 
    return 0;
}