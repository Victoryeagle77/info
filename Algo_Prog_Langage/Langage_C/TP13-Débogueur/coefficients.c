/*
Vous constaterez que le résultat promis n'est pas affiché. 
À l'aide du débogueur, trouvez dans la mémoire le résultat voulu et 
modifiez uniquement la partie «affichage du résultat» du programme pour qu'il soit affiché. 

Fichier debogueur1.c : exemple a deboguer 

int main(void) {
  int i=-1, j=0, n, k, *mem;
  printf("Calcul de C(n, k) :\n");
  printf("Entrez n : ");
  scanf("%d", &n);
  while(n<1) {
    printf("n doit etre supérieur ou égal à 1 !\n");
    printf("Entrez n : ");
    scanf("%d", &n);
  }
  printf("Entrez k : ");
  scanf("%d", &k);
  while((k>n)||(k<1)) {
    printf("k doit etre compris entre 1 et %d !\n", n);
    printf("Entrez k : ");
    scanf("%d", &k);
  }
  mem = (int *) malloc(n*sizeof(int));
  while (i<n)
    if(j<1)
      *(mem+(j=i++)+1) = 1;
    else
      *(mem+j--) += *(mem+j);

  printf("C(%d, %d) = ???\n", n, k);
  free(mem);
  return EXIT_SUCCESS;
}
*/

#include <stdio.h>
#include <stdlib.h>

/* fonction principale */
int main(void) {
  int i=-1, j=0, n, k, *mem;
  /* invite */
  printf("Calcul de C(n, k) :\n");
  /* saisie de n */
  printf("Entrez n : ");
  scanf("%d", &n);
  while(n<1) {
    printf("n doit etre supérieur ou égal à 1 !\n");
    printf("Entrez n : ");
    scanf("%d", &n);
  }
  /* saisie de k */
  printf("Entrez k : ");
  scanf("%d", &k);
  while((k>n)||(k<1)) {
    printf("k doit etre compris entre 1 et %d !\n", n);
    printf("Entrez k : ");
    scanf("%d", &k);
  }
  /* reservation de la place memoire necessaire */
  mem = (int *) malloc(n*sizeof(int));
  /* calculs... */
  while (i<n)
    if(j<1)
      *(mem+(j=i++)+1) = 1;
    else
      *(mem+j--) += *(mem+j);
  /* affichage du resultat */
  printf("C(%d, %d) = %d\n", n, k, *mem);
  /* liberation de la memoire */
  free(mem);
  return EXIT_SUCCESS;
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
(gdb) b coefficients.c:6
(gdb) r
// Observation des variables
(gdb) s
(gdb) p <Variables(i, j, k, n) | Pointeurs(*p)>
Et ainsi de suite pour afficher l'évolution des variables.

- En tapant gdb :
(gdb) p *mem
(gdb) s
Successivement tout au long du programme, 
on voit le contenu du tableau pointé *mem et on constate qu'il vaut toujours 1.

- On se rend compte aussi, en faisant seulement :
(gdb) l 30
qu'il manque une définition de varaible.
printf("C(%d, %d) = ???\n", n, k);
On remplace donc cette ligne par printf("C(%d, %d) = %d\n", n, k, *mem);
*/
