/*
Question 1 : Processus
Faites un programme, à l'aide de la librairie procédurale "unistd", affichant les processus : 
PID, le PPID, le PGID, le TTY, l'UID et le GID.
*/

#include "ressource.h"

int main(int argc, char const *argv[]) {
  system("clear");
  printf(" ---------------------------------\n");
  printf(" --- INFORMATIONS PROCEDURALES ---\n");
  printf(" ---------------------------------\n");
  printf("\n==> SORTIE STANDARD TTY <==\n");
  printf("\n* TTY = %s\n", ttyname(0)); // ttyname prend l'entrée standard pour obtenir le tty d'un processus.
  gid();
  uid();
  sid_pgid(argc, argv);
  pid_ppid();
  return 0;
}
