/*
Question 1 : Records. 
Le fichier top10 contient la liste des dix meilleurs scores d'un jeu video ainsi que le sigle des joueurs qui les ont obtenus. 
Les scores sont des entiers au format int little-endian. Les sigles sont formés de trois caractères ASCII tous imprimables. 
Dans le fichier il y a d'abord le score du meilleur joueur, puis son sigle, puis le score du second meilleur joueur, puis son sigle, et ainsi de suite.

Écrivez un programme qui lit ce fichier puis affiche le «Hall of Fame».

bob@box:~$ ./a.out
004867123 BOB
004854739 <O>
002587684 \o/
002483729 KIX
001982491 :-)
001444726 ALF
000758162 LOL
000758161 T_T
000048214  GG
000000001 @_@
*/

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){
        FILE* flux;
        int entier = 0;
        unsigned char buffer[3]; // Futur stockeur des 3 caractère de login des joueurs
        flux = fopen("top10", "r");
        if(flux == NULL){
                printf("Erreur lors de la lecture du fichier\n");
                exit(1);
        }
        for(int j = 0; j < 10; j++){
                fread(&entier, 4, 1, flux); // Lecture de chaque entier
                fread(&buffer, 1, 3, flux); // stock les trois caractères des symboles
                printf("%.9d  %s\n", entier, buffer); // Lecture des données
                entier = 0;
        }
        fclose(flux); 
        return EXIT_SUCCESS;
}
