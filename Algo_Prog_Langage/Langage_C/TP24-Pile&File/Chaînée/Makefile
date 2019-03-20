but: file

CC = gcc
CCFLAGS = -g -o
OFILES = chainee.o file.o

chainee.o: chainee.c file.h
file.o: file.c file.h

file: $(OFILES)
	$(CC) $(CCFLAGS) file $(OFILES)

clean:
	-rm $(OFILES) file

.PHONY: but clear

run:
	./file