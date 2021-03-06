#include "../header/analyse.h"

#define GPIO 7

static void configuration(void){
    /* Ecrire sur le pin en sortie */
    pinMode(GPIO, OUTPUT);

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

    /* Lire le pin en entree */
    pinMode(GPIO, INPUT);
}

static void lire_donnee(void){
    volatile uint_fast8_t tmp = 1, j = 0;
    /* Variable tampont recueprant les valeurs correctes */
    static uint8_t valeur[5] = {0};

    /* Protocole */
    configuration();

    /* 85 est la valeur maximale de l'humidite pouvant etre relevee.
    (Humidite : de 20% a 80% avec une precision de +- 5%). */
    for(volatile uint_fast8_t i = 0; i <= 85; i++){
        volatile uint_fast8_t plage = 0;
        /* Lecture de l'etat du signal logique du GPIO */
        while(digitalRead(GPIO) == tmp) {
            plage++;
            /* Transmission des donnees apres 1 mircoseconde */
            delayMicroseconds(1);
            /* En cas d'atteinte de la limite de 2^8 valeurs, 
            soit 255 valeurs, on sort de la plage de valeur. */
            if(plage == 255){ break; }
        }

        /* Lecture de l'etat du signal logique du GPIO */
        tmp = digitalRead(GPIO);

        /* En cas d'atteinte de la limite de 2^8 valeurs,
        soit 255 valeurs, on sort de la plage de valeur. */
        if(plage == 255){ break; }
        else if((i >= 4) && (i%2 == 0)){
            /* On stocke chaque bit dans un octet de recuperation,
            (de 8 bit) par decalage bit a bit par 1 vers la gauche. */
            donnee[j/8] <<= 1;
            /* 52 est la valeur maximale que peut relever la sonde en temperature,
            (Temperature : de 0°C a 50°C avec +- 2°C de precision). 
            On effectue un "ou" bit a bit en cas de depassement. */
            if(plage > 52){ donnee[j/8] |= 1; }
            j++;
        }
    }

    /* Verifier que la somme du dernier octet et que la lecture est de 40 bits.
    (car on a 8 bits (1 octet) * 5 cases du tableau de donnees = 40),
    On s'assure ainsi que cela respecte les bornes de mesure de la sonde. */
    if((j >= 40) && (donnee[4] == (donnee[0] + donnee[1] + 
                                   donnee[2] + donnee[3]))){
        for(volatile uint_fast8_t i=0; i<5; i++)
            valeur[i] = donnee[i];
    }else{
        /* Si la valeur est incorrecte, on prend la precedente. */
        for(volatile uint_fast8_t i=0; i<5; i++)
            donnee[i] = valeur[i];
    }
}

extern void analyse(void){
    static pthread_mutex_t mutex;
    /* Deploiement de la librairie wiringPi */
    if(wiringPiSetup() == -1){ exit(1); }
    /* Emettre continuellement toutes les secondes */
    while(1){
        /* Securisation de l'execution multitache */
        pthread_mutex_lock(&mutex);
        /* Lecture et stockage des donnees toutes les secondes */
		lire_donnee();
        sleep(1);
        /* Securisation de l'execution multitache */
        pthread_mutex_unlock(&mutex);
	}
}
