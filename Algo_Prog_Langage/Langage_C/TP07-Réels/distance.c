#include <stdio.h>
#include <math.h>

int main(void){
  
  double x1, y1;
  double x2, y2;
  double distance;
  
  printf("-> Distance entre 2 points d'un plan cartesien de coordonnees (x,y) <-\n");
  
  printf("* Entrer les coordonnees du point a : ");
  scanf("%lf %lf", &x1, &y1);
  printf("* Entrer les coordonnees du point b : ");
  scanf("%lf %lf", &x2, &y2);
  
  // Distance entre deux points A et B : AB = sqrt(|xB - xA|² + |yB - yA|²)
  distance = pow((fabs(x2 - x1)),2) + pow((fabs(y2 - y1)), 2);
  distance = sqrt(distance);
  printf("-> La distance entre les points a et b est : %.4lf\n", distance);
  
  return 0;
}
