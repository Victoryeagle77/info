###### Arthur Chenu ######

### 1] But final du fichier Makefile ###

compilation : show_process

### 2] Variables des fichiers d'extension ".o" à créer ###

OFILES = main.o \
	 gid.o \
	 uid.o \
	 sid_pgid.o \
	 pid_ppid.o

CC = gcc
# Compilation

### 3] Dépedences à règles implicites des fichiers d'extension ".o" ###

gid.o : ressource.h
uid.o : ressource.h
sid_pgid.o : ressource.h
pid_ppid.o : ressource.h
main.o : ressource.h gid.o uid.o sid_pgid.o pid_ppid.o

### 4] Dépedences précédentes appliquées par commandes ###

show_process : $(OFILES)
	$(CC) -g -o show_process $(OFILES)

### 5] Nettoyage des fichiers d'extension ".o" générés ###

clean :
	-rm -f $(OFILES) show_process

### 6] Argument facultatif "clean" permettant d'efféctuer le nettoyage ###

.PHONY : compilation clean
