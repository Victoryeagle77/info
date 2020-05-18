### 1] But final du fichier Makefile ###
compilation : exe

### 2] Variables des fichiers d'extension ".o" a creer ###
OFILES = src/main.o \
         src/interface.o \
         src/analyse.o

# Compilation et arguments de compilation
CC = gcc -Ofast -flto

### 3] Depedences a regles implicites des fichiers d'extension ".o" ###
analyse.o : ../header/analyse.h
interface.o : ../header/interface.h
main.o : data.o interface.o

### 4] Depedences precedentes appliquees par commandes ###
exe : $(OFILES)
	$(CC) -o exe $(OFILES) -lwiringPi -lX11 -pthread

### 5] Nettoyage des fichiers d'extension ".o" generes ###
clean :
	rm -f $(OFILES) exe
.PHONY : compilation clean

### 6] Execution du programme par l'executable ###
run :
	sudo ./exe
.PHONY : run
