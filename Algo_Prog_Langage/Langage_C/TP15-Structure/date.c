/*
Quesstion 1 : Date. 
Écrivez un programme qui affiche la date au format ISO 8601 (AAAA-MM-JJ). Infos sur la pgae manuelle.

bob@box:bob_apl12$ man 3 mktime

La fonction time vous donne cette date, mais exprimée en secondes écoulées depuis le 1er janvier 1970, ce qui n'est pas très pratique. 
La fonction localtime permet de décomposer la date en éléments exploitables.
*/

#include "stdlib.h"
#include "stdio.h"
#include "time.h"

int main(void){
	time_t secondes; // Définition d'une variable de type time_t, venant de la structure time.
	struct tm temps; // Redéfinition du nom de la strcuture.
	time(&secondes); // Fonction time prenant l'adresse d'un variable de type time_t.
    /* Passage de l'adresse du nombre de secondes à la fonction pointée localtime,
	pour décomposer sa valeur en tant que variable en éléments exploitable, en une date. */
    temps = *localtime(&secondes);
	/* tm_mon vas de 0 à 11 et tm_year part de 1900. */
	// Application de la strcture au type de la strcuture time.
	printf("%04d/%02d/%02d\n", temps.tm_year + 1900, temps.tm_mon + 1, temps.tm_mday);

	unsigned long long int sec = time(NULL); // Plus long entier pour les secondes depuis 1970.
	printf("%llu secondes depuis le 1er janvier 1970 \n", sec);
}
