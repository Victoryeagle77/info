#include "../header/database.h"
#include "../header/interface.h"

volatile struct data{
    volatile int fd;
    volatile Bool val;
    volatile pthread_mutex_t mutex;
} *d;

static const uint8_t *substr(volatile uint_fast8_t *chaine, const uint_fast8_t debut, 
                                const uint_fast8_t fin){
    /* Longueur de la chaine finale */
    volatile uint_fast8_t longueur = fin - debut;
    /* Allocation de la taille de la chaine finale a la longueur + 1 */
    uint8_t *msg = (uint8_t *)malloc(sizeof(uint8_t) * (longueur + 1));
    /* On extrait et copie le(s) caractere(s) entre les cases de debut et de fin */
    for(volatile uint_fast8_t i = debut; i<fin && (*(chaine + i)!='\0'); i++){
        *msg = *(chaine + i);
        msg++;
    }
    *msg = '\0'; /* Chaine terminee */
    return msg - longueur; /* Chaine extraite */
}

static void filtrage(volatile uint8_t *buffer){
    /* Si la chaine est du format "00 00 00\n" */
    if((!(strcmp(substr(buffer, 2, 3), " "))) && (!(strcmp(substr(buffer, 5, 6), " ")))
        && (!(strcmp(substr(buffer, 8, 9), "\n")))){

        /* Variable tampon verifiant la validite des donnees numeriques */
        static volatile uint8_t tmp[3] = {0};

        for(volatile uint_fast8_t i=0, j=0; ((i<3) && (j<9)); i++, j+=3){
            tmp[i] = (const uint8_t)strtol(substr(buffer, j, j+2), NULL, 10);
            if(((tmp[0]>=20) && (tmp[0]<=80)) && ((tmp[1]>=0) && (tmp[1]<=50)) 
                                              && ((tmp[2]>=0) && (tmp[2]<=60)))
                db[i] = tmp[i];
        }
    }
}

static void *ecriture(void *flux){
    extern volatile uint8_t donnee[5];
    static uint8_t str[32] = {0x0};
    pthread_mutex_t securisation = ((struct data*)flux)->mutex;

    /* Ecrire une premiere fois la date */
    write(d->fd, strcat(date(), "\n"), 22);

    for(volatile uint_fast8_t sec=0; !(d->val); sec++){
        /* Securisation de l'execution multitache */
        pthread_mutex_lock(&securisation);
        /*  Verouillage consultatif exclusif */
        flock(d->fd, LOCK_EX);
        /* Ecrire toutes les 5 seconcdes */
        sleep(5);
        lseek(d->fd, 0, SEEK_END);

        /* Ecrire pendant 1 minute (12*5s = 60s) */
        if(sec <= 12){
            sprintf(str,"%.2d %.2d %.2d\n", donnee[0], donnee[2], sec*5);
            write(d->fd, str, sizeof(str));
        }else{ 
            d->fd = 1;
            close(d->fd);
        }

        /* Deverrouillage du verrou tenu par le processus */
        flock(d->fd, LOCK_UN);
        /* Deverrouillage de la securisation */
        pthread_mutex_unlock(&securisation);
    }

}

static void* lecture(void *flux){
    static char buffer[32] = {0};
    static volatile off_t offset, tmp = 0;
    pthread_mutex_t securisation = ((struct data*)flux)->mutex;
    
    offset = lseek(d->fd, SEEK_SET, 0);
    
    while(!(d->val)){
        /* Securisation de l'execution multitache */
        pthread_mutex_lock(&securisation);
        /* Verouillage consultatif exclusif */
        flock(d->fd, LOCK_EX);

        lseek(d->fd, offset, SEEK_SET);
        tmp = read(d->fd, buffer, 32);

        /* Deverrouillage du verrou tenu par le processus */
        flock(d->fd, LOCK_UN);
        /* Deverrouillage de la securisation */
        pthread_mutex_unlock(&securisation);

        if((tmp > 0) && (d->fd != -1)){
            offset = lseek(d->fd, offset+tmp, SEEK_SET);
            buffer[tmp] = 0;
            filtrage(buffer);
        }
    }
}

extern void database(void){
    static pthread_t th[2];

    d = (struct data *)malloc(sizeof(struct data));
    d->fd = open(FLUX, O_RDWR | O_CREAT);

    pthread_create(&th[1], NULL, (void *)ecriture, (void*)d);
    pthread_create(&th[0], NULL, (void *)lecture, (void*)d);

    for(volatile unsigned short int i=0; i<2; i++)
        pthread_join(th[i], NULL);

    free((void *)d);
    pthread_exit(NULL);
}

