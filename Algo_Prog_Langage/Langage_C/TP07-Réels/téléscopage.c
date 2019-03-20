#include <stdio.h>

int main(void){
   double n;
   char c;
   printf("Saisir un reel : ");
   scanf("%lf", &n); 
   printf("Notation scientifique : %.3e\n", n);

   printf("Saisir un caractere : ");
   scanf(" %c", &c);
   for(int i=0; i<5; i++)
       printf("Caractere : %c\n", c);
   return 0;
}

/* 
On aurais pour habitude, après affichage du nombre en notation scientifique, 
de coder la saisie d'un caractère comme ceci :

scanf("%c", &c);

Car cela fonctionne bien pour tout scanf() contenant un format de définition de nombre. 
Mais il s'agit ici d'un caractère à saisir.

Si on ne laisse pas un espace dans le format, il restera un saut de ligne et le caractère
affiché sera alors un saut de ligne.
*/ 
