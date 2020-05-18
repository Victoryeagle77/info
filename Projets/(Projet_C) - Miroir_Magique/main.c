#include <pthread.h>
#include "../header/analyse.h"
#include "../header/interface.h"

extern void main(void){
    static pthread_t th[2];
    pthread_create(&th[0], NULL, (void *)analyse, NULL);
    pthread_create(&th[1], NULL, (void *)affichage, NULL);
    
    for(volatile unsigned short int i=0; i<2; i++)
        pthread_join(th[i], NULL);
    
    pthread_exit(NULL);
    exit(0);
}
