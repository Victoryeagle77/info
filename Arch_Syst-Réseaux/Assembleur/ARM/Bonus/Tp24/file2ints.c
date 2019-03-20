#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char ** argv) {

	if(argc != 3) {

		exit(1);
	}

	FILE * y;
	int a,b,c;

	b=open(argv[1],O_RDONLY,0644);
	if(b==-1) {
		perror("open");
		exit(2);
	}

	y=fopen(argv[2], "w");
	if(y==NULL) {
		perror("fopen");
		exit(3);
	}


	c=read(b,&a,4);
	if(c==-1) {
		exit(5);
	}
	fprintf(y,"%d",&a);

	exit(0);
}
