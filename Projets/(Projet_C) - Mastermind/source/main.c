#include "jeu.h"

int main(void){
  system("clear");
  InitialiserGraphique();
  CreerFenetre(20,20,1000,600);
  ChargerImageFond("./images/fond.png");
  jeu();
  return 0;
}