but: pile

CC = gcc
CCFLAGS= -g -o
OFILES = parentheses.o pile.o

parentheses.o: parentheses.c pile.h
pile.o: pile.c pile.h

pile: $(OFILES)
	$(CC) $(CCFLAGS) pile $(OFILES)

clean:
	-rm $(OFILES) pile

.PHONY: but clear

run:
	./pile