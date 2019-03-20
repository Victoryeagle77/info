/*
Question 3 : Hexadécimal. 
La commande hexdump permet l'affichage d'un fichier à la console, dans le cas où le fichier ne contient pas que du texte. 
Chaque ligne contient les valeurs de 16 octets du fichier affichés en notation hexadécimale.

Écrivez un programme qui donne le même résultat que hexdump (sans option).
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
 
#define CHAINE 16 // 16 bytes par rangée
// Il faut écrire la signature de la fonction 'bytes' pour en faire une valeur de variable.
int bytes(FILE *flux, char rangee[], int size);
 
// Imprime le contenu d'un fichier au format hexadécimal
void hexdump(FILE *flux){
    int taille;
    while (taille > 0){
        char rangee[CHAINE + 1]; // Compte +1 pour le caractère vide '\0'
        taille = bytes(flux, rangee, CHAINE);
        if (taille > 0){
           /* Affiche la version hexadécimale des caractères d'une chaîne
           Imprime toujours les valeurs limites, initialisé à 0 pour les valeurs supérieures à taille. */
           for (int i = 0; i < CHAINE; i++){
                int value = rangee[i];
                if (i >= taille) { value = 0; }
                printf("%02x ", value); // Affiche les valeurs en hexadécimal.
            }
            // Imprimer une version d'affichage de la chaîne
            printf("%10.s");
            for (int i = 0; i < taille; i++){
            /* Rendre un caractère imprimable, même s'il s'agit d'espaces.
            isspace(int) venant de ctypes.h vérifie s'il y a espace ou non. */
               if (isspace(rangee[i])){ putchar('\0'); }
               else { putchar(rangee[i]); /* Affichera la chaine de caractère, le texte du fichier */}
            }
            putchar('\n');
        }
    }
}
 
/* Lire les octets de taille dans une chaîne
Retourne le nombre d'octets lus. */
int bytes(FILE *flux, char rangee[], int size){
    int taille = 0;
    int carac;
    // fgetc lit ici caractère par caractère dans le flux de donnés du fichier. 
    while (taille < size && (carac = fgetc(flux)) != EOF) 
    	// Vérification qu'il n'y a pas fin de fichier
        rangee[taille++] = carac;

    rangee[taille] = '\0';
    return taille;
}

int main(void){
    printf("\n=== HEXDUMP ===\n");
    // fputs prend directement une chaine de caractère sur la sortie standard.
    fputs("Nom du fichier a convertir : ", stdout);
    /* La valeur de cette macro est une expression constante entière pratique à utiliser comme argument de taille. 
    Cette valeur est garantie être au moins 256. Elle est présente de base dans <stdio.h>.
    La valeur de BUFSIZ est choisie sur chaque système afin de rendre les entrées / sorties de flux plus efficaces. */
    char fichier[BUFSIZ];
    if (fgets(fichier, BUFSIZ, stdin) != NULL){
 
        if (fichier[strlen(fichier) - 1] == '\n')
            fichier[strlen(fichier) - 1] = '\0';
         
        FILE *flux = fopen(fichier, "r"); // Lecture
        printf("\n --> hexdump -c %s\n\n", fichier);
        // Effectue hexdump si le fichier existe.
        if (flux != NULL){
            hexdump(flux);
            fclose(flux);
        }
    }
    return 0;
}
