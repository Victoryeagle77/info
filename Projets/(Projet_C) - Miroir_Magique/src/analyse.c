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
	/* Pin a l'etat logique bas pendant 20 milliseconds */
	digitalWrite(GPIO, 0);
	usleep(18000);
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
	for(volatile unsigned short i=0; i< 85; i++){
		decalage = 0;
		while(digitalRead(GPIO) == tmp) {
			decalage++;
			delayMicroseconds(1);
			if(decalage == 255){ break; }
		}
		tmp = digitalRead(GPIO);
		if(decalage == 255){ break; }
		
		/* ignore first 3 transitions */
		if((i >= 4) && (i%2 == 0)){
			/* shove each bit into the storage bytes */
			donnee[j/8] <<= 1;
			if(decalage > 50){ donnee[j/8] |= 1; }
			j++;
		}
	}

	/* check we read 40 bits (8bit x 5 ) + 
	verify checksum in the last byte
	print it out if data is good */
	if((j >= 40) && (donnee[4] == (donnee[0] + 
			donnee[1] + donnee[2] + donnee[3]))){
		/* Conversion en degre Fahrenheit */
		conversion = donnee[2] * 9.0 / 5.0 + 32;
		printf("Humidity = %d.%d%%\nTemperature = %d.%d°C ou %.1f°F\n", 
			donnee[0], donnee[1], donnee[2], 
			donnee[3], donnee[4], conversion);
	}
}

extern void analyse(void){
	/* Deploiement de la librairie wiringPi */
	if(wiringPiSetup() == -1){
		puts("Erreur : configuration librairie wiringPi");
		exit(1);
	}
	/* Emettre continuellement toutes les 1s */
	while(1){
		lire_donnee();
		sleep(1);
	}
}