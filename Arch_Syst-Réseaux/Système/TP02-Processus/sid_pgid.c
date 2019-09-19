#include "ressource.h"

/* Processus utilisés : 
* PID = ID du processus.
* SID = ID d'un groupe de processus.
* PGID = ID  
*/
int sid_pgid(int argc, char const *argv[]) {
  int i;
  long int pid, pgid, sid;
  printf("\n===> PROCESSUS SID-PGID <===\n\n");
  
  if (argc == 1) {
    // getsid et getpgid prennent en argument 0, l'entrée de processus appelant.
    fprintf(stdout, "PID = %d <--> SID = %d\n", getpid(), getsid(0));
    fprintf(stdout, "PID = %d <--> PGID = %d\n", getpid(), getpgid(0));
    return 0;
  }
  /* S'il n'y a pas de PID, il ne peut y avoir les processus PGID et SID prenant en argument le PID */
  for (i = 1; i < argc; i ++)
    if (sscanf(argv[i], "%ld", & pid) != 1)
      fprintf(stderr, "PID invalide : %s\n", argv[i]);
    else {   
      sid = (long) getsid((pid_t) pid);
      pgid = (long) getpgid((pid_t) pid);
      // S'il n'y a pas de PID, erreur de SID.
      if (sid == -1)
	  fprintf(stderr, "PID = %ld inexistant\n", pid);
      else
	  fprintf(stderr, "PID = %ld : SID = %ld\n", pid, sid);
      // S'il n'y a pas de PID, erreur de PGID.
      if (pgid == -1)
        fprintf(stderr, "PID = %ld inexistant\n", pid);
      else
        fprintf(stderr, "PID = %ld : PGID = %d\n", pid, pgid);
    }
    return 0;
}
