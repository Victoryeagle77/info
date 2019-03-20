/*
Question 6 : Truandage. 
Qu'affiche le programme suivant ?

int main(void) {
  long long int n = 32217268732456802LL;
  printf("%s\n", &n);
  return EXIT_SUCCESS;
}

Comment faire pour calculer la valeur qu'il faudrait donner à n pour qu'il affiche bonsoir ? 
Commencez par afficher n en hexadécimal. Voyez-vous les lettres ?
*/

#include <stdio.h>
#include <stdlib.h>

int main(void){
  long long int n = 32217268732456802LL;
  printf("* Chaine debut : %s\n", &n); // Ce programme affiche "bonjour".
  /*
  - En faisant printf("%x", n), on remarque que ce mot correspond en hexadécimal à 6a 6e 6f 62, 
  soit "jnob", converti en ascii.
  - On en déduit qu'il faudrait y rajouter le suffixe "rios", soit 72 69 6f 73 en hexadécimal, et enlever
  la lettre 'j' soit, en tenant compte de l'odre inversé par la transcription en adresse, 6a.
  - On fusionne donc, dans l'ordre, le suffixe "rios" avec le préfixe "nob", soit 72 69 6f 73 avec 6e 6f 62.
  - Une fois l'odre inversé par la transcription en adresse, on obtient bonsoir.
  */ 
  n = 0x72696f736e6f62;
  printf("* Chaine fin : %s\n", &n);
  return EXIT_SUCCESS;
}
