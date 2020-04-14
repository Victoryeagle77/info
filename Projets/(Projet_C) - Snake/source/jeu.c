#include "jeu.h"

#define SERPENT 5
#define ESPACE 20
#define MAP_W 40
#define MAP_H 25
#define MARGE 20
#define TIMER 100000

static volatile unsigned short int pomme[2], direction[2];
static volatile unsigned int score, cycle;
static volatile unsigned short int **grille;
static volatile unsigned short int continuation;

static volatile couleur fond, vert, rouge;

static void deplacement(void){
	static volatile unsigned short int tmp[2], temp[2];
	static volatile unsigned short int i;

	tmp[0] = grille[0][0];
	tmp[1] = grille[0][1];
	grille[0][0] += direction[0];
	grille[0][1] += direction[1];
	
	if(grille[0][0] > ((MAP_W-1)*ESPACE)+MARGE || grille[0][0] < MARGE)
		continuation = 0;
	
	else if(grille[0][1] > ((MAP_H-1)*ESPACE) + MARGE || grille[0][1] < MARGE)
		continuation = 0;
	
	else if(grille[0][0] == pomme[0] && grille[0][1] == pomme[1]){
		pomme[0] = ((rand()%(MAP_W))*ESPACE) + MARGE;
		pomme[1] = ((rand()%(MAP_H))*ESPACE) + MARGE;
		score++;
		grille = realloc(grille, score*sizeof(volatile unsigned short int*));
		grille[score-1] = malloc(2*sizeof(volatile unsigned short int));
		cycle = TIMER - (TIMER/(MAP_H*MAP_W))*score;
	}

	for(i=1; i<score; i++){
		temp[0] = grille[i][0];
		temp[1] = grille[i][1];
		
		grille[i][0] = tmp[0];
		grille[i][1] = tmp[1];
		
		tmp[0] = temp[0];
		tmp[1] = temp[1];
	}
}

static void afficher(void){
	static volatile unsigned short int i;
	ChoisirCouleurDessin(fond);
	RemplirRectangle(0, 0, LARGEUR, LONGUEUR);
	ChoisirCouleurDessin(vert);
	DessinerRectangle(MARGE, MARGE, MAP_W*ESPACE, MAP_H*ESPACE);
	
	for(i=0; i<score; i++)
		RemplirRectangle(grille[i][0], grille[i][1], ESPACE, ESPACE);
		
	ChoisirCouleurDessin(rouge);
	RemplirRectangle(pomme[0], pomme[1], ESPACE, ESPACE);
}

extern void initialiser(void){
	static volatile unsigned short int i;
	continuation = 1;
	cycle = TIMER;
	score = SERPENT;
	*direction = 0;
	
	vert = CouleurParComposante(10,255,50);
	fond = CouleurParComposante(20,20,20);
	rouge = CouleurParComposante(255,0,0);
	
	grille = malloc(SERPENT*sizeof(volatile unsigned short int*));
	
	for(i=0;i<SERPENT;i++){
		grille[i] = malloc(2*sizeof(volatile unsigned short int));
		grille[i][0] =(MARGE*ESPACE)/2;
		grille[i][1] =(MARGE*ESPACE)/2;
	}
	pomme[0] = ((rand()%(MAP_W))*ESPACE) + MARGE;
	pomme[1] = ((rand()%(MAP_H))*ESPACE) + MARGE;
}

extern void jeu(void){
	sleep(1);
	*direction = 0;
	static volatile KeySym touche;
	afficher();
	while(continuation==1){
		while((!(ToucheEnAttente())) && (continuation)){
			usleep(cycle);			
			deplacement();
			afficher();
		}
		touche = Touche();
		if(touche == XK_z){
			if(direction[1] == 0){
				direction[0] = 0;
				direction[1] -= ESPACE;
			}
		}else if(touche == XK_q){
			if(direction[0] == 0){
				direction[0] -= ESPACE;
				direction[1] =0;
			}
		}else if(touche == XK_d){
			if(direction[0] == 0){
				direction[0] = ESPACE;
				direction[1] = 0;
			}
		}else if(touche == XK_s){
			if(direction[1] == 0){
				direction[0] =0;
				direction[1] = ESPACE;
			}
		}
	}
}