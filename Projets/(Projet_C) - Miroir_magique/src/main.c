#include "../header/analyse.h"
#include "../header/interface.h"
#include "../header/database.h"

/**
* @function main
* Permet l'execution synchronisee de tous les programmes.
*/
extern void main(void){
    static pthread_t th[3];
    pthread_create(&th[0], NULL, (void *)analyse, NULL);
    pthread_create(&th[1], NULL, (void *)interface, NULL);
    pthread_create(&th[2], NULL, (void *)database, NULL);

    for(volatile unsigned short int i=0; i<3; i++)
        pthread_join(th[i], NULL);

    pthread_exit(NULL);
    exit(0);
}
