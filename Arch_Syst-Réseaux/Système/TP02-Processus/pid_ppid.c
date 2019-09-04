#include "ressource.h"

/* Processus utilisés : 
* PID = ID du processus
* PPID = ID du processus parent ou PPID. 
*/
int pid_ppid(void){
  printf("\n===> PROCESSUS PID-PPID FILS/PARENT <===\n\n");
  /* typedef pid_t définissant un suffixe à pid, ici un processus fils. */
  pid_t	pid_fils;
  /* Conditionnement pour initialiser le fork tant que le processus fils est actif. */
  do { pid_fils = fork(); } 
  while ((pid_fils == -1) && (errno == EAGAIN));
  // Erreur si le processus fils est non-actif.
  if (pid_fils == -1){
    fprintf(stderr, "Erreur fork <-> errno = %d\n", errno);
    return -1; // Retourne avec échec
  }
  /* Dans le cas du processus FILS */
  if (pid_fils == 0){
  /* fprintf permet l'affichage avec type d'erreur ou de success,
  sur l'entrée ou la sortie standard. 
  On prévoit ici un format de type (long) pour les gros processus. */ 
  fprintf(stdout, "\n[ PROCESSUS FILS ]\n* PID = %ld\n* PPID = %ld\n",
	  (long)getpid(), (long)getppid());
  return 0; // Retourne avec success
  /* Si le processus n'est pas fils, traité le cas du processus parent en premier */
  } else { 
     fprintf(stdout, "[ PROCESSUS PARENT ]\n* PID = %ld\n* PPID = %ld\n* PID_FILS = %ld\n",
	     (long)getpid(), (long)getppid(), (long)pid_fils);
     return 0;
  }
}
