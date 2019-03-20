/*
Question 5 : Couverture.
Lorsqu'une compagnie d'assurance prend en charge des réparations, elle laisse une franchise à la charge de l'assuré.
Celle-ci est égale à 10% du montant des réparations, avec un minimum de 200€ et un maximum de 800€.
	
	réparations 	part assuré (franchise) 	part assurance

	150,00€ 		150,00€ 					0,00€
	250,00€ 		200,00€ 					50,00€
	2500,00€ 		250,00€ 					2250,00€
	10000,00€ 		800,00€ 					9200,00€

Écrivez un programme qui demande le montant total des réparations, puis affiche la franchise correspondante ainsi que la part prise en charge par l'assurance. 
*/


#include <stdio.h>
#include <stdlib.h>

#define MIN 200
#define MAX 800

int main(void){
	double montant_rep, franchise, assurance;
	printf("Entrez le montant des reparations : ");
	scanf("%lf", &montant_rep);
	// Les 10% de la franchise -> Opération castée en entier
	franchise = (int)(montant_rep/10);

	if(franchise < MIN){
		if(montant_rep > MIN)
			franchise = MIN;
		else
			franchise = montant_rep;
	}else if (franchise > MAX)
		franchise = MAX;

	assurance = montant_rep - franchise;
	
	printf("Reparations = %.2lf euros | Franchise = %.2lf euros | Assurance = %.2lf euros\n", montant_rep, franchise, assurance);
	return EXIT_SUCCESS;
}