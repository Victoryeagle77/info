/* Question 1 : Utilisation de GDB
sample.c -- Sample C program to be debugged with GDB 
*/
     
#include <stdio.h>
#include <stdlib.h>

void shell_sort(int a[], int taille){
        int i, j;
        int s = 1;
        do{
            s = s * 3 + 1;
        }while (s <= taille);
        do{
            s /= 3;
            for (i = s; i < taille; i++){
                int v = a[i];
                for (j = i; j >= s && a[j - s] > v; j -= s)
                    a[j] = a[j - s];
                if (i != j)
                    a[j] = v;
            }
         }while (s != 1);
     }
     
int main(int argc, char const *argv[]){
    int *a;
    int i;
    a = (int *)malloc((argc - 1) * sizeof(int));
    for (i = 0; i < (argc - 1); i++)
        a[i] = atoi(argv[i + 1]);

    shell_sort(a, argc); // Résultat de sorti du terminal

    for (i = 0; i < (argc - 1); i++)
        printf("%d ", a[i]);
    printf("\n");

    free(a);
    return 0;
}

/***** DEBOGUAGE ******/

/* Pour commencer on tape dans l'invite de commande (dans le répertoire de ce fichier) : 

---> Manuel <---
-> breakpoint :    b   <Numéro de la ligne>
Permet de marquer une ligne et de faire suivre l'exécution,
à partir de celle-ci.
-> run :           r
Permet de lancer un programme dans (gdb)
-> print :         p   <Nom de variables>
Permet d'afficher la valeur d'une variable,
à n'importe quel endroit d'un programme après le breakpoint.
-> backtrace :     bt 
-> list :          l   <Numéro de la ligne>
Permet d'afficher une liste de lignes en inscrivant le numéro de la dernière.
-> step :          s
Permet la lecture ligne par ligne depuis le breakpoint.

[bob@box TP13-Débogueur]$ gcc -g <programme>
[bob@box TP13-Débogueur]$ gdb ./a.out
Un fois dans gdb, on attérit dans l'intérface de déboguage.
(gdb) b sample.c:8
(gdb) r argv[0] argv[1]...
// Observation des variables
(gdb) s
(gdb) p a[0]
Et ainsi de suite pour afficher l'évolution des variables.
*/