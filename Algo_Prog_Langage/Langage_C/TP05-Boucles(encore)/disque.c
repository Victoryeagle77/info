/*
Question 4  : Disque. 
Écrivez un programme qui demande le rayon, puis affiche un disque formé d'étoiles.

Rayon ? 10
                                          
            * * * * * * * * *             
          * * * * * * * * * * *           
      * * * * * * * * * * * * * * *       
      * * * * * * * * * * * * * * *       
    * * * * * * * * * * * * * * * * *     
  * * * * * * * * * * * * * * * * * * *   
  * * * * * * * * * * * * * * * * * * *   
* * * * * * * * * * * * * * * * * * * * *  
* * * * * * * * * * * * * * * * * * * * *  
* * * * * * * * * * * * * * * * * * * * *  
* * * * * * * * * * * * * * * * * * * * *  
* * * * * * * * * * * * * * * * * * * * *  
  * * * * * * * * * * * * * * * * * * *   
  * * * * * * * * * * * * * * * * * * *   
    * * * * * * * * * * * * * * * * *     
      * * * * * * * * * * * * * * *       
      * * * * * * * * * * * * * * *       
          * * * * * * * * * * *           
            * * * * * * * * *             
                                          

Remarque : On se souviendra que les points d'un disque sont les points dont la distance au centre est inférieure au rayon. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void){
    int rayon, ligne, colonne;
    do{
       printf("Rayon (strictement supérieur à 0) : ");
       scanf("%d",&rayon);
    }while(rayon <= 0);
     /* On part de la valeur négative de rayon.
     Puis on conditionne les boucles avec la valeur rayon + 1.
     Car sur le disque que nous devons représenter, le diamètre du cercle ne vaut pas tout à fait 2 fois le rayon.
     Il y a en effet en plus une étoile au centre, qu'il faut donc définir comme repère.
     [Par exemple -> pour un rayon de 2, on aura un diamètre de 4 + le centre (soit 5 caractères '*' pour chaque distances)]
     */
     for (colonne = -rayon; colonne < rayon+1; colonne++){    
        putchar('\n');     
        for (ligne = -rayon; ligne < rayon+1 ; ligne++) {   
            /* En mettant l'instruction suivante : ligne² + colonne² - rayon²      
            --> On fait en sorte que les points du disques aient une distance du centre inférieur au rayon
	    */
	    if(((pow(ligne,2)) + (pow(colonne,2)) - (pow(rayon,2))) <= (rayon/2))                   
                printf(" *"); 
                // Espace pour répéter la figure à droite (sinon forme un demi-cercle à gauche)                                        
            else                                           
                printf("  ");                                
        }                
    }
    putchar('\n');  
    return 0;
}
