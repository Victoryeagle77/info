/* Question 1 : Lecture simple d'un fichier.
Faire un programme lisant le contenu d'un fichier dont le chemin sera l'argument (argv) de la ligne de commande.
On ouvrira le flux de donné avec "open", par tranche de 256 octets.
"read" sera nécessaire pour lire le flux de donnné du fichier, et "write" pour l'afficher.
On gérera les erreurs d'appel systèmes et du manque d'argument de commande.
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> // Librairie d'appel système de getsion de fichier
#include <unistd.h>

int main(int argc, char const *argv[]){
    unsigned int flux; 
    char buffer[256]; // Permettera de ranger les données (caractères) du flux.
    int taille; // Taille du buffer
    system("clear");

    if (argc != 2) { 
        printf("Usage : %s <file_name.txt>\n", argv[0]);
        exit(0);
    }
    /* Récupération d'un flux sur le fichier */
    flux = open(argv[1], O_RDONLY); // Lecture seulement du fichier.

    if (flux != -1){ // Il ne peus pas y avoir de flux négatif.
        /* LECTURE FICHIER
        Passage à read des données suivantes :
        - le flux,
        - le buffer,
        - la taille du buffer.
        */
        taille = read(flux, buffer, 256);
        buffer[taille] = 0; // Taille du buffer initialisé à 0 pour le future stockage.

        /* AFFICHAGE FICHIER
        Affichage des éléments lus dans la console :
        Le flux 1 est la sortie standart (console).
        */
        write(1, buffer, taille);
        /* Fermeture du flux de donné */
        close(flux);

     } else {
          perror("/!\\ Lecture impossible "); // Retournera automatiquement l'erreur correspondante.
          return -1;
     }

     return 0;
}

