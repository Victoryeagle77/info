/*
Qestion 5 : Étapes. Considérez (sans l'exécuter) le programme suivant :

int main(void) {
  int a = 1, b = 2, c = 3;
  int *p, *q;
 
  p=&a;
  q=&c;
  *p=(*q)++;
  p=q;
  q=&b;
  *p-=*q;
  ++*q;
  *p*=*q;
  a=++*q**p;
  p=&a;
  *q=*p/(*q);
  return EXIT_SUCCESS;
}

Simulez sur papier le déroulement du programme. Après l'exécution de chaque instruction, 
répondez aux questions suivantes :

    Que contiennent a, b et c ?
    Vers quoi pointent p et q ?

Vous pouvez tester vos réponses en exécutant réellement le programme, 
auquel vous aurez rajouté quelques appels à printf. 
*/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int a = 1, b = 2, c = 3;
  int *p, *q;
  
  printf("-> Etapes du pointage d'un tas d'instructions <-\n");
  p=&a;
  q=&c;
  printf("p=&a : %d, q=&c : %d\n", p, q);
  *p=(*q)++;
  printf("*p=(*q)++ : %d\n", *p);
  p=q;
  printf("p=q : %d\n", p);
  q=&b;
  printf("q=&b : %d\n", q);
  *p-=*q;
  printf("*p-=*q : %d\n", *p);
  ++*q;
  *p*=*q;
  printf("*p*=*q : %d\n", *p);
  a=++*q**p;
  printf("a=++*q**p : %d\n", a);
  p=&a;
  printf("p=&a : %d\n", p);
  *q=*p/(*q);
  printf("*q=*p/(*q) : %d\n", *q);
  return EXIT_SUCCESS;
}

/* 
5) - Il y a trois variable a = 1, b = 2 et c = 3 et deux pointeurs p et q.
*** Dans l'ordre du programme ***
- p = l'adresse de a et q = l'adresse de c (et non pas leur valeur en tant que variables soit 1 et 3).
- Le pointeur *p = le pointeur *q qui est incrémenté poistivement soit *q + 1, 
(or sachant que q = l'adresse de c, 
alors *q pointe vers la valeur à laquelle est attribuée cette adresse soit le pointeur *q = 3 + 1).
- p = l'adresse de q.
- q = l'adresse de b donc, pour l'instruction précédente, p = l'adresse de b.
- Le pointeur *p = le pointeur *p - le pointeur *q (avec le pointeur *p = 4 et le pointeur *q = b = 2) 
donc le pointeur *p = 4 - 2 = 2.
- Le pointeur *q est incrémenté positivement donc le pointeur *q = 2 + 1 = 3.
- Le pointeur *p = le pointeur *p * le pointeur *q donc 2 * 3 = 6.
- La variable a = (le pointeur *q + 1) * le pointeur *p, soit a = (3 + 1) * 6 = 4 * 6 = 24.
- p = l'adresse de a (sa valeur en tant que variable est à présent 24).
- Le pointeur *q = le pointeur *p / le pointeur *q (avec le pointeur *p = 24 et le pointeur *q = 6) 
donc 24 / 4 = 6.
--> Le résultat final est donc 6 <--

Si on demande au programme d'afficher le résultat, le programme affichera bien que la valeur de *q est 6.
*/