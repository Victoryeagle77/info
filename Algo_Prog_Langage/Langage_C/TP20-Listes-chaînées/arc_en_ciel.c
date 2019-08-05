#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Structure définissant un élément de la liste (maillon) */
typedef struct ElementListeCirc { 
  char *donnee; 
  struct ElementListeCirc *suivant; 
} Element; 
/* Structure définissant la liste (prenant les maillon) */
typedef struct ListeRepereCirc { 
  Element *debut; 
  Element *fin; 
  int taille; 
} Liste; 

/* initialisation de la liste*/
void initialisation (Liste * liste){ 
  liste->debut = NULL; 
  liste->fin = NULL; 
  liste->taille = 0; 
} 
/* insertion dans une liste vide */ 
int ins_liste_circ_vide(Liste * liste, char *donnee){ 
  Element *nouveau_element; 
  if ((nouveau_element = (Element *) malloc (sizeof (Element))) == NULL) 
    return -1; 
  if ((nouveau_element->donnee = (char *) malloc (50 * sizeof (char))) == NULL) 
    return -1; 
  strcpy (nouveau_element->donnee, donnee); 
  nouveau_element->suivant = nouveau_element; 
  liste->debut = nouveau_element; 
  liste->fin = nouveau_element; 
  liste->taille++; 
  return 0; 
} 
/* insertion dans une liste non-vide */ 
int ins_liste_circ(Liste * liste, Element *courant, char *donnee){ 
  Element *nouveau_element; 
  if ((nouveau_element = (Element *) malloc (sizeof (Element))) == NULL) 
    return -1; 
  if ((nouveau_element->donnee = (char *) malloc (50 * sizeof (char))) == NULL) 
    return -1; 
  strcpy (nouveau_element->donnee, donnee); 
  if(courant != liste->fin){ return -1; } 
  nouveau_element->suivant = courant->suivant; 
  courant->suivant = nouveau_element; 
  liste->fin = nouveau_element; liste->taille++; 
  return 0; 
} 
/* suppression au début de la liste */ 	
int supp_liste_circ(Liste * liste){ 
  if (liste->taille < 2) return -1; 
  Element *supp_element; 
  supp_element = liste->debut; 
  liste->debut = liste->debut->suivant; 
  liste->fin->suivant = liste->debut; 
  free (supp_element->donnee); 
  free (supp_element); 
  liste->taille--; 
  return 0; 
} 
/* suppression dans une liste avec un seul élément*/ 	
int supp_liste_circ_unique(Liste *liste){ 
  if (liste->taille != 1){ return -1; }
  Element *supp_element; 
  supp_element = liste->debut; 
  liste->debut = NULL; 
  liste->fin = NULL; 
  free (supp_element->donnee); 
  free (supp_element); 
  liste->taille--; 
  return 0; 
} 
/* affichage de la liste */ 
void affiche (Liste * liste){ Element *courant; 
                             courant = liste->debut; 
                             int i; 
                             for(i=0;i<liste->taille;++i){ 
                               printf ("addr[%p] --> %s\n", courant, courant->donnee); 
                               courant = courant->suivant;
                             } 
} 

/* parcourir la liste à l'infini*/ 
void affiche_infini (Liste * liste){ 
  Element *courant; 
  courant = liste->debut;
  while (1){ 
    printf ("%p - %s\n", courant, courant->donnee); 
    courant = courant->suivant; 
  } 
} 
/* detruire la liste */ 
void detruire (Liste * liste){ 
  while (liste->taille > 0){ 
    if(liste->taille > 1) supp_liste_circ (liste); 
    else supp_liste_circ_unique(liste); 
  } 
} 

int menu (Liste *liste){ 
  int choix; 
  printf("********* MENU **********\n"); 
  if (liste->taille == 0){ 
    printf ("1] Ajout du 1er element\n"); 
    printf ("2] Quitter\n"); 
  }else{ 
    printf ("1] Ajout d'un élément\n"); 
    printf ("2] Suppression au début (la liste doit avoir au moins 2 éléments)\n"); 
    printf ("3] Suppression dans une liste avec un seul élément\n"); 
    printf ("4] Affiche liste circulaire\n"); 
    printf ("5] Affiche liste circulaire [Ctrl-C] pour quitter le programme\n"); 
    printf ("6] Détruire la liste\n"); printf ("7. Quitter\n"); 
  } 
  printf ("\n--> Faites votre choix : "); 
  scanf ("%d", &choix); 
  getchar(); 
  if(liste->taille == 0 && choix == 2){ choix = 7; } 
  return choix; 
}
  
int main (void) { 
  system("clear");
  char choix; 
  char *nom; 
  Liste *liste; 
  Element *courant; 
  if ((liste = (Liste *) malloc (sizeof (Liste))) == NULL)
    return -1; 
  if ((nom = (char *) malloc (50)) == NULL){ 
    return -1; 
    courant = NULL; 
    choix = 'o'; 
  }
  initialisation (liste); 
  while (choix != 7){ 
    choix = menu (liste); 
    switch (choix){ 
      case 1: 
        printf ("Entrez un element : "); 
        scanf ("%s", nom); 
        getchar ();
        if(liste->taille == 0) ins_liste_circ_vide (liste,nom); 
        else ins_liste_circ (liste,liste->fin,nom); 
        printf ("%d elements : debut = %s, fin = %s\n", liste->taille, liste->debut->donnee, liste->fin->donnee); 
        affiche (liste); 
        break; 
      case 2: 
        if(liste->taille < 2) { break; } 
        supp_liste_circ (liste); 
        if (liste->taille != 0) 
          printf ("%d elements : debut = %s, fin = %s\n", liste->taille, liste->debut->donnee, liste->fin->donnee); 
        affiche(liste); 
        break; 
      case 3: 
        if(liste->taille != 1) break; 
        supp_liste_circ_unique(liste); 
        printf("La liste est vide\n"); 
        break; 
      case 4: affiche(liste); break; 
      case 5: affiche_infini(liste); break; 
      case 6: 
        detruire (liste); 
        printf ("la liste a ete detruite : %d elements\n", liste->taille); 
        break; 
    } 
  } 
  return 0; 
}