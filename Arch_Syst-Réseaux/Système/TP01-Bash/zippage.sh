# Question 5 : Compression #

# Créer un fichier peremttant d'archiver un dossier,
# dont le nom est passé en argument.

#!/bin/bash

Compression(){
	echo "****** Compression ******"
	echo ""
	tar -cvf "$1.tar.gz" $1 
	echo "archive ok =>" $1
}

clear 

if [[ $# -ne 1 ]]
then
	echo "Usage: <repertoire/dossier>"
	exit 1;
fi
Compression "$1"