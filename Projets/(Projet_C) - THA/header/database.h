#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <pthread.h>

#define FLUX "./database/log.txt"

/**** TYPES DE DEFINITION ET STRUCTURES DE DONNEES ****/

volatile uint8_t db[3];

volatile struct data{
    volatile int fd;
    volatile uint_fast8_t val;
    volatile pthread_mutex_t mutex;
} *d;

/**** FONCTIONS ****/

extern void database(void);

#endif
