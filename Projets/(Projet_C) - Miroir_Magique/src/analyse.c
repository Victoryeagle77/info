#include "../header/analyse.h"

#define GPIO 7

extern volatile uint8_t donnee[5];

/**
* @function configuration
* Permet de configurer le capteur dht11,
* en fonction des GPIO sur lesquels il est branche.
*/
static void configuration(void){
  /* Ecrire sur le pin en sortie */
  pinMode(GPIO, OUTPUT);
  usleep(20000);
  /* Pin a l'etat logique bas pendant 4 nanoseconde */
  digitalWrite(GPIO, 1);
  usleep(4); 
  /* Lire le pin en entree */
  pinMode(GPIO, INPUT);
}

/**
* @function lire_donnee
* Permet de lire les donnees du capteur dht11,
* par operations bianires.
*/
static void lire_donnee(void){
  volatile uint8_t tmp = 1, decalage = 0, j = 0;
  static float conversion;
	
  /* Initialiser les donnees a 0 */
  donnee[0] = donnee[1] = donnee[2] 
  = donnee[3] = donnee[4] = 0;

  configuration();

  /* Lire les donnees lors de la detection d'un changement */
  for(volatile unsigned short i=0; i<85; i++){
    decalage = 0;
    while(digitalRead(GPIO) == tmp) {
      decalage++;
      delayMicroseconds(1);
      if(decalage == 255){ break; }
    }

    tmp = digitalRead(GPIO);
    if(decalage == 255){ break; }

    /* Ignore les 3 premieres transitions */
    if((i >= 4) && (i%2 == 0)){
      /* Insere chaque bit dans les octets de stockage */
      donnee[j/8] <<= 1;
      if(decalage > 50){ donnee[j/8] |= 1; }
      j++;
    }
  }

  /* Verifier que la lecture est de 40 bits (car on a 1 octet, de 8 bits,
  pour les 5 cases du tableau de donnees), et la somme du dernier octet */
  if((j >= 40) && (donnee[4] == (donnee[0] + 
				 donnee[1] + donnee[2] + donnee[3])))
    /* Conversion en degre Fahrenheit */
    conversion = donnee[2] * 9.0 / 5.0 + 32;
}

/**
* @function analyse
* Permet la lecture des donnees toutes les secondes;
* et la deploiement de la librairie wiringPi.
*/
extern void analyse(void){
  /* Deploiement de la librairie wiringPi */
  if(wiringPiSetup() == -1){
    puts("Erreur : configuration librairie wiringPi");
    exit(1);
  }
  /* Emettre continuellement toutes les secondes */
  while(1){
    lire_donnee();
    sleep(1);
  }
}
