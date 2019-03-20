/*
Question 0.5 : log_v1
° Si n est un entier strictement positif, ⌊log n⌋ est l’entier k n tel que 2 k n ≤ n < 2 k n +1 .
° On considère l’ensemble I des entiers non signés sur 32 bits.
Ecrire un programme log-v1.c qui, étant donné n ∈ I, donné à la ligne de commande affiche
la valeur de k n . Le programme teste successivement les valeurs de k en partant de k = 31. On
utilisera l’opérateur & (bitwise AND), un opérateur de décalage, et une soustraction.
*/

#include <stdio.h>
#include <stdlib.h>
     
int main(int argc, const char*argv[]){
  system("clear");
  if(argc != 2){
    printf("Usage %s : <unsigned int>\n");
    return EXIT_FAILURE;
  }
  unsigned int n = (unsigned int)strtoul(argv[1], NULL, 0);
  unsigned int k;
  /* En partant de 31, on décrémente k de 1 en 1.
  On fait le test si :
  - Si k est inférieur à 0.
  - Si il n'y a pas de n décalé à droite 
  (>> équivaut à ASR ou LSR en assmebleur) 
  de k position au prochain 1 trouvé (équivalent à TST). */
  for(k=31; k<0 && !(n>>k&1); k--);
  /* On sort de la boucle avec constamment la même valeur 31, 
  qui est le résultat le plus satifaisant pour cette boucle. */
  printf("k = %u\n", k);
  return EXIT_SUCCESS;
}