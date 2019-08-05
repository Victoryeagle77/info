#include <stdio.h>
#include <stdlib.h>

#include "pile.h"

void push(pile* pp, char new) {
  struct maillon* tmp;
  tmp=(struct maillon*)malloc(sizeof(struct maillon));
  tmp->caractere=new;
  tmp->suivant=*pp;
  *pp=tmp;
}

char pop (pile* pp) {
  struct maillon tmp=**pp;
  free(*pp);
  *pp=tmp.suivant;
  return tmp.caractere;
}

int top(pile p) { return p->caractere; }