# Dossier ou se trouve le code à compiler
SOURCE = .
# Dossier ou se trouve les class à utiliser
CLASSES = class
# Option de compilation
JFLAGS = -sourcepath $(SOURCE) -d $(CLASSES) -encoding utf-8
# Compilation
JC = javac
# Intègre le chemin du fichier mariadb-client.jar, 
# permettant de se connecter à la base de données.
DATABASE = ./mariadb-client.jar
# Exécution
JE = java -classpath $(CLASSES):$(DATABASE)

compilation: $(SOURCE)
	$(JC) $(JFLAGS) $(SOURCE)/src/*.java

run:
	$(JE) src/Main

clean:
	rm -rf $(CLASSES)/*

.PHONY: clean