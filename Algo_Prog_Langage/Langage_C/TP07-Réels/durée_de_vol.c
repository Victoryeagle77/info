#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Vitesse minimale et maximale de vol d'un avion de ligne
#define MAX_AVION 1000
#define MIN_AVION 300
#define MIN_DISTANCE 50
#define MAX_VENT 150

int main(void){
    double v_avion, v_vent, d, t;
    int min;
    printf("\n----- Parametre du trajet aerien -----\n\n");
    
    do{
       printf("* Vitesse de vol de l'avion (km/h) [comprise entre 300 km/h et 1000 km/h]: ");
       scanf("%lf", &v_avion);
    }while(v_avion < MIN_AVION || v_avion > MAX_AVION);

    printf("\n* Vitesse du vent (km/h)\n");
    printf("-> [Positive pour vent contraire et negative pour vent arriere] : ");
    scanf("%lf", &v_vent);
    
    if(v_vent > MAX_VENT || v_vent < -MAX_VENT){
       printf("\n! Attention : Etes-vous certain de cette information !\n");
       printf("! Un avion ne peut voler par plus de 150 ou -150 km/h !\n");
       printf("Saisissez de nouveau le vitesse du vent pour confirmer ou corriger : ");
       scanf("%lf", &v_vent);
    }

    if(v_vent > MAX_VENT || v_vent < -MAX_VENT){
        printf("\n/!\\ Condition climatiques trop violentes !\n");
	    printf("Annulation d'autorisation de vol en cours ...\n");
        return 1;
    }
    
    do{
       printf("\n* Distance a parcourir (km) [supérieur à 50 km]: ");
       scanf("%lf", &d);
    }while(d < MIN_DISTANCE);
    
    /* 
    -> temps = distance/vitesse
    -> Vitesse : * vitesse - vent contraire 
                 * vitesse - (- vent arriere) soit vitesse + vent arriere
    */
     
    t = d / (v_avion-v_vent);
    min = trunc((int)(t*100)%100);
    if(min > 60){
	min = min - 60; 
	t += 1.0;
    }

    printf("Duree de vol : %.lf heure(s) et %d minute(s)\n", t, min);
    return 0;
}
