/*
Question 5 : Chaînes. 

En C, les chaînes de caractères ne sont pas des listes chaînées, étrangement. 
Mais nous pouvons arranger ça : 
Ecrivez les définitions nécessaires pour représenter une chaîne de caractères 
comme une liste chaînée où chaque maillon contient un unique caractère.

Écrivez ensuite une fonction qui transforme une chaîne tableau en une chaîne liste, et une fonction qui fait l'inverse. 
Testez-les.

Si nous souhaitons utiliser les chaînes définies à l'exercice précédent, 
il faut pouvoir remplacer complètement les anciennes chaînes. 
Écrivez donc des fonctions qui procurent pour les nouvelles chaînes les fonctionnalités de puts et fgets. 
*/

#include <stdio.h>
#include <stdlib.h>

struct maillon{
	char caractere;
	struct maillon* suivant;
};
typedef struct maillon* depart;
typedef struct maillon maillon;

void chaine_liste(char* chaine,depart* liste){
	maillon* l;
	char c = ' ';
	int i = 0;
	for(; c!='\0'; i++){
		c = chaine[i];
		maillon* m = (maillon*) malloc(sizeof (maillon));
		m->suivant = NULL;
		m->caractere = c;
		if(*liste == NULL)
			*liste = m;
		else{
			for(l=*liste; l->suivant!=NULL; l=l->suivant);
			l->suivant = m;
		}		
	}

}

void liste_chainee(depart* liste,char** chaine){
	maillon* l;
	char* str = (char*) malloc(sizeof(char));
	int i = 1;
	for(l=*liste; l != NULL; l = l->suivant){
		str = (char*) realloc(str, i*sizeof(char));
		str[i-1] = l->caractere;
		i++;
	}
	str[i] = '\0';
	*chaine = str;
}

void afficher_liste(depart liste) {
    maillon* p;
    printf("Liste --> ");
    for(p = liste; p->suivant != NULL; p = p->suivant)
       printf("%c", p->caractere);
    putchar('\n');
}

void afficher_chaine(char* chaine){
	int i;
	printf("Chaine --> ");
	for(i=1; chaine[i] != '\0'; i++)
		printf("%c", chaine[i]);
	putchar('\n');
}

int main(int argc, char *argv[]){
	system("clear");
	depart liste = (depart) malloc(sizeof (maillon));
	char* string;
	int i;
	if(argc < 2){
		printf("Usage : %s <string>", argv[1]);
		return -1;
	}
	for(i=1; i<argc; i++){
		chaine_liste(argv[i],&liste);
		afficher_liste(liste);
		liste_chainee(&liste,&string);
		afficher_chaine(string);
	}
	return EXIT_SUCCESS;
}