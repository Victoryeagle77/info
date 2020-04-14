#include <netdb.h>
#include "helpers.h"

#define PROTOCOLE "HTTP/1.1"
#define VAILDATE "200 Ok\r\n"
#define SERVEUR "Serveur: le mien\r\n"
#define CONTENU "Content-Type : "
#define CR_LF "\r\n"
/* Erreurs */
#define EF "File Not Found"
#define E404 "404 Not Found\r\n"
#define E415 "415 Unknown Ressource Type\r\n"

static void etat(volatile unsigned short int socket, unsigned char *type){
    write(socket, VAILDATE, strlen(VAILDATE));
    write(socket, SERVEUR, strlen(SERVEUR));
    write(socket, CONTENU, strlen(CONTENU));
    write(socket, type, strlen(type));
    write(socket, CR_LF, strlen(CR_LF));
    write(socket, CR_LF, strlen(CR_LF));
}

/* Handle one http request. */
static void handle_request(volatile unsigned short int socket){
    static FILE *fd;
    static int methode;
    static char *chemin;
    parse_request(read_request(socket), &methode, &chemin);
    /* Protocole de transfert hypertexte */
    write(socket, PROTOCOLE, strlen(PROTOCOLE));

    if((methode == REQUEST_GET) && (chemin != NULL)){
        if((fd = fopen(chemin, "r")) <= 0) {
            write(socket, E404, strlen(E404));
            etat(socket, find_mimetype(chemin));
            write(socket, EF, strlen(EF));
            puts("Erreur : fichier vide");
            return;
        }

        etat(socket, find_mimetype(chemin));

        char buffer[ESPACE];
        static off_t offset = 0;
        
        while((offset = fread(buffer, sizeof(volatile unsigned char), 
            (size_t)ESPACE, fd)))
            write(socket, buffer, offset);
        fclose(fd);
    }else{
        /* 2 erreurs possibles */
        if(chemin == NULL)
            write(socket, E404, strlen(E404));
        else{ write(socket, E415, strlen(E415)); }
    }
    shutdown(socket, 2);
    close(socket);
}

static unsigned int configuration(const unsigned char *port){
    static struct addrinfo addr = {0}, *parametre, *i;
    static int tmp, fd = 0;
    static unsigned short int ipv6 = 0, valide = 1;

    addr.ai_family = AF_INET6;
    addr.ai_socktype = SOCK_STREAM;
    addr.ai_flags = AI_PASSIVE;

    if((tmp = getaddrinfo(NULL, port, &addr, &parametre)) != 0){
        fprintf(stderr, "Address info: %s\n", gai_strerror(tmp));
        exit(1);
    }

    for(i = parametre; i != NULL; i = i->ai_next){
        
        if((fd = socket(i->ai_family, i->ai_socktype, 
            i->ai_protocol)) == -1){
            puts("Serveur: Probleme de socket");
            continue;
        }
        /* Charge les options du socket recupere dans le file descriptor */
        if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &valide, 
               sizeof(volatile unsigned int)) == -1){
            puts("Serveur : Probleme de setsockopt");
            exit(1);
        }
        /* Define le format d'ipv6 avec le socket recupere dans le file descriptor */
        setsockopt(fd, IPPROTO_IPV6, IPV6_V6ONLY, &ipv6, 
            sizeof(volatile unsigned short int));
        
        if(bind(fd, i->ai_addr, i->ai_addrlen) == -1){
            close(fd);
            puts("Serveur: Probleme de bind");
            continue;
        }
        listen(fd, ESPACE);
        break;
    }
    /* Si le fichier est vide */
    if(i == NULL){ exit(2); }
    return fd;
}

extern void main(void){
    volatile unsigned int socket = configuration("5000");
    static int fd;

    system("clear");

    if(socket <= 0){
        puts("Erreur de connexion");
        exit(1);
    }

    while(1){ 
        fd = accept(socket, NULL, NULL);
        if((fd != -1) && (!fork())) {
            puts("Connection externe");
            handle_request(fd);
            close(socket);
            break;
        }
    }
    exit(0);
}