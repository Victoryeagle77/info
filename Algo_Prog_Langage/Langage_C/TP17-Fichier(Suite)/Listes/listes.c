/*
Question 4 : Listes. 
Dans le cadre de cet exercice, une liste est un fichier contenant un ou plusieurs réels au format double little-endian.

- Écrivez un programme qui crée une liste en demandant une par une les valeurs à inclure à l'utilisateur.
- Écrivez un programme qui affiche une liste.
- Écrivez un programme qui vérifie si une liste est croissante. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int creation_liste(const char *argv[]);
int range_liste(int **, FILE *);
int ordonne_liste(int *, int, int);
void insertion(int *, int, int, int);
int affiche_liste(char const *argv[]);


/* Partie permettant d'inscrire des chiffre sour forme de liste dans un fichier */
int creation_liste(const char *argv[]){
    FILE *fichier;
	int valeur = 0, nombre = 0;
    int *taille = NULL; // Initialisation du tableau d'entier taille à NULL

    fichier = fopen(argv[1], "w"); // Ecriture seulement
        
    if (fichier != NULL) {
        printf ("Nombre de valeur a saisir : ");
        scanf ("%d", &nombre);
        // Définition de malloc pour entrer le nombre souhaité de nombres
        taille = (int *)malloc(sizeof(int) * nombre);
        for(valeur=0; valeur < nombre; valeur++){
            printf("Reel --> ");
            scanf("%d", &taille[valeur]);
            fprintf(fichier, "%d\n", taille[valeur]);
        }
        free(taille); // Libération de l'espace mémoire pris par le malloc().
        fclose(fichier);
    } else {
        perror("/!\\ Lecture impossible /!\\ ");
        return -1;
    }
}

int range_liste(int **rangement, FILE *fichier){
   int nb_valeur = 0; 
   int position, indice, i;
  
   while (fscanf(fichier, "%d", &position) != EOF) { nb_valeur++; }
   
   *rangement = (int *)malloc(nb_valeur * sizeof(int));
   // Présent dans <stdio.h>, rewind(FILE *) permet de se positionner au début d'un fichier.
   rewind(fichier); 
   nb_valeur = 0;
    while (fscanf(fichier, "%d", &position) != EOF){
        indice =  ordonne_liste(*rangement, nb_valeur, position);
        if (indice == -1) { nb_valeur++; } // Dans le cas ou un indice est déjà présent
        else {
		  // Permet d'insérer les valeurs classée dans l'ordre croissant
		  insertion(*rangement, nb_valeur, position, indice);
		  nb_valeur++;
	    }
    }
    // Réallocation du tableau rangement en cas de dépassement
    *rangement = (int *)realloc(*rangement, nb_valeur * sizeof(int));
    return nb_valeur;
}

/* Vérifie si la liste est croissante, si elle ne l'est pas, 
elle est ordonnée dans l'ordre croissant */
int ordonne_liste(int * rangement, int nb_valeur, int position){
    // On identifie chaque position par rapport au fichier
    int gauche = 0, droite = nb_valeur - 1, centre;
    while (gauche <= droite){
	    centre = (gauche + droite) / 2;
	    if (position <= rangement[centre]) { droite = centre - 1; }
	    else if (position >= rangement[centre]) { gauche = centre + 1; }
	    else { return -1; }
    }
    return gauche;
}

void insertion(int *rangement, int nb_valeur, int position, int indice){
  int i;
  for(i = nb_valeur; i > indice; i--) { rangement[i] = rangement[i - 1]; }
  rangement[indice] = position;
}

int affiche_liste(char const *argv[]){
    unsigned int flux; // Définition en entier positid du flux de donné d'un fichier 
    char buffer[BUFSIZ]; // Permettera de ranger les données (caractères) du flux.
    int taille; // Taille du buffer
    /* Récupération d'un flux sur le fichier */
    flux = open(argv[1], O_RDONLY); // Lecture seulement du fichier.
    // LECTURE FICHIER
    taille = read(flux, buffer, 256);
    buffer[taille] = 0; // Taille du buffer initialisé à 0 pour le future stockage.
    /* AFFICHAGE FICHIER
    Affichage des éléments lus dans la console : */
    write(1, buffer, taille);
    /* Fermeture du flux de donné */
    close(flux);
}

int main(int argc, const char * argv[]){
	int *rangement;
	int nb_valeur, i;  
	FILE * fichier;
	system("clear");
	if (argc != 2){
	    printf("%s <name_source_list_file>\n", argv[0]);
	    return -1;
    }
    // Création puis lecture de la liste dans un fichier source
    creation_liste(argv);
    
    fichier = fopen(argv[1], "r");
	nb_valeur = range_liste(&rangement, fichier);
	fclose(fichier);
	
	fichier = fopen(argv[1], "w");
	// Permet d'écrire la liste dans le fichier.
	fprintf(fichier, "=== Liste Croissante ===\n\n");
    for(i = 0; i < nb_valeur; i++) { fprintf(fichier, " %d ", rangement[i]); }
    puts("\n> Creation et rangement de la liste finis <");
    printf("\nContenu de la liste du fichier %s :\n\n", argv[1]);
	
    free(rangement);
	fclose(fichier);
    // Affichage à la console de la liste croissante
    affiche_liste(argv);
	return 0;
}