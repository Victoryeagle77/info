#include <stdio.h>
#include <stdlib.h>

int max(int a,int b,int c) {
int x=a;

if(x<b) {
x=b;
}
if(x<c) {
x=c;
}

return x;
}

int main(int argc, char ** argv) {

if(argc!=4) {
printf("Usage : %s <int1> <int2> <int3>\n",argv[0]);
exit(1);
}

int x,y,z,a;

x=(int) strtol(argv[1],NULL,0);
y=(int) strtol(argv[2],NULL,0);
z=(int) strtol(argv[3],NULL,0);

a=max(x,y,z);
printf("Le maximum est : %d\n",a);
exit(0);
}
