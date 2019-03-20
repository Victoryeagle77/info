/*
Question 7 : Diversions. 
Considérons un programme qui comporte les déclarations suivantes :

	int a[] = {12, 23, 34, 45, 56, 67, 78, 89, 90};
	int* p = a;

Écrivez sur papier la valeur des expressions suivantes. 
(sauf pour les valeurs qui seront des adresse qu'on ne peut évidemment pas déterminer d'avance, marquez juste adresse):

	*p+2 	*(p+2) 	&p+1 	&a[4]-3
	a+3 	&a[7]-p 	p+(*p-10) 	*(p+*(p+8)-a[7])

Vous pouvez ensuite vérifier vos réponses en écrivant un programme. 
*/

#include <stdio.h>

int main(void){
	int a[] = {12, 23, 34, 45, 56, 67, 78, 89, 90};
	int* p = a;	
        printf("-> *p+2 = %d\n-> *(p+2) = %d\n-> &p+1 = %d\n-> &a[4]-3 = %d\n", *p+2, *(p+2), &p+1, &a[4]-3);
        printf("\n-> a+3 = %d\n-> &a[7]-p = %d\n-> p+(*p-10) = %d\n-> *(p+*(p+8)-a[7]) = %d\n", a+3, &a[7]-p, p+(*p-10), *(p+*(p+8)-a[7]));
	return 0;
}

/*
4) Pour déterminer le reste, déterminons d'abord le pointeur *p, il n'y a pas ici à pointer sur l'adresse du tableau a[] car celui-ci n'est pas 
initialisé avec un nombre de cases précis. Le pointeur *p pointe donc vers l'adresse des valeurs attirbuées au tableau a[]. 
Donc *p aura pour valeur la première case du tableau a[] sachant qu'il n'est pas initialisé soit et qu'il commence au rang 0 : 
*p = (première case de a[]) = 12.
On peut à présent déterminer le reste :

- *p+2 (avec un pointage vers la valeur de la première case soit 12) donc 12 + 2 = 14

- *(p+2), il s'agit d'un pointage vers *p+2, soit le rang de la première case de valeur 12 + le rang des 2 cases suivantes donc 
il s'agit de la valeur de la troisième case soit : *(p+2) = 34

- &p+1 aura pour valeur une adresse car p est défini en tant que pointeur et non en tant que variable manipulable par adresse.

- &a[4]-3 aura pour valeur une adresse car le tableau a[] n'est pas pointé vers son adresse.

- a+3 aura pour valeur une adresse car le tableau a[] n'est pas pointé vers son adresse.

- &a[7]-p, ici le pointeur p est présent en tant que variable, donc sachant que p=a cela revient à écrire &a[7]-a, 
or ici nous avons la présence de la variable ainsi que l'adresse du tableau a[], 
donc l'opérateur de soustraction va soustraire l'adresse de la variable à la variable elle-même et on obtiendra : &a[7]-p = 7.

- p+(*p-10) aura pour valeur une adresse car il y a ici p en tant que variable qui s'additionne au résultat de (*p-10) avec *p en tant que pointeur,
nous avons donc ici : adresse + (12-2) = adresse + 2 soit en définitive une adresse.

- *(p+*(p+8)-a[7]), on peut facilement détaillé le calcul à partir des réponses précédentes :
	> *(p+8) = Valeur de la première case du tableau + valeurs des 8 cases suivantes = valeur de la 9ème case donc *(p+8) = 90.
	> a[7] est une simple déclaration de la valeur de la 8ème case du tableau donc a[7] = 89.
	> Et il reste *(p + (90 - 89)) soit 12 + 1 soit la valeur de la 1ère case + 1 case = la valeur de la 2ème case soit 23.
*/
