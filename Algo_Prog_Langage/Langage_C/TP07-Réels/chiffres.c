/* Question 6 : Chiffres 
Écrivez un programme qui demande à l'utilisateur un réel, 
puis affiche le chiffre des unités et le chiffre des dixièmes uniquement.

$ ./a.out
Entrez un réel : 141.35
chiffre des unités :   1
chiffre des dixièmes : 3

! Remarque ! Pensez à la fonction trunc ! 
*/

#include <stdio.h>
#include <math.h>

int main(void){
  float n;
  printf("Entrez un reel : ");
  scanf("%f", &n);
  /* Le modulo ne s'applique pas avec un nombre entier sur un nombre décimale. */
  printf("chiffre des unites : %.f\n", trunc((int)n%10)); 
  /* On caste donc en entier, dans la troncature du nombre saisit, l'opération n % 10. */
  printf("chiffre des dixiemes : %.f\n", trunc((int)(n*10)%10));
  return 0;
}