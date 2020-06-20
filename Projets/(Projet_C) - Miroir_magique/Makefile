### 1] But final du fichier Makefile ###
compilation : exe

### 2] Variables des fichiers d'extension ".o" a creer ###
OFILES = src/main.o \
	 src/database.o \
         src/interface.o \
	 src/graph.o \
	 src/composant.o \
	 src/utilitaire.o \
         src/analyse.o

# Compilation et arguments de compilation
CC = gcc -Ofast -flto

### 3] Depedences precedentes appliquees par commandes ###
exe : $(OFILES)
	$(CC) -o exe $(OFILES) -lwiringPi -lX11 -pthread

### 4] Nettoyage des fichiers d'extension ".o" generes ###
clean :
	rm -f $(OFILES) exe
.PHONY : compilation clean

### 5] Execution du programme par l'executable ###
run :
	sudo ./exe
.PHONY : run
