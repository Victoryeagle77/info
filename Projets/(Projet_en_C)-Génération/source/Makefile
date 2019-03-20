### 1] But final du fichier Makefile ###

compilation : mapping

### 2] Variables des fichiers d'extension ".o" à créer ###

OFILES =  main.o \
          affichage.o \
          accueil.o \
          generation.o

CC = gcc
# Compilation

CFLAGS = -ansi -pedantic -Wall -Ofast -flto
# Option de vérification de compiltaions

CCOPT = -g -o
# Option de compilation

### 3] Dépedences à règles implicites des fichiers d'extension ".o" ###

generation.o : generation.h
accueil.o : accueil.h
affichage.o : affichage.h generation.h
main.o : generation.h affichage.h accueil.h

### 4] Dépedences précédentes appliquées par commandes ###

mapping : $(OFILES)
	$(CC) $(CFLAGS) $(CCOPT) mapping $(OFILES) -lgraph
# Reviens à écrire ceci : 
# gcc -g -o <exécutable> <fichiers d'extension ".o"> -lgraph

### 5] Nettoyage des fichiers d'extension ".o" générés et appel de l'argument 'clean' avec make ###

clean :
	-rm -f $(OFILES) mapping

.PHONY : compilation clean

### 6] Exécution du programme principale avec pour argument de make 'run' ###

run:
	./mapping

.PHONY: run
