#ifndef GENERATION_H
#define GENERATION_H

struct terrain{
  int x;
  int y;
  int niveau;
};

typedef struct terrain terrain;

terrain** Creation(terrain**,int,int);
terrain** Remplissage(terrain**,int,int);

#endif