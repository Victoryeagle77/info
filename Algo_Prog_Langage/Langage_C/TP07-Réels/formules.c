#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (void){
        /* 
	sqrt() ne peut pas prendre de valeur non signé, cela donne un résultat indéfini et log(0.5) est négatif.
	Mais ici nous utilisons la valeur absolue fabs() pour que log(0.5) soit poisitif. 
	*/
	printf("-> sqrt(|log(0.5)|) = %f\n", sqrt(fabs(log(0.5))));
	
	printf("-> sin pi/6 = %f\n", sin(M_PI/6));
	
	printf("-> archtan((13)^2) = %f\n", atan(pow(13, 2)));
	
	printf("-> (e^(-1))^4 = %f\n", pow(exp(-1),4));
	// ln ne peut pas prendre de valeur non signé -> résultat indéfini	
	printf("-> ln(-3) = %f\n", log(-3));

	printf("-> sqrt(2)^2 = %.f\n", pow(sqrt(2),2));
}
