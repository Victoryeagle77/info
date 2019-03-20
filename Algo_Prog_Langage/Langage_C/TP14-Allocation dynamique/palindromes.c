/*
Question 2 : Palindromes. 
Écrivez un programme qui teste si les arguments passés sur sa ligne de commande sont des palindromes. Vous vous appuierez sur la fonction suivante :

char* inverse(const char* s);

Cette fonction, que vous devrez définir, doit créer et renvoyer une chaîne contenant les mêmes caractères que s mais en ordre inverse. Exemple de session :

bob@box:~$ ./a.out laval denis luc radar
laval est un palindrome,
denis n'est pas un palindrome,
luc n'est pas un palindrome,
radar est un palindrome.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* inverse(const char* s){
    int length;
    char *tab; // Tableau de caractère pointé
    length = strlen(s); // Longueur de la chaine de caractère s.
    tab = (char*)malloc(length*sizeof(char)); // Allocation de la longueur chaine de caractère.
	
    for (int i = 0; i < length; i++)
	 tab[i]=s[length-i-1]; // Inverse la chaine de caractère s.

    return tab; 
}

int main (int argc,char const *argv[]){

	int i, y, length;
	int test = 1; // Variable de test booléen vérifiant la validité de l'inversion
	char *tab; // Tableau de caractère pointé

	if (argc != 2){
		printf("usage:%s <string> ...\n", argv[0]);
		return EXIT_FAILURE;
	}

	for (i = 1; i < argc; i++){
		
		length = strlen(argv[i]); // Longeur de la chainer de caractère de l'argument
		tab = inverse(argv[i]); // Inverse l'argument de ligne de commande.
		
		for (y = 0; y < length; y++) { 
		/* Le test booléen vaut 0 si l'inversion n'est pas égale à l'inversion des caractère de l'argument */
                     if (tab[y] != argv[i][y]) { test=0; }  
		}

		if (test) { printf("%s est un palindrome.\n", argv[i]); } 
	        else { printf("%s n'est pas un palindrome.\n", argv[i]); }
		test = 1; // Réinitialisation à 1 pour la prochaine exécution.
		// Libération de l'espace mémoire.
		free(tab);
	}
	return EXIT_SUCCESS;
}
