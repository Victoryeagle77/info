#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <pthread.h>

#define FLUX "./database/log"

volatile uint8_t db[3];

extern void database(void);

#endif
