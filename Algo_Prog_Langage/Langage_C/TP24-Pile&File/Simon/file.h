#ifndef FILE_H
#define FILE_H

struct maillon {
	unsigned couleur;
	struct maillon* suivant;
};
typedef struct {
	struct maillon* premier;
	struct maillon* dernier;
} file;

void enqueue(file* pf, char new);

unsigned dequeue (file* pf);

int empty(file f);

void clear(file* pf);

int top(file f);


#endif