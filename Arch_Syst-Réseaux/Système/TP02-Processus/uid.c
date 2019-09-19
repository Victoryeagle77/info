#include "ressource.h"

/* Processus utilisés : 
  * UID : ID Utilisateur. 
*/
int uid(void){
  printf("\n===> PROCESSUS UID <===\n\n");
  /* typedef uid_t définissant un suffixe à uid : 
  -> ruid = (real uid) L'UID réel.
  -> euid = (efficiant uid) L'UID effectif.
  -> suid = (sleeping uid) L'UID dormant.
  */
  uid_t   ruid, euid, suid;
    
  getresuid(&ruid, &euid, &suid);
  printf("* UID-reel = %u\n* UID-effectif = %u\n* UID-dormant = %u\n",
		    ruid, euid, suid);
  printf("-> setresuid(-1, %u, %u) = %d\n", euid, ruid, setresuid(-1, euid, ruid));
  printf("=================================\n");
  getresuid(&ruid, &euid, &suid);
  printf("* UID-reel = %u\n* UID-effectif = %u\n* UID-dormant = %u\n", ruid, euid, suid);
  printf("-> setresuid(-1, %u, -1) = %d\n", suid, setresuid(-1, suid, -1));
  getresuid(&ruid, &euid, &suid);
  printf("=================================\n");
  printf("* UID-reel = %u\n* UID-effectif = %u\n* UID-dormant = %u\n", ruid, euid, suid);
  return 0;
}
