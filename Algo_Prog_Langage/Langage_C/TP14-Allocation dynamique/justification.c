/*
Question 5 : Justification. 
Écrivez une fonction qui lit un mot à la console et le renvoie sous la forme d'une chaîne de caractères. 
Notez que cette fonction devra s'acquitter de sa tâche quelle que soit la longueur du mot. 
Si les premiers caractères lus sont des caractères blancs, ils seront ignorés et sautés.

À l'aide de cette fonction, écrivez un programme qui lit à la console un paragraphe (terminé par un saut de ligne) et qui l'affiche ensuite en une colonne de texte justifié large de 50 caractères. Exemple de session :

bob@box:~$ ./a.out
Entrez votre texte : Lorem ipsum dolor sit amet, consectetur adipisici elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. 
Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. 
Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. 
Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.

Lorem ipsum dolor sit amet, consectetur adipisici
elit,  sed do eiusmod tempor incididunt ut labore
et  dolore magna aliqua. Ut enim ad minim veniam,
quis nostrud exercitation ullamco laboris nisi ut
aliquip  ex ea commodo consequat. Duis aute irure
dolor  in  reprehenderit  in voluptate velit esse
cillum dolore eu fugiat nulla pariatur. Excepteur
sint  occaecat  cupidatat  non  proident, sunt in
culpa  qui  officia  deserunt  mollit anim id est
laborum.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int justification (void *chaine, int longueur_txt) {
    int i;
    unsigned char *buffer = NULL;
    unsigned char *printing = (unsigned char *)chaine;
    // Adaptera la taille à la chaine séléctionnée
    buffer = (char*)malloc(longueur_txt*sizeof(char));
    // Traite chaque octet dans les données.
    for (i = 0; i < longueur_txt; i++) {
        // Multiple de 49 signifie nouvelle ligne (avec décalage de ligne).
        if ((i % 49) == 0) { // Technique de transformation par 49.
            // Ne pas imprimer l'ASCII pour la ligne zéro.
            if (i != 0) { printf ("%s\n", buffer); }
        }

        // Stocke un caractère ASCII imprimable pour plus tard.
        if ((printing[i] > 0x20) || (printing[i] <= 0x7e));
          // On inclus entre un minimum et un maximum --> 0x20 = 32 bits et 0x7e = 126.
            buffer[i % 49] = printing[i];

        buffer[(i % 49) + 1] = '\0';
    }

    // Remplit la dernière ligne s'il n'y a pas exactement 16 caractères.
    for (; (i % 49) != 0; i++);

    // Affiche le dernier bit ASCII.
    printf ("%s\n", buffer);
}

int main (void) {
    char text[BUFSIZ]; // Constante de chaine dans les entrées / sorties standard et d'au moins 256.
    printf("Entrez votre text : ");
    fgets(text, BUFSIZ, stdin);
    putchar('\n');
    justification (&text, strlen(text));
    return 0;
}
