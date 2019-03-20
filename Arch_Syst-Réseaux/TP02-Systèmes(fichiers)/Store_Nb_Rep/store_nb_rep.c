/*
Question 4 :
Créer Un programme store_nb_rep.c qui saisit des nombres entiers 32 bits, par interaction 
avec l’utilisateur en utilisant la fonction scanf dans une boucle.
La representation 32 bits de chaque nombre saisi est enregistrée à l’aide de l’appel
système 'write', l’une à la suite de l’autre, dans un fichier dont le nom a été donnée
en argument à l’executable. La gestion des erreurs doit tre réalisée. Le programme créé le
fichier s’il n’existe pas et le tronque s’il existe.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[]){
    int flux, chiffre, nombre = 0;
    int *taille = NULL; // Initialisation du tableau d'entier taille à NULL

    system("clear");

    if (argc != 2){
       fprintf(stderr, "Usage : %s <file_name>\n", argv[0]);
       exit(0);
    }
    /* Ecriture + Création si fichier inexistant + Troncature du contenu (vaudra 0) 
    + Permition en chmod 600 */
    flux = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0600);
    
    if(flux == 1){
        perror("Echec d'ouverture du fichier ");
        exit(2);
    }
    
    printf ("Nombre de chiffre a saisir : ");
    scanf ("%d", &nombre);
    // Définition de malloc pour entrer le nombre souhaité d'entiers
    taille = malloc(sizeof(int) * nombre);

    for(chiffre=0; chiffre<nombre; chiffre++){
      printf("Numb --> ");
      scanf("%d", &taille[chiffre]);
      write(flux, &taille[chiffre], sizeof(int)); // Taille d'un entier de 32 bits écrits dans unsss fichier
    }
    
    free(taille); // Libération de l'espace mémoire pris par le malloc().
    close(flux);
    exit(0);
}