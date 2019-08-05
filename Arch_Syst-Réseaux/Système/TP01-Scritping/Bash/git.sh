# Question 6 : git #

# Faite un script qui permet d'envoyer sur git des pour un utilisateur,
# A partir de sa racine.

#!/bin/bash

Commission(){
	echo "****** Commission Git ******"
	echo "-> Dossiers disponibles <-"
	echo ""
	cd ~/$1
	git pull
	git add .
	git commit -m "commits"
	git push
}

clear

if [[ $# -ne 1 ]]
then
	echo "Usage: <repertoire/dossier>"
	exit 1;
fi
Commission "$1"