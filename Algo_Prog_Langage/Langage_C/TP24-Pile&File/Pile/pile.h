#ifndef PILE_H
#define PILE_H

struct maillon {
  char caractere;
  struct maillon* suivant;
};
typedef struct maillon* pile;

void push(pile* pp, char new);
char pop (pile* pp);
int empty(pile p);
void clear(pile* p);
int top(pile p);

#endif