# Question 2 : bin2dot-with-for.sh #

# bin2dot-with-for.sh, prend deux arguments. Le premier est un fichier contenant
# des adresses ipv4 en représentation binaire (dans le fichier in_ipv4_addres.dat). 
# Le deuxième est un fichier qui contiendrales mêmes adresses ipv4 mais en notation décimale pointée. 
# On affectera une variable, disons addr, successivement à l’aide d’une commande composée for.
# Par exemple :
# $ cat bin_ipv4_addres.dat
# 10110010111000101000011101110010
# 11100101110001010101100101010010
# 00110010111001101000010001110010
# $ ./bin2dot-with-for.sh bin_ipv4_addres.dat
# Usage: ./bin2dot-with-for.sh <SRC_FILE> <DEST_FILE>
# $ ./bin2dot-with-for.sh bin_ipv4_addres.dat dot_ipv4_addres.dat
# $ cat dot_ipv4_addres.dat
# 178.226.135.114
# 229.197.89.82
# 50.230.132.114
# $ cat >> bin_ipv4_addres.dat
# 11110000111111110000000010101010
# 1$ cat bin_ipv4_addres.dat
# 10110010111000101000011101110010
# 11100101110001010101100101010010
# 00110010111001101000010001110010
# 11110000111111110000000010101010
# $ ./bin2dot-with-for.sh bin_ipv4_addres.dat dot_ipv4_addres.dat
# dot_ipv4_addres.dat exists. Overwrite? Yes/No --> Yes
# $ cat dot_ipv4_addres.dat
# 178.226.135.114
# 229.197.89.82
# 50.230.132.114
# 240.255.0.170

#!/bin/bash

clear

if [[ $# -ne 2 ]]
then
    echo "Usage: $0 <fichier_source> <fichier_destination>"
    echo "Conseille --> $0 bin_ipv4_addres.dat resultat.txt"
    exit
fi
# Test de l'existance de l'emplacment du fichier
if [[ ! -f $1 ]]
  then 
  echo "$1 n'existe pas ou n'est pas présent dans le dossier"
  exit
fi
# Si le fichier existe déjà
if [[ -f $2 ]]
  then
  echo -n "$2 existe, écraser ? oui/non --> "
  read reponse
  if [[ $reponse != "oui" ]]
  then 
    exit
  fi
rm -rf $2 # Réinitialise le fichier $2
fi

  for addr in `cat $1`
  do
    a=$(expr substr $addr 1 8)
    b=$(expr substr $addr 9 8)
    c=$(expr substr $addr 17 8)
    d=$(expr substr $addr 25 8) 
    point=$((2#$a)).$((2#$b)).$((2#$c)).$((2#$d))
    echo "$point" >> $2
  done

exit