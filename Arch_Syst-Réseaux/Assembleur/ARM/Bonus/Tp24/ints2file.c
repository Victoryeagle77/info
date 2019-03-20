#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char ** argv) {

	if(argc != 3) {

		exit(1);
	}

	FILE * x;
	int a,b,c;

	x=fopen(argv[1],"r");
	if(x==NULL) {
		perror("fopen");
		exit(2);
	}

	b=open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0644);
	if(b==-1) {
		perror("open");
		exit(3);
	}

	while(1) {

		c=fscanf(x,"%d",&a);
		if(c==EOF||c==0) {
			break;
		}
		write(b,&a,4);
	}

	if(c==0) {
		printf("Betise : \n");
		exit(5);
	}

	exit(0);
}
