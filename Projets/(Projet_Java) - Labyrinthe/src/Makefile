# Flag de compilation
JC = javac
# Flag d'option de compilation
JFLAGS = -g -encoding UTF-8 -implicit:none
# Flag d'execution
JT = java

# Définiton des suffixes à identifier
.SUFFIXES: .java .class
# Effectue la commande : "javac *.java" 
.java.class:
	$(JC) $(JFLAGS) $*.java

# Définie les classes liées au fichier java #
CLASSES = \
    View.java \
    Action.java \
    Controller.java \
    Ariane.java \
    Model.java \
    Build.java \
    Editor.java \
    State.java \
    Saving.java \
    Main.java

default: classes

classes: $(CLASSES:.java=.class)

# Effectue la commande : "java Main"
run:
	$(JT) Main

# Effectue la commande : "rm -f *.class"
clean:
	$(RM) *.class