/*
Question 5 : Produit. 
Écrivez un programme qui prend un nombre quelconque d'entiers sur la ligne de commande et affiche leur produit. 
On souhaite que les arguments qui ne sont pas des entiers soient ignorés. 
Lisez la page manuelle de la fonction strtol et servez-vous en pour repérer les arguments inutilisables. 
*/

#include <stdio.h>
#include <stdlib.h>

int produit(int argc, char const *argv[]){
    int x, i, res = 0;
    for(i = 1; i < argc; i++){ // Commence après ./<exécutable>
		// Conversion des arguments en entier de type int
		x = strtol(argv[i], NULL, 10);
		printf("+ %d ", x);
                // Variable tampon additionnant toutes les valeurs des arguments entre elles
		res += x;
	}
	return res; 
}

int main(int argc, char const *argv[]){
    if(argc < 3){
        printf("%s\n", "Usage : <int> <int> ++..");
        return EXIT_FAILURE;
    }
    printf("= %d\n", produit(argc, argv));
    return EXIT_SUCCESS;
}
