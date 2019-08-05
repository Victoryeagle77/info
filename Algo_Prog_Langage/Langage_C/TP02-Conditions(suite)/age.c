/*
Question 2.5 : Age
Faire un programme dans le quelle on entre une date de naissance puis la date actuelle et affiche l'age correspondant
On supposera que toutes les saisies sont vraies.
*/

#include <stdio.h>
#include <stdlib.h>

int main(void){
  int j, m, a; /* jour, mois, année de naissance. */
  int j_c, m_c, a_c; /* jour, mois, année actuels. */

  printf("-> Date au format JJ/MM/AAAA <-\n\n");

  printf("Entrez votre date de naissance : ");
  scanf("%d %d %d", &j, &m, &a);
  printf("Date de naissance : %.2d / %.2d / %.4d\n", j, m, a);

  printf("\nEntrez la date actuelle : ");
  scanf("%d %d %d", &j_c, &m_c, &a_c);
  printf("Date actuelle : %.2d / %.2d / %.4d\n", j_c, m_c, a_c);
  /* On utilise la varaible m en tant que variable tampon récupérant une nouvelle valeur,
  qui sera un calcul avec elle-même. */
  m = m_c - m;
  /* Pareil pour a qui sera l'age final. */
  a = a_c - a;
  /* La soustraction entre les 2 années dépend de celle entre les 2 mois, 
  et elle même dépend de celle entre les 2 jours. */
  if(j_c - j < 0){ /* Si la différence entre le jour actuel et le jour de naissance est inférieur à 0. */
    m--; /* Alors le mois sera décrémenté de -1 mois, soit : m = m - 1 */
    if(m < 0) /* Si la différence entre le mois actuel et le mois de naissance est inférieur à 0. */
      a--; /* Alors l'age de l'individu sera décrémenté de -1 an. */
  }
  printf("\nVous avez %d ans.\n", a);
  return EXIT_SUCCESS;
}