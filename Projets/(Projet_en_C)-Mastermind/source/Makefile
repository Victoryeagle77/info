### 1] But final du fichier Makefile ###

compilation : mastermind

### 2] Variables des fichiers d'extension ".o" à créer ###

OFILES = objets.o \
         jeu.o \
         main.o

CC = gcc
# Compilation

CFLAGS = -ansi -Wall -Ofast -flto
# Option de vérification de compiltaion

CCOPT = -g -o
# Option de compilation

### 3] Dépedences à règles implicites des fichiers d'extension ".o" ###

objets.o : objets.h
jeu.o : objets.h
main.o : jeu.h

### 4] Dépedences précédentes appliquées par commandes ###

mastermind : $(OFILES)
	$(CC) $(CFLAGS) $(CCOPT) mastermind $(OFILES) $(CFLAGS) -lgraph
# Reviens à écrire ceci : 
# gcc -g -o <exécutable> <fichiers d'extension '.o'> -lgraph

### 5] Nettoyage des fichiers d'extension ".o" générés et appel de l'argument 'clean' avec make ###

clean :
	-rm -f $(OFILES) 

.PHONY : compilation clean

### 6] Exécution du programme principale avec pour argument de make 'run' ###

run: 
	./mastermind

.PHONY : run
