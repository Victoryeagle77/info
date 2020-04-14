#ifndef _HELPERS_H
#define _HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define REQUEST_GET 1
#define REQUEST_UNKNOWN 10
#define ESPACE 1024

char *readline(int fd);
char *read_request(int fd);
void parse_request(char *line, int *method, char **filename);
char *find_mimetype(char *filename);

#endif
