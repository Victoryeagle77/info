#include <stdio.h>
#include <stdlib.h>

/*
 bc(n,0) = 1;
 bc(n,n) = 1;
 bc(n,k) = bc(n,k-1)+bc(n-1,k-1);
*/


int binomefdp(int n, int m) {

if((n==m)||(n==0)){
return 1;
}

return binomefdp(n,m-1)+binomefdp(n-1,m-1);
}

int main(int argc,char ** argv) {
int x,y,z;
x=(int) strtol(argv[2],NULL,0);
y=(int) strtol(argv[1],NULL,0);

if(x>y) {
printf("Non defini\n");
exit(1);
}

z=binomefdp(x,y);
printf("%d\n",z);
exit(0);
}
