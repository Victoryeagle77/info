/***** Arthur Chenu *****/

#ifndef JEU_H
#define JEU_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "graph.h"

/* Définition d'un nouveau type de définition. 
Permet de cliquer directement de vérifier les coordonnées de la souris sur l'écran 
par rapport à la zone. */
typedef unsigned short int zone[8];

/* Fonction permettant de définir une zone cliquable à la souris */
unsigned short int interaction(short int, short int, 
                               unsigned short int[]); 
void jeu(unsigned short int);

#endif