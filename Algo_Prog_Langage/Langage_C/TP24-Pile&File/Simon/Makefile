but: simon

CC = gcc
CCFLAGS = -g -o
OFILES = simon.o file.o

simon.o: simon.c file.h
file.o: file.c file.h

simon: $(OFILES)
	$(CC) $(CCFLAGS) simon $(OFILES) -lgraph

clean:
	-rm $(OFILES) simon

.PHONY: but clear

run:
	./simon