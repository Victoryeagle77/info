/*
Question 5.5 : Deuxième. 
Écrivez une fonction qui affiche la deuxième lettre de chacun de ses arguments. 
*/

#include <stdio.h>

int deuxieme(int argc, char const *argv[]){
    int i, j;
    // Conditionnement pour qu'il y est au moins un argument entré en plus de ./<exécutable>
    for(i = 1; i < argc; i++){ // Commence après ./<exécutable>
      	 printf("Deuxieme lettre de l'argument [%d] %s = ", i, argv[i]);
    	   for(j=0; argv[i][j] != '\0'; j++);
    	       // Représentant des caractères avec j incrémentés
    	       printf("%c\n", argv[i][1]); // Deuxième caractère d'un argument
    }
    return 0;
}

int main(int argc, char const *argv[]){
    if(argc < 2){
        printf("%s\n", "Usage : <argv[1]> ++..");
        return -1;
    }
    printf("%c", deuxieme(argc, argv));
    return 0;
}