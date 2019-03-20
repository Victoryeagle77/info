/*
Question 2.5 : Bissextile 
Une année bissextile se déroule tous le 4 ans. Une année bissextile est donc multiple de 4.
Faire un programme affichant si une année est bissextile ou pas.
Premièrement n'utilisez pas une structure conditioinnelle avec else puis ensuite faites le avec une structure conditionnelle.
*/

#include <stdio.h>
#include <stdlib.h>

#define BISSEXTILE 4

int main(void) {

	int annee;
	printf("Entrez une annee : ");
	scanf("%d", &annee);
	printf("\n-> Condition avec expression conditionnel <-\n");
	// Récupère la reste de la division euclidenne
	printf("%s%s", "Annee ", (annee%BISSEXTILE==0) ? "BISSEXTILE\n" : "NON BISSEXTILE\n");
	
	/** La condition (annee==BISSEXTILE) ? "BISSEXTILE\n" : "NON BISSEXTILE\n" correspond à : **/
	printf("-> Condition avec if - else <-\n");
	printf("Annee ");
	if (annee%BISSEXTILE==0)
		printf("%s", "BISSEXTILE\n");
	else
		printf("%s", "NON BISSEXTILE\n");
	return EXIT_SUCCESS;
}
