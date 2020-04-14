EXE = httpd 

all : $(EXE)

# Compilation #
httpd : httpd.o helpers.o 
	gcc -o httpd httpd.o helpers.o
httpd.o : httpd.c helpers.h 
	gcc -c httpd.c
helpers.o : helpers.c helpers.h
	gcc -c helpers.c

# Nettoyage #
clean :
	rm -f $(EXE) *.o

# Execution #
run :
	./httpd
