#ifndef FILE_H
#define FILE_H

struct maillon {
  char caractere;
  struct maillon* suivant;
};
typedef struct {
  struct maillon* premier;
  struct maillon* dernier;
} file;

void enqueue(file* pf, char new);
char dequeue (file* pf);
int empty(file f);
void clear(file* pf);
int top(file f);

#endif