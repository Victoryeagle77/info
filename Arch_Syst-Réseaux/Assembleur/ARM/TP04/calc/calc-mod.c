/*
Questions 2 : Calculateur

Le fichier 'func-def.txt' contient la definition recursive de la fonction 
f: NxN->Z (c.a.d. les arguments sont les entiers naturels, 
la valeur est un entier signe). Le fichier 'argXY.dat' contient un entier non-signe, soit K, en format machine. 
Il vous faut ecrire un programme en assembleur ARM,
qui calcule les valeurs de la fonction 'f' pour tous les couples des arguments :
<i,j> tels que 0<=i<=K et 0<=j<=K.

  (1) Ecrivez en C un programme 'calc-mod.c' qui fait le calcul demandé et qui:
      (a) Affiche les resultats pour que nous puissions les voir
      (b) Met les resultats dans le fichier 'res-c.dat';
  Celui-ci devra être compilable à la main en pré-assembleur 
  (avec étiquettes remplacant toutes les conditions et les boucles).

  (3) Faites ensuite le programme 'calc.s' en assembleur ARM,
   qui calcule la même fonction et qui met les resultats dans le fichier 'res-s.dat'.

*/

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int calc(unsigned int x, unsigned int y) {
  int v, res, z;
  if (x==0) { goto Sortie; }
  if (y==0) { goto Result_x; }
  res = x*y; x--;
  v = calc(x,y);
  y--;
  z = calc(x,y);
  res *= z; res -= v;
  goto Resultat;

  Result_x:
    res=x;
    /* return x */
    goto Resultat;
  Sortie:
    res=1;
    /* return 1 */
    goto Resultat;
  Resultat:
    return res;
}

int main(void) {
  unsigned int k, i=0, j=0;
  int r, fd, res;
  /* Ouverture du fichier arg.dat */ 
  fd = open("arg.dat", O_RDONLY, 0444);
  if (fd > 0) { goto Lecture; }
  return 1;

  Lecture:
    /* Lecture sur la sorite standard du file descriptor */
    res = read(fd, &k, 4);
    if (res==4) { goto Analyse; }
    return 2;
    
  Analyse:
    /* Fermeture du fichier arg.dat */ 
    close(fd);
    /* Ouverture du fichier res-c.dat */ 
    fd = open("res-c.dat", O_WRONLY|O_TRUNC|O_CREAT, 0666);
    /* S'il ne reste plus d'éléments à analyser, on passe à l'écriture */
    if (fd>0) { goto Ecriture; }
    return 3;

  Ecriture:
    Boucle:
      r = calc(i, j);
      printf("f(%u, %u) = %d\n", i, j, r);
      /* Ecriture sur la sorite standard du file descriptor */
      res = write(fd, &r, 4);
      if (res == 4) { goto Suite; }
      return 4;

  Suite:
    j++;
    if (j<k) { goto Fermeture; }
    j=0; i++;

  Fermeture:
    if (i<k) { goto Boucle; }
    close(fd);
    return 0;
}