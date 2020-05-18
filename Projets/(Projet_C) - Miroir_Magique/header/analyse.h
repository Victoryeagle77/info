#ifndef ANALYSE_H
#define ANALYSE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>
/* Librairie de communication serie sur Raspberry */
#include <wiringPi.h>

volatile uint8_t donnee[5];

extern void analyse(void);

#endif
