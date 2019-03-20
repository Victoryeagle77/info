#include <stdio.h>
#include <stdlib.h>

#include "file.h"

void enqueue(file* pf, char new) {
	struct maillon* tmp;
	tmp=(struct maillon*)malloc(sizeof(struct maillon));
	tmp->couleur=new;
	tmp->suivant=NULL;
	if (pf->dernier!=NULL) {
		pf->dernier->suivant=tmp;
	} else {
		pf->premier=tmp;
		pf->dernier=tmp;
	}
}

unsigned dequeue(file* pf) {
	struct maillon* tmp;
	tmp=pf->premier;
	free(pf->premier);
	pf->premier=tmp->suivant;
	if (pf->premier==NULL) pf->dernier=NULL;
	return tmp->couleur;
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
	return f.premier->couleur;
}