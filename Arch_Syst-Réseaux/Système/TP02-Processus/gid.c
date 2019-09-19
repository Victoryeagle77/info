#define _DEFAULT_SOURCE

#include "ressource.h"

/* Processus utilisés : 
* ID du groupe de processus. 
*/
int gid(void){
  int taille, i;
  gid_t *table_gid = NULL;
  // typedef d'un tableau d'argument argv[] pointé initialisé à NULL. 
  printf("\n===> PROCESSUS GID <===\n\n");
  /* getgroups() identifie le groupe de processus.
  /!\ NOTE /!\ Cette partie de code est intéressante en localhost, 
  mais marche aussi en partie en connexion avec résultat constant. */  
  fprintf(stdout, "PID = %ld <--> GROUPE = %ld\n", (long)getpid(), (long)getpgrp());
  /* S'il n'y a pas de groupe de processus. */
  if ((taille = getgroups(0, NULL)) < 0) {
    fprintf(stderr, "Erreur getgroups, errno = %d\n", errno);
    return -1;
  }
  if ((table_gid = calloc(taille, sizeof(gid_t))) == NULL) {
    fprintf(stderr, "Erreur  calloc, errno = %d\n", errno);
    return -1;
  }
  if (getgroups(taille, table_gid) < 0) {
    fprintf(stderr, "Erreur getgroups, errno = %d\n", errno);
    return -1;
  }
  printf("- Groupe de processus : \n");
  for (i = 0; i < taille; i ++)
    /* Affiche un tableau de groupe de processus à l'instar de la fonction getpgrp(); */
    fprintf(stdout, "%u ", table_gid[i]);
  putchar('\n');
  free(table_gid);
  return 0;
}
