#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

typedef int Bouton[8];

#ifndef OBJETS_H
#define OBJETS_H

int interaction(int, int, int[]);
void verification(int[], int[], int[]);
void couleur_bouton(int[]);
void case_bouton(int[]);
void coloration(int[], int[]);
void rafraichir(int[], int[], int[], int[]);
void indice(int[], int[]);

#endif