#include <stdio.h>
#include <stdlib.h>

#include "file.h"


void enqueue(file* pf, char new) {
	struct maillon* tmp;
	tmp=(struct maillon*)malloc(sizeof(struct maillon));
	tmp->caractere=new;
	tmp->suivant=NULL;
	if (pf->dernier!=NULL) {
		pf->dernier->suivant=tmp;
	} else {
		pf->premier=tmp;
		pf->dernier=tmp;
	}
}

char dequeue (file* pf) {
	struct maillon* tmp;
	char x;
	tmp=pf->premier;
	pf->premier=pf->premier->suivant;
	x=tmp->caractere;
	free(tmp);
	if (pf->premier==NULL) pf->dernier=NULL;
	return x;
}

int empty(file f) {
	return f.premier==NULL;
}

void clear(file* pf) {
	while (pf->premier!=NULL) {
		dequeue(pf);
	}
}

int top(file f) {
	return f.premier->caractere;
}