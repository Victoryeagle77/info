/* Question 3 : ls 
Ecrivez un programme qui permet de lister le contenu d'un répetoire,
vous pouvez recourir à la libraire "dirent.h".
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>	

int main (void){
  char *chaine;
  fgets(chaine, sizeof chaine, stdin);
  DIR * rep = opendir(".");
  if (rep != NULL){
    struct dirent * ent;
    while ((ent = readdir (rep)) != NULL)
      printf ("%s\n", ent->d_name);
    closedir (rep);
  }
  return 0;
}