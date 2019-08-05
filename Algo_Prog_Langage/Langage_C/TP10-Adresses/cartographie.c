/*
Question 1 : Cartographie. 
Écrivez un programme qui déclare des variables de type

    float
    double
    long double
    char
    short int
    int
    long long unsigned int

puis qui affiche l'adresse de chacune d'entre elles.
Faites le plan de la mémoire comme si c'était une avenue et placez-y les variables à l'aide des adresses obtenues.
Que constatez-vous ? Faites plusieurs exécutions d'affilée : qu'est-ce qui ne change pas ?
*/

#include <stdio.h>
#include <stdlib.h>

int main(void){
	float f;
	double d;
	long double ld;
	char c;
	short int si;
	int i;
	long long unsigned int llui;
	printf("/** Adresse des types **/\n");
	// %p et &variable pour afficher l'adresse d'une variable avec printf
	printf("-> float > %p\n-> double > %p\n-> long double > %p\n-> char > %p\n-> short int > %p\n-> int > %p\n-> long long unsigned int > %p\n", &f, &d, &ld, &c, &si, &i, &llui);

/* 
1)
On remarque que la partie 0061FF ne change pas quelque soit l'adresse des types, 
et seul le suffixe change pour identifier une nouvelle adresse.
Les adresses ne sont donc pas distrubué au hasard, après exécution, 
elles sont répartis en fonction de leur disponibilité dans la mémoire.

A l'exécution, une nouvelle adresse est attrbuée à une variable et le suffixe des autres en découle.

On peut imaginer que la cartograpqhie de la mémoire lors de la distribution des adresses ressemble à ceci.

      ----------       Attribution d'une adresse     Corps de l'adresse
      | Memory |_______________EXECUTION________________> 0061FF-- <
      ----------                                                 |
                                                                 <<<<<<<<<<<<<<<>>>>>>>>>>>>>>	
                                                                 < Distribution des adresses >
                                                              < par décalage de la pile après 0a >
                                                                 <<<<<<<<<<<<<<<>>>>>>>>>>>>>>
                                                                 |         * char * 
                                                                 >-------------------------0f               
                                                                 |      * short int * 	
                                                                 >-------------------------0c
                                                                 |        * float *  	  
                                                                 >-------------------------2c
                                                                 |         * int *   
                                                                 >-------------------------08
                                                                 |        * double * 	              
                                                                 >-------------------------20
                                                                 |* unsigned long long int * 	  
                                                                 >-------------------------00
                                                                 |     * long double * 	  
                                                                 >-------------------------10
*/