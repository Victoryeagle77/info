/*
Question 4 : Chiffrement. 
Écrivez un programme qui permette de chiffrer/déchiffrer un fichier par la méthode suivante :

 ° les octets de rang pair sont complémentés à 1,
 ° les octets de rang impair sont remplacés par leur xor avec l'octet précédent.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
void source_crypte(FILE *flux_source, FILE *flux_sortie, int clef){
	int car;
	while((car = fgetc(flux_source)) != EOF) { // Vérification qu'il n'y a pas fin de fichier.
	/* Cryptage de chaque caractère par les opérations procédurales XOR et le complément à 1. 
	XOR correspond au ou_exclusif (symbolisé par la touche '^' sur le clavier). 
	Ils manipulent tout deux les données binaires des variables dans la mémoires.
	(les bits des octets constituant les variables en mémoires : les valeurs 1 et 0). 
	En l'occurence ici les caractères présents dans un futur fichier à crypté. */
		int complement = ~car; // Le complément est à 1 de base et est représenté par la touche '~'.
	        // Complément à 1 permet d'inverser tous les bits d'un octet (1 devient 0 et inversement).
		int xor = car ^ clef; // XOR renvoie 0 pour tout bit de même valeur et 1 pour l'inverse.
		fputc(complement, flux_sortie);
		fputc(xor, flux_sortie);
        /* La fonction fputc écrit un caractère caractère dans le flux de donné d'un fichier.
        fputc rend le caractère écrit si l'écriture s'est faite sans erreur, ou EOF en cas d'erreur. */
	}
}
 
void cryptage(const char *source_file, const char *destination_file, int clef){
	FILE *flux_source = fopen(source_file, "r"); // Lecture seule
	if(flux_source == NULL)
		perror("Echec d'ouverture du fichier source ");
	else {
		FILE *flux_sortie = NULL;
		flux_sortie= fopen(destination_file, "w"); // Ecriture seule
		if(flux_sortie == NULL)
			perror("Echec d'ouverture du fichier destination ");
		else{
			source_crypte(flux_source, flux_sortie, clef);
			fclose(flux_sortie);
		}
		fclose(flux_source);
	}
}
 
int main(void) {
	char *file_name, *retour_chariot = NULL;
	int clef;
        printf("\n--> Chiffrement <--\n");
	printf("> Nom du fichier a crypter : ");
        // BUFSIZ est une constante de chaine étant d'au moins 256
	fgets(file_name, BUFSIZ, stdin);
	// Concatène un retour chariot pour mettre un terme au nom du fichier.
	retour_chariot = strchr(file_name, '\n');
        /* Il est nécessaire de demander une clef de cryptage qui sera un nombre entier, 
        pour qu'il y est cryptage efficace en calculant avec XOR. */
        printf("> Entrer une clef de cryptage : ");
	scanf("%d", &clef);

	*retour_chariot = '\0'; // Le \n étant présent, troncature de la chaîne présente.
	cryptage(file_name, "crypte.txt", clef);
	printf ("Cryptage fini !\n");	
	return 0; 
}
