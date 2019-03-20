/*
Question 1 : Lecture
Faite un programme permettant de saisir un mot de passe ne faisant pas plus de 26 caractères.
Dire si l'authentification est correcte ou non. 
Vous ne pouvez pas utiliser scanf ou fgets.
*/

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
	char password[256];
	char confirm_passwd[256];
	int i, j;
	// On utilisera getchar() qui récupère un seul caractère
	printf("--> Entrez un mot de passe : ");
	for (i = 0; i < 26 && password[i-1] !='\n'; ++i)
		password[i]=getchar();
	password[i-1]='\0';
	
	printf("--> Confirmez le mot de passe : ");
	for (j = 0; j < 26 && confirm_passwd[j-1] !='\n'; ++j)
		confirm_passwd[j]=getchar();
	confirm_passwd[j-1]='\0';
    // Méthode strcmp() comparant deux chaînes de caractères
	printf("\n--> ");
	if (strcmp(password, confirm_passwd)==0) // Compare 2 chaînes de caractère
		printf("Authentification reussit !");
	else
		printf("Echec d'authentification !");

	putchar('\n');
	printf("--> Mot de passe d'origine : %s\n", password);
	return 0;
}
