#include "jeu.h"
#include "menu.h"
/* Permet d'obtenir en constante les plus grande valeur de chaque type */
#include <limits.h>
#include <string.h> 
/* Entier définissant une position par défaut hors du tableau d'entiers non-signés*/
#define DEFAULT -1

/* Déclaration globale pour d'avantage d'optimisation,
selon l'option de compilation -Ofast */
unsigned int secondes = 0; /* Nombre de secondes */
unsigned long tmp; /* Initialisation du timer */
char temps[CHAR_MAX]; /* CHAR_MAX ==> La valeur maximum que char peut contenir. */
unsigned short int dimension, paires;

/* Ensemble d'instrcution permettant de créer une zone intéractive cliquable,
en fonction des positions de la souris en abscisse et en ordonnée, 
(_X et _Y avec la librairie <graph.h>) par rapport à l'écran qui sont relevés */
unsigned short int interaction(short int x, short int y, 
                               unsigned short int zone[]) {
  if ((x > zone[0]) && (x < zone[0] + zone[2])) {
    if ((y > zone[1]) && (y < zone[1] + zone[3]))
      return 1; /* Pas dans la zone. */
  }
  return 0;
}

/* Fonction qui assure le mélange aléatoire d'une paire de carte,
 en fonction des cases dans la grille */
void melange(unsigned short int paire, unsigned short int grille[]) {
  unsigned short int i;
  unsigned short int remplissage[paire];
  unsigned short int distribution;
  srand(time(NULL));
  /* Initialisation de la "graine", pour une génération aléatoire efficace. 
  (Prend que des valeurs aléatoire supérieur à la précédente s'il elle n'y est pas)*/
  /* Génère les cartes 2 fois */
  for (i = 0; i < paire; i++) { remplissage[i] = 2; } 
  for (i = 0; i < (paire * 2); i++) {
    distribution = rand() % paire;
    /* La séléction vaut le brassage aléatoire au modulo d'une paire. 
    La carte généré sera donc multipliée par 2. */
    while (remplissage[distribution] == 0) {
      distribution++;
      distribution %= paire;
    }
    grille[i] = distribution;
    remplissage[distribution]--;
  }
}

/*** [1] Permet de vérifier la validité d'une paire et le retournement des cartes,
en changeant d'écran sur une zone précise. ***/
unsigned short int relever(zone case_x, zone case_y, 
                           unsigned short int grille[], unsigned short int score) {
  /* Si la case en abscisse est égale à la case en ordonnée. */
  if (grille[case_x[7]] == grille[case_y[7]]) {
    CopierZone(3, 0, case_x[0], case_x[1], case_x[2],
               case_x[3]+5, case_x[0], case_x[1]);
    CopierZone(3, 0, case_y[0], case_y[1], case_y[2],
               case_y[3]+5, case_y[0], case_y[1]);
    CopierZone(3, 1, case_x[0], case_x[1], case_x[2],
               case_x[3]+5, case_x[0], case_x[1]);
    CopierZone(3, 1, case_y[0], case_y[1], case_y[2],
               case_y[3]+5, case_y[0], case_y[1]);
    CopierZone(3, 2, case_x[0], case_x[1], case_x[2],
               case_x[3]+5, case_x[0], case_x[1]);
    CopierZone(3, 2, case_y[0], case_y[1], case_y[2],
               case_y[3]+5, case_y[0], case_y[1]);
    /* Compte le nombre de paires trouvées */
    score++;
  } else { /* Si elles sont différentes */
    /* Permettre de changer l'écran sur une zone précise, 
    pour retourner sur le dos les cartes découvertes qui ne sont pas paires entre elles. */
    CopierZone(1, 0, case_x[0], case_x[1], case_x[2],
               case_x[3], case_x[0], case_x[1]);
    CopierZone(1, 0, case_y[0], case_y[1], case_y[2],
               case_y[3], case_y[0], case_y[1]);
  }
  return score; 
}

/*** [2] Fonction timer affichant graphiquement le temps en secondes,
 depuis le début de la partie ***/
void timer(void){
  /* Incrémentation et affichage graphique du TIMER.
  Conversion de Microsecondes en seconde (soit 1 s = 10⁶ ms). */
  if (((Microsecondes() - tmp) > 1000000L)){ 
  /* Une periode s'est écoulée après une seconde. */
    secondes++; /* Incrémentation des secondes. */
    ChoisirEcran(0);
    tmp = Microsecondes();
    /* Evite d'empiler les chiffres les uns sur les autres */
    ChoisirCouleurDessin(CouleurParNom("gray"));
    RemplirRectangle(670, 720, 270, 30);
    ChoisirCouleurDessin(CouleurParNom("black"));
    sprintf(temps, " %d s", secondes); /* Conversion en chaine de caractère */
    CopierZone(2, 0, Maxx(), Maxy(), 0, 0, Maxx(), Maxy());
    EcrireTexte(680, 740, temps, 1);
  }
}

/*** [5] Fonction permettant d'intégrer le mode triche en appuyant sur la touche 'k' ***/
void triche(void){
  unsigned short int continuer = 1; 
  /* Boucle d'intégrité à valider et à invalider selon le clique */
  if (ToucheEnAttente() /* Permet d'activer la fonctionnalité du clavier 
  pour relever une future touche appuyée*/) {
    /* La touche sera déterminée par le renvoie de celle-ci */
    if (Touche() == XK_t) { /* Retourne les images */
      CopierZone(2, 0, 0, 0, Maxy(), Maxy(), 0, 0);
      ChoisirCouleurDessin(CouleurParNom("gray"));
      RemplirRectangle(670, 720, 270, 30);
      ChoisirCouleurDessin(CouleurParNom("black"));
      EcrireTexte(680, 150, "===  Mode triche actif  ===", 1);
      EcrireTexte(670, 700, "=== Timer (en secondes)  ===", 1);
      EcrireTexte(680, 740, temps, 1);
      while (continuer) {
        if (ToucheEnAttente()) {
          if (Touche() == XK_t) { 
            /* Évite de cliquer sur une carte et de sauvegarder son retournement, 
            au sortir du mod triche. */
            while (SourisCliquee());
            /* Reviens à l'écran de jeu */
            CopierZone(1, 0, 0, 0, Maxx(), Maxy(), 0, 0);
            /* Réaliser une seconde boucle, 
            au sein d'intégrité va permettre de stopper le timer */
            continuer = 0;
          }
        }
      }
    }
  }
}

/* Fonction définissant le jeu volontairement non-séparé en fonction,
 pour éviter l'utilisation d'instructions laborieuses tel que l'utilisation de pointeur, 
 pour 'cases'. */
void jeu(unsigned short int niveau) {
  /* Image de cartes à générer dans le dossier 'miniautures' */
  char* cartes[32] = {
    "1.png", "2.png", "3.png", "4.png", "5.png",
    "6.png", "7.png", "8.png", "9.png", "10.png",
    "11.png", "12.png", "13.png", "14.png", "15.png", 
    "16.png", "17.png", "18.png", "19.png", "20.png", 
    "21.png", "22.png", "23.png", "24.png", "25.png", 
    "26.png", "27.png", "28.png", "29.png", "30.png", 
    "31.png", "32.png" };
  
  /* Curseurs identifiant la position de retournement par défault des cartes,
  en abscisse et en ordonnée initialisée à -1.
  (valeur DEFAULT pour laquelle une carte ne peut pas être retournée) */
  short int case_x[] = {DEFAULT, DEFAULT};
  short int case_y[] = {DEFAULT, DEFAULT};
  /* Longueur de la chaine maximale "../images/miniatures/32.png" */
  char chemin[28]; 
  unsigned short int score = 0;
  /* Ecran de jeu*/
  InitialiserGraphique();
  CreerFenetre(0, 0, 1000, 860);
  ChoisirEcran(1);
  ChargerImageFond("../images/fond.png");
  
  /* Ecran avec les cartes */
  CopierZone(1, 2, 0, 0, Maxx(), Maxy(), 0, 0);
  /* Ecran avec les cartes supprimés */
  CopierZone(1, 3, 0, 0, Maxx(), Maxy(), 0, 0);
  /* Affichage de l'initialisation graphique du TIMER (à 0) */
  ChoisirCouleurDessin(CouleurParNom("gray"));
  /* Pour éviter que les chiffres s'empilent les uns sur les autres graphiquement,
  on place un rectangle de couleurs différentes sur le nombre précédent. */
  RemplirRectangle(670, 720, 270, 30);
  ChoisirCouleurDessin(CouleurParNom("black"));
  EcrireTexte(670, 700, "=== Timer (en secondes)  ===", 1);
  /* Dimension et nombre de paire en fonction du choix de difficultés */

  /*** [3] Choix de grille de taille différentes ***/
  if (niveau == 1) { dimension = 4; paires = 8; } 
  /* 16/2 = 8 paires*/
  else if (niveau == 2) { dimension = 6; paires = 18; } 
  /* 36/2 = 18 paires */
  else if (niveau == 3) { dimension = 8;  paires = 32; } 
  /* 64/2 = 32 paire */

  /* cases de la grille = paries multipliée par 2. */
  unsigned short int grille[paires * 2]; 
  melange(paires, grille); /* Mélange les paires dans la grille de jeu */
  /* Génération de la distribution des cartes en une grille,
  sous forme de carré de taille --> dimension */
  zone cases[dimension][dimension];
  unsigned short int i; /* ligne */
  for (i = 0; i < dimension; i++) {
    unsigned short int j; /* Colonne */
    for(j = 0; j < dimension; j++) {
      ChoisirEcran(1);
      /* On modifie uniquement la position de la distribution des cartes,
      en ligne et en colonne, choisie par le niveau de difficulté */
      if(niveau == 1) { /* Grille de 4 par 4, soit 16 cartes */
        cases[i][j][0] = (i * 80) + 50; /* Ajustement en ligne */
        cases[i][j][1] = (j * 120) + 180; /* Ajustement en colonne */
      } else if (niveau == 2) { /* Grille de 6 par 6, soit 36 cartes */
        cases[i][j][0] = (i * 80) + 50; 
        cases[i][j][1] = (j * 120) + 80;
      } else if (niveau == 3) { /* Grille de 8 par 8, soit 64 cartes */
        cases[i][j][0] = (i * 75) + 10; 
        cases[i][j][1] = (j * 105) + 10; 
      }
      cases[i][j][2] = 70; /* Résolution de l'image d'une carte en longueur. */
      cases[i][j][3] = 100; /* Résolution de l'image d'une carte en hauteur. */
      cases[i][j][4] = i; 
      /* Position de l'écart en abscisse à retourner s'il n'y a pas de paires. */
      cases[i][j][5] = j; 
      /* Position de l'écart en ordonnée à retourner s'il n'y a pas de paires. */
      cases[i][j][6] = 0; /* Position de point de mise en place de la carte sur l'écran. */
      /* Génère une carte pas plus de deux fois aléatoirement,
       en fonction de la hauteur ou longueur. */
      cases[i][j][7] = i + (dimension*j); 
      ChargerImage("../images/carte.png", cases[i][j][0], cases[i][j][1], cases[i][j][6],
                   cases[i][j][6], cases[i][j][2], cases[i][j][3]);
      
      ChoisirEcran(2); 
      /* Concaténation de la chaine de caractère "../images/miniatures/" avec la chaine 
      "x.png" ou x est un nombre de 1 à 32 (représentant le chemin relatif d'une image) . */
      strcat(strcpy(chemin, "../images/miniatures/"), cartes[grille[cases[i][j][7]]]);
      ChargerImage(chemin, cases[i][j][0], cases[i][j][1], cases[i][j][6], 
                   cases[i][j][6], cases[i][j][2], cases[i][j][3]);
    }
  }
  /* Choisis l'écran 1 par défault pour les cartes faces cachées */
  ChoisirEcran(1);
  CopierZone(1, 0, 0, 0, Maxx(), Maxy(), 0, 0);   
  while (1) {
    if (SourisCliquee()) {
      unsigned short int i;
      for (i = 0; i < dimension; i++) {
        unsigned short int j;
        for (j = 0; j < dimension; j++) {
          /* Condition appliquée pour toute carte cliquée présente dans la grille */
          if (interaction(_X, _Y, cases[i][j]) && ((case_x[0] != cases[i][j][4]) 
              || (case_x[1] != cases[i][j][5]))){
              /* On copie la zone vers l'écran virtuelle pour retourner les cartes,
              en prenant en considération que la zone cliquée doit comprendre pour une carte :
              - Sa disposition sur sur une ligne de la grille de jeu.
              - Sa disposition sur sur une colonne de la grille de jeu.
              - Sa dimension en longueur.
              - Sa dimension en hauteur.
              */
              CopierZone(2, 0, cases[i][j][0], cases[i][j][1], cases[i][j][2], 
                           cases[i][j][3], cases[i][j][0], cases[i][j][1]);
              /* Dans le cas ou un clique ne correspond pas à une carte dan la grille. */
              if (case_x[0] == DEFAULT) { 
                case_x[0] = cases[i][j][4];
                case_x[1] = cases[i][j][5];	
              } else { 
                case_y[0] = cases[i][j][4];
                case_y[1] = cases[i][j][5];
                /*** [4] Une seconde s'écoule avant que la carte se retourne ***/
                sleep(1); 
                /* sleep permet égalemnt de figer le timer pendant une seconde */
                score = relever(cases[case_x[0]][case_x[1]], 
                                cases[case_y[0]][case_y[1]], grille, score);
                case_x[0] = DEFAULT;
                case_y[0] = DEFAULT;
              }
            }
          }	
        }
      }
      timer();
      triche();
      if(score >= paires){
        /* S'il ne reste plus de paire sur l'écran, 
        afficher un message de victoire et quitter le jeu. */
        while(1) {
          EcrireTexte(430, 340, "== Bravo ==", 1);
          ChargerImage("../images/victoire.png", 440, 380, 0, 0, 100, 150);
          sleep(2); /* Attend 2 seconde avant de quitter */ 
          FermerGraphique();
          exit(0);
        }
      }
  }
}