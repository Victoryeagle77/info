/**** Appel des processus ****/

#ifndef process_h
#define process_h

/* Header fournissant les librairies aux fichiers et fonction
nécessaire (dont de l'assembleur) défines dans les fichiers */
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

int sid_pgid();
int pid_ppid(void);
int gid(void);
int uid(void);

#endif
