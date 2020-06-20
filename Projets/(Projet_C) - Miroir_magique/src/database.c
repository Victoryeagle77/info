#include "../header/database.h"

int fd;
volatile uint_fast8_t continuation = 0;
extern volatile uint8_t donnee[5];

static void *ecriture(void *flux){

    for(volatile uint_fast8_t i=0; i<5; i++){
        /*  Verouillage consultatif exclusif */
        flock(fd, LOCK_EX);
        /* Ecrire toutes les 10 seconcdes */
        sleep(1);
        lseek(fd, 0, SEEK_END);
        write(fd,  donnee[i], sizeof(donnee[i]));
        /* Deverrouillage du verrou tenu par le processus */
        flock(fd, LOCK_UN);
    }

    continuation = 1;
    close(fd);
}

static void* lecture(void *flux){
    static unsigned char buffer[32] = {0};
    static volatile off_t offset, octet = 0;

    while(!(continuation)){
        /* Verouillage consultatif exclusif */
        flock(fd, LOCK_EX);

        lseek(fd, offset, SEEK_SET);
        octet = read(fd, buffer, 32);

        /* Deverrouillage du verrou tenu par le processus */
        flock(fd, LOCK_UN);

        if(octet > 0){
            offset = lseek(fd, offset+octet, SEEK_SET);
            buffer[octet] = 0;
            puts(buffer);
        }
    }

    lseek(fd, offset, SEEK_SET);
    octet = read(fd, buffer, 32);

    if(octet > 0){
        buffer[octet] = 0;
        puts(buffer);
    }

    offset = lseek(fd, SEEK_SET, 0);
}

extern void main(void){
    static pthread_t th[2];
    fd = open(FLUX, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG);

    pthread_create(&th[1], NULL, (void *)ecriture, (void*)&fd);
    pthread_create(&th[0], NULL, (void *)lecture, (void*)&fd);

    for(volatile unsigned short int i=0; i<2; i++)
        pthread_join(th[i], NULL);
    
    pthread_exit(NULL);
}

