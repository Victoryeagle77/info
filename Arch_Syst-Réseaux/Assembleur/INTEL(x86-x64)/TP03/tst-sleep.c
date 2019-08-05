/* Question 1 : tst-sleep.c
Ecrivez en C un programme 'tst-sleep.c' qui calcule et affiche
le nombre de tics effectué par ce processeur quand il dort pendant 1 seconde
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

unsigned long nbtic() {
  unsigned long tic;
  __asm__(
    /* rdtsc permet déjà de relever les cycles du processeur */
    "rdtsc\n\t"
    /* décalage sur la gauche de la valeur sur 32 bit */
    "shlq $32,%%rdx\n\t"
    "movl %%eax,%%edx\n\t"
    "movq %%rdx,%%rax\n\t"
    : "+r" (tic) 
  );
  return tic;
}

int main(void) {
  time_t rawtime;
  unsigned int temps,cycle;
  unsigned long t0,t1,t2;
  temps=time(&rawtime);
  t2=0;
  t0=nbtic();
  do {
    cycle=time(&rawtime);
  } while (cycle<=temps);
  t1=nbtic();
  printf("temps = %u && cycle = %u\n", temps, cycle);
  printf("1 sec = %lu tics\n", t1-t0);
  return EXIT_SUCCESS;
}
