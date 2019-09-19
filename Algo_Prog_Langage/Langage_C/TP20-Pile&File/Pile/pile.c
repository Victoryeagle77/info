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

int empty(pile p) {
  return p==NULL;
}

void clear(pile* p) {
  while (*p!=NULL) { pop(p); }
}

int top(pile p) {
  return p->caractere;
}