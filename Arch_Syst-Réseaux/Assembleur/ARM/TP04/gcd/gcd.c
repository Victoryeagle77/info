/* Question 0.5 : gcd de 2 entiers
Faite un programme qui calcul le gcd de 2 entiers
On rappelle que gcd(a,0) = a, si a != 0 ; et si a et b sont non nuls, 
gcd(a, b) = gcd(b, a%b). Il n’y a pas de recursivite à considérer ici.
*/

#include <stdio.h>

int gcd(int a, int b){
  while(a != b){
    if(a > b) { a -= b; }
    else { b -= a; }
  }
  return a;
  // Ou retourne b quand il y a égailté avec a
}

int main(void){
  int a, b;
  printf("Entrer 2 entiers a et b : ");
  scanf("%d %d", &a, &b);
  printf("gcd(%d, %d) = %d", a, b, gcd(a, b));
}