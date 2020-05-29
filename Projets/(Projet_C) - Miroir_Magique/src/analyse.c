#include "../header/analyse.h"

extern volatile uint8_t donnee[5];

extern volatile unsigned char *date(char *chaine){
    time_t temps = time(NULL);
    volatile struct tm tm = *localtime(&temps);
    sprintf(chaine, "%s%02d/%02d/%d - %02d:%02d",
            "", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, 
            tm.tm_hour, tm.tm_min);
    return chaine;
}

/**
* @function etalonnage
* Permet d'effectuer une transitions sur les niveaux logiques,
* pour définir le protocole (le temps d'attente entre l'ecriture et la lecture de donnees)
*/
static void etalonnage(void){
  /* On effectue un front montant pour configurer les signaux logiques.
      |-----|
      |  1  | (Etat haut du signal logique)
      A     V
      |  0  | (Etat bas du signal logique)
  ----|     |-----
  */
  digitalWrite(GPIO, 0);
  usleep(20000);
  digitalWrite(GPIO, 1);
  usleep(4);
}

/**
* @function configuration
* Permet de configurer le capteur dht11,
* en fonction des GPIO sur lesquels il est branche.
*/
static void configuration(void){
	/* Ecrire sur le pin en sortie */
	pinMode(GPIO, OUTPUT);
	etalonnage();
	/* Lire le pin en entree */
	pinMode(GPIO, INPUT);
}

/**
* @function lire_donnee
* Permet de lire les donnees du capteur dht11,
* par operations bianires.
*/
static void lire_donnee(void){
	volatile uint_fast8_t tmp = 1, decalage = 0, j = 0;

	configuration();

	/* Lire les donnees lors de la detection d'un changement */
	for(volatile unsigned short i=0; i<85; i++){
		decalage = 0;
		while(digitalRead(GPIO) == tmp) {
			decalage++;
			delayMicroseconds(1);
			if(decalage == 255){ break; }
		}
		
		/* Lecture de l'etat du signal logique du GPIO */
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
	
	/* Variable tampont recueprant les valeurs correctes */
	static volatile uint8_t valeur[5] = {0};
	/* Verifier que la lecture est de 40 bits (car on a 1 octet, de 8 bits,
	pour les 5 cases du tableau de donnees), et la somme du dernier octet. */
	if((j >= 40) && (donnee[4] == (donnee[0] + 
			donnee[1] + donnee[2] + donnee[3]))){
		for(volatile unsigned short i=0; i<5; i++)
			valeur[i] = donnee[i];
	}else{
		/* Si la valeur est incorrecte, on prend la precedente. */
		for(volatile unsigned short i=0; i<5; i++)
			donnee[i] = valeur[i];
	}
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
