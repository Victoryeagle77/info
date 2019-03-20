/*
Question 3 : Groupe. 
Écrivez un programme qui affiche la liste des noms des utilisateurs qui appartiennent au groupe students17. 
La fonction getgrnam devrait vous y aider : lisez sa page manuelle.
*/


#include <stdlib.h>
#include <stdio.h>
// Librairie de la fonction getgrnam
#include <sys/types.h>
#include <grp.h>

/* Enumération de la strcuture group qui renverra un nom correspondant à un UID,
grâce à la fonction getgrnam de la librairie 'grp.h' permettant d'identifier . 
Cela permet d'identifier une liste d'utilisateur sur un réseau. */
struct group *getgrnam(const char *students18);

int main(void){
        // Redéfinition de la structure group en student18
	struct group students18;
	int i;
        // Passage de la chaine de caractère revoyant à un groupe d'utilisateur.
	students18 = *getgrnam("students18");
        // Pointeur pointé pour manipuler par adresse, l'adresse pointée du groupe d'utilisateur sur le réseau.
	char **eleve = students18.gr_mem;
        // Boucle indiquant pour tout utilisateur relevé, afficher ces derniers.
	for(i=0; eleve[i] != NULL; i++)
		printf("%s\n", eleve[i]);

	return EXIT_SUCCESS;
}
