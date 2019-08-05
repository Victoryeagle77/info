/*
Question 1 : Monnaie. 
- Ce même magasin vend 5,49€ un produit très demandé, mais il n'accepte ni chèque, ni carte de paiement. 
Ses caisses n'ont que des pièces de 2€, 20 centimes et 1 centime.
- Écrivez un programme qui demande à l'utilisateur combien le client a payé, 
puis affiche comment rendre la monnaie avec le moins de pièces possible.
*/


#include <stdio.h>
#include <stdlib.h>

#define PRODUIT 5.49

int main(int argc, char** argv) {
  double achat, monnaie, remboursement;
  int deux_euro=0, vingt_centimes=0, un_centime=0;
  int i=0, j=0, k=0;
  if (argc != 2) {
    printf("%s <double>\n", argv[0]);
    return 1; /* Sortie avec échec */
  }
  achat = strtod(argv[1],NULL);
  printf("Valeur du produit : %.2f\nPrix du produit : %.2f\n", achat, PRODUIT);
  monnaie = achat - PRODUIT;
  printf("Monnaie a rendre : %.2f\n", monnaie);
	
  for (; monnaie >= 2.0; i++) {
    monnaie -= 2.0; /* Signifie monnaie = monnaie - 2.0 */
    deux_euro ++;
  }
  for (; monnaie >= 0.20; j++) {
    monnaie -= 0.20;
    vingt_centimes ++;
  }
  for (; monnaie >= 0.0; k++) {
    monnaie -= 0.01;
    un_centime ++;
  }
  printf("Monnaie rendu : %d pieces de 2e + %d pieces de 20c + %d pieces de 1c.\n", 
         deux_euro, vingt_centimes, un_centime);
  return EXIT_SUCCESS;
}