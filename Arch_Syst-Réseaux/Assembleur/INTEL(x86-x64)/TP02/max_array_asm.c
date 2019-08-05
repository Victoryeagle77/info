/* Question 1 : max_array_asm
Faite un programme qui compte le nombre de cycle du processuer,
sur une période passé en argument (en secondes).
Cette argument sera également la dimension d'un tableua,
dont les valeurs seront aléatoires.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int max_array(int *tab, int l){
  int i=0, max=0;
  /*
  *tab => %rax
  l => %rbx
  i => %rcx
  max => %rdx
  */
  asm(
    /* boucle for */
    "boucle:\n\t"
    "cmpq %%rcx,%%rbx\n\t"
    "je fin\n\t"
    /* test du if */
    "cmpq %%rdx,(%%rax)\n\t"
    "jl suite\n\t"
    /* Changement du max */
    "movq (%%rax),%%rdx\n\t"
    /* On incremente l adresse du tableau de 4,
    On incremente le compteur de 1 */
    "suite:\n\t"
    "addq $4,%%rax\n\t"
    "incq %%rcx\n\t"
    "jmp boucle\n\t"
    
    "fin:\n\t"
    
    :"+a" (tab), "+b" (l),"+c" (i),"+d" (max)
    );
  return max;
}

unsigned long tic(void){
  unsigned int hi,lo;
  asm(
    "nop\n\t"
    "xorl %%eax,%%eax\n\t"
    "xorl %%edx,%%edx\n\t"
    "rdtsc\n\t"
    :"=a" (lo), "=d" (hi)
  );
  return (unsigned long) hi<<32|lo;
}


int main(int argc, char ** argv){
  if(argc != 2){
    printf("Usage : %s <unsigned int>\n", argv[0]);
    return EXIT_FAILURE;
  }
  int max,i;
  unsigned long t,T;
  int len = (int) strtol(argv[1],NULL,0);

  int *tab = malloc(len * sizeof(int));
  srand(time(NULL));
  putchar('|');
  for(i=0; i<len; i++){
    tab[i] = rand()%100;
    printf(" %d |", tab[i]);
  }
  putchar('\n');
  T = tic();
  max = max_array(tab,len);
  t = tic();
  
  T=t-T;
  printf("Nombre de tic ecoule : %lu\n", T);
  printf("Numero max du tableau : %d\n", max);
  exit(0);
}
