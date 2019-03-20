/* Question 3 : Copie. 
Faire un programme copiant le contenu d'un fichier dans un ature.
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[]){ 
    FILE* flux_source; // Flux du fichier de départ.
    FILE* flux_destination; // Flux du fichier dans lequel on veut placer le flux du fichier de départ.
    char buffer[256]; 
    int lecture; 
    
    if (argc != 3) { 
        printf("Usage : %s <source_file.txt> <destination_file.txt>\n", argv[0]);
        exit(0);
    }

    printf("\n=== COPIE DE FICHIER ===\n\nCopie finie");
    
    // Conditionnement pour géré les erreurs d'ouverture du fichier source.
    if ((flux_source = fopen(argv[1], "r")) == NULL) { // Lecture seulement 
        perror("Erreur de fichier ");  
        return 1; 
    } 
    // Conditionnement pour géré les erreurs d'ouverture du fichier destination.
    if ((flux_destination = fopen(argv[2], "w+")) == NULL) { // Ecriture + lecture
        fclose(flux_source); // Fermeture du flux pointé
        perror("Erreur de fichier "); 
        return 2; 
    } 
    // Boucle permettant d'écrire le flux de donné du premier fichier vers le deuxième avec fwrite.
    while ((lecture = fread(buffer, 1, 256, flux_source)) != 0) 
        fwrite(buffer, 1, lecture, flux_destination); // Concaténation de l'écriture d'un flux à un autre.

    /* Fermeture des flux de donnés des 2 fichiers */
    fclose(flux_destination);
    fclose(flux_source); 
    
    return 0; 
}
