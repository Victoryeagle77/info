but: pile

CC = gcc
CCFLAGS= -g -o
OFILES = chainee.o pile.o

chainee.o: chainee.c pile.h
pile.o: pile.c pile.h

pile: $(OFILES)
	$(CC) $(CCFLAGS) pile $(OFILES)

clean:
	-rm $(OFILES) pile

.PHONY: but clear

run:
	./pile