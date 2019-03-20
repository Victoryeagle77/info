/*
Question 3 : Diviseur. 
Écrivez un programme qui demande deux entiers naturels à l'utilisateur, puis affiche leur plus grand commun diviseur.

L'algorithme d'Euclide nous donne un bon moyen de faire ce calcul :
Si b = 0,
Sinon,
pgcd(a, b) = a
pgcd(a, b) = pgcd(b, a mod b)
*/


#include <stdio.h>

int main(void){
    int a,b,res,pgcd,tmp;
    // On conditionne a et b pour q'ils soient supérieur à 0.
    do{
        printf("Entrez un entier ""a"" SUPÉRIEUR à 0 : ");
        scanf("%d",&a);
        printf("Entrez un entier ""b"" SUPÉRIEUR à 0 : ");
        scanf("%d",&b);
    }while(a <=0 || b <= 0);
    /* Après avoir donné les 2 entiers. */
    if (a > b){ // Si "a" supérieur à "b".
        pgcd=b;
        // la variable pgcd prend la valeur du plus grand des 2 nombres soit a
        res=a%b;
        // res = a modulo b
    }else{ // Si "b" supérieur à "a".
        pgcd=a;
         // la variable pgcd prend la valeur du plus grand des 2 nombres soit b
        res=b%a;
        // res = b modulo a
    }
    while(res != 0){ // Quand le reste est différent de 0
        // Variable tampon prenant la valeur de la variable pgcd.
        tmp=pgcd; 
        // la varible pgcd prend la valeur du reste de la division euclidienne de a par b (ou b par a)
        pgcd=res;
        // la variable res prend la valeur du reste de la division euclidienne tmp par pgcd
        res=tmp%pgcd;          
    }
    printf("pgcd(%d, %d) = %d\n", a, b, pgcd);
    return 0;
}
