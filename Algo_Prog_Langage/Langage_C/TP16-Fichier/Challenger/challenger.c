/* Question 2 : Challenger. 
Écrivez un programme qui prend en argument sur la ligne de commande un score et un nom 
et qui met à jour le fichier top10 de l'exercice précédent.

bob@box:~$ ./a.out 1581427 '>_>'
004867123 BOB
004854739 <O>
002587684 \o/
002483729 KIX
001982491 :-)
001581427 >_>
001444726 ALF
000758162 LOL
000758161 T_T
000048214  GG
*/

#include <stdio.h>
#include <stdlib.h>


int main (int argc, const char *argv[]){

	if (argc!=3){
		printf("usage:%s <long int> <string>\n", argv[0]);
		return EXIT_FAILURE;
	}

	int score, scoring, val_update;
	char login[4]; // Permettera de gérer les 3 caractères des logins.
	FILE *flux, *flux_update; // flux source et flux de destination.   

	score = strtol(argv[1], NULL, 10); // Coversion en entier
    // Ouverture 
  	flux = fopen("top10", "r"); 
  	
  	if (flux == NULL) {
 		perror("Probleme d'ouverture ");
	    exit(0);         
	}
    // Erreur d'ouverture

	while(1){
      
		fread (&scoring, sizeof(int), 1, flux); // Lecutre sur l'entrée standard
		fread (login, sizeof(char), 3, flux);
        /* Repérage de la fin du flux du fichier source. */
		feof(flux); 
		if(feof(flux)) exit(0);
		
		if ((scoring < score) && (val_update > score)) { // Pour le fichier destination
			fwrite (&score, sizeof(int), 1,flux); // Prend 1 eniter : le score
			fwrite (&argv[2], sizeof(char), 3,flux); // Prend 3 caractères : le login
			printf("%09d %s\n", score , argv[2]);
		}
        // Pour le fichier destination
		fwrite (&scoring, sizeof(int), 1, flux);
		fwrite (login, sizeof(char), 3, flux);
		printf("%09d %s\n", scoring, login);
		val_update = scoring; // Tampon du nouveau 
	}
    // Fermeture des flux.
	fclose(flux); 
	return EXIT_SUCCESS;
}