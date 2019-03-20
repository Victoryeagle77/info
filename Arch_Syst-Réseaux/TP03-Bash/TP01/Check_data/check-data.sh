# Question 3 : check-data #

# Ecrire un script check-data.sh qui prend 3 paramètres à la ligne de commande. 
# Le premier est un fichier contenant des représentations ; une représentation par ligne du fichier. 
# Le deuxième paramètre du script est un nombre entier entre 2 et 36. 
# Le script écrit dans le fichier donné en troisième argument, pour chaque représentation dans le
# fichier donné en premier argument, la liste des digits non conformes à la base donnée et deuxième argument.
# Voici le comportement attendu du script :

# $ ./check-data.sh
# Usage: ./check-data.sh <STRINGS_REPRESENTATIONS_FILE> <radix> <REPORTS_FILE>
# $ ./check-data.sh none.dat 3 reporting_file.dat
# none.dat does not exist or is not regular.
# $ cat strings_representations.dat
# 101
# 1011011
# 12010
# 11011201040
# 24A5204
# 15E12A122G84K48
# 493B6H
# 789810924

#!/bin/bash

clear

if [[ $# -ne 3 ]]
then
    echo "Usage: $0 <ficheir_source> <int> <fichier_destination>"
    echo "Conseil --> $0 none.dat 5 reporting_file"
    exit 1;
fi
# Vérifie si l'entier est plus petit que 36 et plus grand que 2
if [[ $2 -lt 2 || $2 -gt 36 ]]
then
    echo "L'entier doit être entre 2 et 36."
    exit 1;
fi
# Vérifier si le fichier existe déjà et propose son écrasement 
if [[ -f $3 ]]
then
    echo -n "$3 exist déjà. Ecraser ? oui/non --> "
    read reponse
    if [[ $reponse = oui ]]
    then
        rm $3
    else
        exit -1
    fi
fi

digits='0123456789abcdefghijklmnopqrstuvwxyz'

while read number
do
    echo -n ${number}:
    for j in $(seq $(expr length $number))
    do
        if [[ $(expr index $digits $(expr substr $number $j 1)) -gt $2 ]]
        then
            echo -n $(expr substr $number $j 1)
        fi
    done
    echo
done < $1 >> $3

exit 0