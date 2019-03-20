/*
Question 3 : Initiales. 
Écrivez un programme qui affiche la première lettre de chacun de ses arguments. 
*/

#include <stdio.h>

int main(int argc, char const *argv[]){
	int i, j;
	if(argc < 2){
		printf("Usage <string>\n");
		return -1;
	} 
	// Conditionnement pour qu'il y est au moins un argument entré en plus de ./<exécutable>
	for(i = 1; i < argc; i++){ // Commence après ./<exécutable>
  	    printf("Initiale de l'argument [%d] %s = ", i, argv[i]);
	    for(j=0; argv[i][j] != '\0'; j++);
		// Représentant des caractères avec j incrémentés
	    printf("%c\n", argv[i][0]); // Premier caractère d'un argument
	}
	return 0;
}
