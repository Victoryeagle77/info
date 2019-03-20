/*
Question 1 : Censure
Ecrviez un programme qui prend sur sa ligne de commande le nom et le chemin d'un fichier
contenant uniquement du texte et qui remplace dans ce ficheir tous les "e" par des "X". 
Le programme ne devra pas retenir en mémoire plus d'un carctère à la fois.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Lecture et remplacement des caractères
char* lecture(char* buffer){
    FILE* fichier;
    unsigned int i = 0, chaine = 1;
    char caractere;
    int eof; // Variable entière de fin de fichier
    buffer = (char*)malloc(sizeof(char));
    fichier = fopen("text.txt", "r");
    if(fichier == NULL){
        fprintf(stderr,"Erreur lors de la lecture du fichier\n");
        exit(1);
    }
    while(1){
        eof = feof(fichier);
        if(eof == 1)
            break;
        fread(&caractere, 1, 1 , fichier);
        if(caractere == 'e') { caractere = 'X'; }
        buffer[i] = caractere;
        i++;
        chaine++;
        // Réallocation en cas de dépassement
        buffer = (char*)realloc(buffer, chaine*sizeof(buffer));
    }
    fclose(fichier);
    return buffer;
}

void chaine(char* buffer, unsigned int longueur){
    unsigned int i;
    for(i=0; i < longueur; i++){
        printf("%c", buffer[i]);
    }
}

// Ecrit un nouveau fichier censuré
void censure(char* buffer){
    FILE* fichier;
    unsigned int i;
    fichier = fopen("censure.txt", "w");
    for(i=0;i<strlen(buffer);i++){
        fprintf(fichier, "%c", buffer[i]);
    }
    fclose(fichier);
}

int main(int argc, char* argv[]){
    char* buffer;
    unsigned int i, longueur;
    buffer = lecture(buffer);

    chaine(buffer, strlen(buffer));
    putchar('\n');
    censure(buffer);
    return EXIT_SUCCESS;
}
