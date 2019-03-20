#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int binomeS(int n, int m) {

int x,y,z;

if(n==m) goto L;
if(n==0) goto L;

m=m-1;

x=binomeS(n,m);
n=n-1;
y=binomeS(n,m);
z=x+y;

goto out;

L:

z=1;
goto out;

out:

return z;
}

int main(int argc,char ** argv) {

int x,y,z,fd,fo,v;

fd=open("ints.dat",O_RDONLY,0644);
if(fd!=-1) goto read;
exit(1);

read:

v=read(fd,&x,4);
if(v==-1) exit(2);
v=read(fd,&y,4);
if(v==-1) exit(2);

close(fd);

if(x<=y) goto Func;
printf("Non defini\n");
exit(1);

Func:

z=binomeS(x,y);

fo=open("out.txt",O_WRONLY|O_TRUNC|O_CREAT,0644);
if(fo!=-1) goto write;
exit(3);

write:
v=write(fo,&z,4);
if(v==-1) exit(4);

close(fo);

exit(0);
}
