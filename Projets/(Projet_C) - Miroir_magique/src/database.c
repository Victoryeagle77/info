#include "../header/database.h"
#include "../header/interface.h"

volatile struct data{
    volatile int fd;
    volatile uint_fast8_t val;
    volatile pthread_mutex_t mutex;
} *d;

static void *ecriture(void *flux){
    static uint_fast8_t str[32] = {0x0};
    pthread_mutex_t securisation = ((struct data*)flux)->mutex;
    /* Tableau de donnee de temperature et humidite */
    extern volatile uint8_t donnee[5];

    /* Ecrire une premiere fois la date */
    write(d->fd, strcat(date(), "\n"), 22);

    for(volatile uint_fast8_t i = 0; !(d->val); i++){
        /* Securisation de l'execution multitache */
        pthread_mutex_lock(&securisation);
        /*  Verouillage consultatif exclusif */
        flock(d->fd, LOCK_EX);
        /* Ecrire toutes les 5 seconcdes */
        sleep(5);
        lseek(d->fd, 0, SEEK_END);

        if(i > 6){
            write(d->fd, strcat(date(), "\n"), 22);
            i = 0;
        }else{
            sprintf(str,"%d %d\n", donnee[0], donnee[2]);
            write(d->fd, str, sizeof(str));
        }

        /* Deverrouillage du verrou tenu par le processus */
        flock(d->fd, LOCK_UN);
        /* Deverrouillage de la securisation */
        pthread_mutex_unlock(&securisation);
    }

    close(d->fd);
}

static void* lecture(void *flux){
    static uint_fast8_t buffer[32] = {0};
    static volatile off_t offset, tmp = 0;
    pthread_mutex_t securisation = ((struct data*)flux)->mutex;

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
            //printf("%s", buffer);
        }
    }
}

extern void database(void){
    static pthread_t th[2];

    d = (struct data *)malloc(sizeof(struct data));
    d->fd = open(FLUX, O_RDWR | O_CREAT | O_TRUNC);

    pthread_create(&th[1], NULL, (void *)ecriture, (void*)d);
    pthread_create(&th[0], NULL, (void *)lecture, (void*)d);

    for(volatile unsigned short int i=0; i<2; i++)
        pthread_join(th[i], NULL);

    pthread_exit(NULL);
    free((void *)d);
}

