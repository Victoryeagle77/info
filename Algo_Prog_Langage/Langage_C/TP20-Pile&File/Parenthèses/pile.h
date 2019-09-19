#ifndef PILE_H
#define PILE_H

struct maillon {
	char caractere;
	struct maillon* suivant;
};
typedef struct maillon* pile;

void push(pile* pp, char new);

char pop (pile* pp);

int top(pile p);


#endif