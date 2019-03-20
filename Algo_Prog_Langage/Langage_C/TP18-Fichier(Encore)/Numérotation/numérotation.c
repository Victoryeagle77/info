/*
Question 1 : Numérotation. 
Écrivez un programme qui lit un fichier contenant uniquement du texte dont le nom et le chemin seront donnés en argument sur
la ligne de commande puis affiche le contenu du fichier sur sa sortie standard en numérotant chaque ligne.

Pour les esthètes, faites en sorte d'afficher les numéros dans une couleur différente. Utiliser le code d'échappement.
*/

/* Code d'échappement de couleur dans le printf
DEFAULT   = "\033[0m";
HIGHLIGHT = "\033[1m";
UNDERLINE = "\033[4m";
BLINK     = "\033[5m";
BLACK     = "\033[30m";
RED       = "\033[31m";
GREEN     = "\033[32m";
YELLOW    = "\033[33m";
BLUE      = "\033[34m";
PURPLE    = "\033[35m";
CYAN      = "\033[36m";
WHITE     = "\033[37m";
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char* argv[]) {
	FILE* flux;
	int feo=0; 
	char buffer[BUFSIZ];

	if (argc != 2) {
		printf("usage : %s <file_name>\n", argv[0]);
		exit(1);
	}
	flux=fopen(argv[1], "r"); // Ouverture en lecture seule.
	
	if (flux==NULL) {
		perror("Probleme d'ouverture ");
		exit(2);
	}
	for (int i=1; feo != 1; i++) { // feof renvoie vrais s'il n'y a pas d'erreur
		fgets(buffer, BUFSIZ, flux); // Lit un caractère dans le flux de donné du fichier
		feo = feof(flux); // Détecte la fin du flux de donné du fichier
		printf("\033[0mLigne "); // Code d'échappement de couleur par défault (blanc).
		printf("\033[31m%d", i); // Code d'échappement de couleur rouge.
		printf("\033[0m] %s", buffer); // Code d'échappement de couleur par défault (blanc).
	}
	putchar('\n');
	exit(0);
}
