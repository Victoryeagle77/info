#include <stdio.h>
#include <stdlib.h>

#include "pile.h"

void main (void) {
	pile p=NULL;
	FILE* flux;
	int res;
	char in, out;
	flux=fopen("test.txt", "r");
	if (flux==NULL) return;
	while (1) {
		res=fread(&in,sizeof(char),1,flux);
		if (res!=1) break;
		if (in=='('||in=='{'||in=='[') 
			push(&p,in);
		else if (in==')'||in=='}'||in==']') {
			out=top(p);
			if (out==in) { pop(&p); } 
			else {
				printf("Mauvais parenthesage\n");
				break;
			}
		}
	}
}