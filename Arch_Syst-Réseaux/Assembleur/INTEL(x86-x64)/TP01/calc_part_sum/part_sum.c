/* Question 2 : part_sum
Créer un programme C qui prend deux entiers non-signés sur sa ligne de commande,
Et qui calcule la somme d'impaires et de sont ppcm, en effectuant un décalage bit à bit à droite,
sur le premier impair par 1, puis ensuite un décalage à gauche par 1 sur celui-ci, 
et enfin additioner par 1. 
*/
#include<stdio.h>
#include<stdlib.h>

int Simpair(unsigned int a, unsigned int b){
  unsigned int tmp,res;
  res=0;
  tmp=((a>>1)<<1)+1;
  while(tmp<=b){
    res+=tmp;
    tmp+=2;
  }
  return res;
}

int main(int argc,char ** argv){
  int a,b,S;
  if(argc!=3){
    printf("Usage : %s <int> <int>\n",argv[0]);
    return -1;
  }
  a=(unsigned int) strtoul(argv[1],NULL,0);
  b=(unsigned int) strtoul(argv[2],NULL,0);
  if(a>b){
    printf("%d > %d, somme des impairs = 0\n",a,b);
    return 1;
  }
  S = Simpair(a,b);
  printf("Somme des impairs %d et %d = %d\n",a,b,S);
  return 0; 
}
