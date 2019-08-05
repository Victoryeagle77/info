/*
Question 2 : Opération. 
Écrivez un programme qui calcule 73×16, 73/16, 73+16 et affiche le résultat, 
mais sans utiliser d'opérateur arithmétique (avec les opérateur bit à bit). 
*/

#include <stdio.h>

int main(void) {
  printf("-> Opération bit à bit <-\n");
  
  /* [ Décalage à gauche << ]
  Décale les bits vers la gauche (multiplie par 2 à chaque décalage).
  Les zéros qui sortent à gauche sont perdus, tandis que des zéros sont insérés à droite.
  Donc on doit faire 73 << 4 pour avoir par caclul 73 * (4*4).
  */
  printf("73 x 16 (avec <<) = %d\n", 73 << 4);
  
  /* [ Décalage à droite avec conservation du signe >> ]
  Décale les bits vers la droite (divise par 2 à chaque décalage). 
  Les zéros qui sortent à droite sont perdus, tandis que le bit non nul de poids plus fort est recopié à gauche.
  */
  printf("73 / 16 (avec >>) = %d\n", 73 >> 4);
  
  /* [ Le ou bit à bit | et le ou exclusif ^ ]
  Effectue une addition si l'opérateur n'a pas à effectuer un nombre par lui même.
  */ 
  printf("73 + 16 (avec |) = %d et 73 + 16 (avec ^) = %d\n", 73|16, 73^16);
  return 0;
}
