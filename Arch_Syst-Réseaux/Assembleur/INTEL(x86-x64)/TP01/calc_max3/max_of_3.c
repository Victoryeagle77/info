/* Question 1 : max_of_3.c 
Faite un programme C qui prend 3 entiers sur sa ligne de commande,
et montre le plus grand des 3. */

#include <stdio.h>
#include <stdlib.h>

int max(int a,int b,int c) {
  int tmp=a;
  if(tmp<b){ tmp=b; }
  if(tmp<c){ tmp=c; }
  return tmp;
}

int main(int argc, char ** argv) {
  if(argc!=4) {
    printf("Usage : %s <int> <int> <int>\n", argv[0]);
    return -1;
  }
  int a,b,c,res;
  a=(int) strtol(argv[1],NULL,0);
  b=(int) strtol(argv[2],NULL,0);
  c=(int) strtol(argv[3],NULL,0);
  res=max(a,b,c);
  printf("Le maximum est : %d\n",res);
  return 0;
}
