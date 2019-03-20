###### Arthur Chenu ######

### 1] But final du fichier Makefile ###

compilation : memory

### 2] Variables des fichiers d'extension ".o" à créer ###

OFILES =  main.o\
          menu.o \
          jeu.o

CC = gcc
# Compilation

CFLAGS = -ansi -Wall -Ofast -flto
# Option de vérification de compiltaion

CCOPT = -g -o
# Option de compilation

### 3] Dépedences à règles implicites des fichiers d'extension ".o" ###

jeu.o : jeu.h
menu.o : menu.h jeu.h
main.o : menu.h

### 4] Dépedences précédentes appliquées par commandes ###

memory : $(OFILES)
	$(CC) $(CFLAGS) $(CCOPT) memory $(OFILES) -lgraph
# Reviens à écrire ceci : 
# gcc -g -o <exécutable> <fichiers d'extension '.o'> -lgraph

### 5] Nettoyage des fichiers d'extension ".o" générés et appel de l'argument 'clean' avec make ###

clean :
	-rm -f $(OFILES) memory

.PHONY : compilation clean

### 6] Exécution du programme principale avec pour argument de make 'run' ###

run:
	./memory

.PHONY: run