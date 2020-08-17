#include <stdarg.h>
#include "helpers.h"

/****
* @function *readline
* Retounre une ligne de la requête du client
****/
extern char *readline(volatile int fd){
	char *ligne = malloc(ESPACE+1);
	static unsigned char c;
	static unsigned short int i = 0;

	while(i < ESPACE && (read(fd, &c, 1) == 1) && (c != '\n'))
		ligne[i++] = c;

	ligne[i] = 0;
	
	if((i > 0) && (ligne[i-1] == '\r'))
		ligne[i-1] = 0;

	if(strlen(ligne)== 0){
		free(ligne);
		/* La ligne etait vide */
		return NULL;
	}
	return ligne;
}

/****
* @function purge_request
* Lit le file descriptor jusqu'a ce qu'on est \r\n consecutifs.
*
* PROPRIETES :
* +--------------------------+
* | state | \r | \n  | other |
* +-------+----+-----+-------+
* |   0   |  0 |  1  |   0   |
* |   1   |  2 |  0  |   0   |
* |   2   |  0 |  $  |   0   |
* +--------------------------+
****/
static void purge_request(volatile int fd){
	static unsigned short int etat = 0;
	static unsigned char c;
	while(read(fd, &c, 1) == 1) {
		if((etat == 0) && (c == '\n'))
			etat = 1;
		else if((etat == 1) && (c == '\r'))
			etat = 2;
		else if((etat == 2) && (c == '\n'))
			break;
		else{ etat = 0; }
	}
}

/****
* @function *read_request
* Lit une requete http complete du file descriptor
* Et retourne la premiere ligne. 
****/
extern char *read_request(volatile int fd){
	char *ligne = readline(fd);
    purge_request(fd);
	return ligne;
}

/**** 
* @function parse_request
* Decoupe la requete envoye
* et retourne la methode et l'url. 
****/
extern void parse_request(char *ligne, int *methode, char **chemin){
	if(strncmp(ligne, "GET ", 4) == 0){
		*methode = REQUEST_GET;
		/* On ignore "GET /" */
		*chemin = ligne + 5;
		volatile unsigned char *p = strchr(*chemin, ' ');
		if(p != NULL){ *p = '\0'; }
		printf("Request: GET %s\n", *chemin);
	}else{
		*methode = REQUEST_UNKNOWN;
		*chemin = NULL;
		puts("Request: UNKNOWN");
	}
}

/****
* @function strend
* Retourne true si s1 se termine avec s2. 
****/
static int strend(unsigned char *s1, unsigned char *s2){
	volatile unsigned int l1 = strlen(s1);
	volatile unsigned int l2 = strlen(s2);
	return ((l1 >= l2) && (strcmp(s1 + l1 - l2, s2) == 0));
}

extern char *find_mimetype(char *chemin){
	if(strend(chemin, ".html"))
		return "text/html; charset=utf-8";
	else if(strend(chemin, ".jpg") || strend(chemin, ".jpeg"))
		return "image/jpeg";
	else if(strend(chemin, ".png"))
		return "image/png";
	else{ return "text/plain; charset=utf-8"; }
}