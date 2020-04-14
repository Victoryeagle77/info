### 1] But final du fichier Makefile ###

compilation : snake

### 2] Variables des fichiers d'extension ".o" à créer ###

OFILES = main.o \
         jeu.o \

# Argument de compilation
CFLAGS = -Ofast -flto

### 3] Dépedences à règles implicites des fichiers d'extension ".o" ###

snake.o : jeu.h
main.o : jeu.o

### 4] Dépedences précédentes appliquées par commandes ###

snake : $(OFILES)
	gcc $(CFLAGS) -o snake $(OFILES) -lgraph

### 5] Nettoyage des fichiers d'extension ".o" générés ###

clean :
	-rm -f $(OFILES) snake
.PHONY : compilation clean

### 6] Exécution du programme par l'exécutable ###
run :
	./snake
.PHONY : run