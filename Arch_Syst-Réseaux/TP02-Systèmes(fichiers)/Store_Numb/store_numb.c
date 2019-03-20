/* Question 3 : 
Faites un programme qui demande à l'utilisateur de saisir des nombre entiers, 
qui seront enregistrés puis placés sous forme de texte dans le fichier,
dont le nom a été donné en argument de ligne de commande.
Utilisé une boucle avec "read" dont on sort lorsque l'entrée standard a été détecté.
La gestion des erreurs sera réalisée.
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    system("clear");
    FILE* fichier = NULL;
    int chiffre = 0, nombre = 0;
    int *taille = NULL; // Initialisation du tableau d'entier taille à NULL
        
    if (argc != 2) { 
          printf("Usage : %s <file_name.txt>\n", argv[0]);
          exit(0);
    }

    fichier = fopen(argv[1], "w"); // Ecriture seulement
        
    if (fichier != NULL) {
        printf ("Nombre de chiffre a saisir : ");
        scanf ("%d", &nombre);
        // Définition de malloc pour entrer le nombre souhaité de nombres
        taille = malloc(sizeof(int) * nombre);
        for(chiffre=0; chiffre<nombre; chiffre++){
            printf("Numb --> ");
            scanf("%d", &taille[chiffre]);
            fprintf(fichier, "%d\n", taille[chiffre]);
        }
        free(taille); // Libération de l'espace mémoire pris par le malloc().
        fclose(fichier);
    } else {
        perror("/!\\ Lecture impossible /!\\");
        return -1;
    }
    return 0;
}