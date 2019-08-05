/* Question 2 : verif.c

Soit un vecteur a=(a1,a2,...,aN) t.q. pour chaque i
ai=-1 ou ai=0 ou ai=1. 

Appelons le vecteur 'a' p-pair ssi  
   Pos(a) est pair.

Etant donne un vecteur, verifier, est-il p-pair.
Si son nombre de cycle est pair. */

#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* Compte le nombre de tours effectué par le processeur 
(cycle appelé ici "tic") */
unsigned long nbtic() {
  unsigned long tic;
  __asm__(
    /* rdtsc permet de relever le nombre de tours du processuers */
    "rdtsc\n\t"
    "shlq $32,%%rdx\n\t"
    "movl %%eax,%%edx\n\t"
    "movq %%rdx,%%rax\n\t"
    /* droit de permission pour aller dans les fichiers */
    : "+r" (tic)
  );
  return tic;
}

int verif(long long int* vect, unsigned int len) {
  int i;
  for (i=0;i<len;i++) {
    if (vect[i]!=-1 && vect[i]!=0 && vect[i]!=1)
      return 0;
  }
  return 1;
}

int verif_asm(long long int* vect, unsigned int len) {
  int i,x=1;
  __asm__(
    /* rsi va servir en tant que i */
    "movq $0,%%rsi\n\t"
    /* boucle */
    "loop:\n\t"
    "cmpq $1,(%1)\n\t"
    /* si égalité, passe à suite */
    "je suite\n\t"
    "cmpq $0,(%1)\n\t"
    "je suite\n\t"
    "cmpq $-1,(%1)\n\t"
    "je suite\n\t"
    "movl $0,%0\n\t"
    "jmp fin\n\t"
    "suite:\n\t"
    /* i++ */
    "incq %%rsi\n\t"
    "addq $8,%1\n\t"
    "cmpl %%esi,%2\n\t"
    "jl loop\n\t"
    "fin:\n\t"
    /* droit de permission pour aller dans les fichiers */
    : "+r" (x)
    : "r" (vect), "r" (len)
  );
  return x;
}

/* Lecture des fichiers contenant les dimesnions des vecteurs */
void lire_vecteur(char* nom, long long int* vect, int len) {
  int fd,res,i;
  /* ouverture en lecture seule */
  fd=open(nom, O_RDONLY, 0440);
  if (fd==-1) { /* Erreur d'ouverture */
    printf("Erreur d'ouverture du fichier %s\n", nom);
    exit(1);
  }
  /* lecture des informations sur les vecteurs, 
  puis place dans ces informations dans la variables res */
  for (i=0;i<len;i++) {
    res=read(fd,&vect[i],8);
    if (res!=8) {
      printf("La longueur donnée est trop grande pour le fichier\n");
      exit(2);
    }
  }
  close(fd);
}

int main(int argc, char** argv) {
  long long int* vect;
  unsigned long t0, t1, asm_t0, asm_t1;
  unsigned len;
  int statut;

  if (argc!=3) {
    printf("usage : %s <fichier> <taille_vecteur>\n", argv[0]);
    return EXIT_FAILURE;
  }
  len=(unsigned)strtoul(argv[2],NULL,0);
  vect=(long long int*)malloc(len*sizeof(long long int));
  lire_vecteur(argv[1],vect,len);
  /* Test du nombre de cycle avec la fonction verif */
  t0=nbtic();
  statut=verif(vect,len);
  t1=nbtic();
  /* Test du nombre de cycle avec la fonction verif_asm */
  asm_t0=nbtic();
  statut=verif_asm(vect,len);
  asm_t1=nbtic();

  if (statut==0)
    printf("fichier %s dimension %u F tics sans asm %lu avec asm %lu\n", 
           argv[1], len, t1-t0, asm_t1 - asm_t0);
  else
    printf("fichier %s dimension %u T tics sans asm %lu avec asm %lu\n", 
           argv[1], len, t1-t0, asm_t1 - asm_t0);
  return EXIT_SUCCESS;
}