# Question 4 : roun.sh #

# Ecrire round.sh qui prend deux arguments. Le premier est un nombre décimal donné
# sous la forme [-]interger[.[fractional_part]], c’est à dire un nombre décimal avec
# éventuellement un signe “-”, avec éventuellement une partie fractionnaire introduite par
# un symbole “.” (exemples ci-après). Le deuxième argument est un nombre strictement
# positif. Le script affiche le nombre donné en position du premier argument, écrit avec
# un nombre de chiffres après la virgule indiqué par le deuxième argument. Le nombre est
# arrondi au besoin selon les conventions usuelles :
# $ ./round.sh 45 2
# 45.00

#!/bin/bash

clear 

length(){
    # Retourne la longueur de la chaine de $1
    expr length $1
}

caractere(){
    # Retourne la chaine de caractère de $1 à l'index $2
    expr substr $1 $2 1
}

partie_entiere(){
    # Retourne la partie de $1 d'index $2 à la fin $1
    expr substr $1 $2 $(length $1)
}

fractionaire(){
    # Retourne la partie de $1 d'index 1 à l'index $2
    expr substr $1 1 $2
}

if [[ $# -ne 2 ]]
then
    echo "Usage: $0 <float> <int>"
    exit 1;
fi

nombre=$1
if ! [[ $nombre =~ ^[-]?[0-9]+\.?[0-9]*$ ]]
then
    echo "Incorrect format for first arg."
    exit 1;
fi

fraction=$(expr index $1 .)
if [[ $fraction == 0 ]] # Partie non-fractionnaire
then
    entier=$1
else
    entier=$(fractionaire $nombre $(($fraction - 1)))
    decimal=$(partie_entiere $nombre $(($fraction + 1)))
fi

# Mettre un "." à la fin de $nombre si nécessaire
if [[ $decimal == "" && $(caractere $nombre $(expr length $nombre)) != "." ]]
then
    # Ecrire un "." pour préparer l'écriture de la partie fractionnaire
    nombre=${nombre}.
fi

res=$(($(length $entier) + $2 + 1))

if [[ $(length $nombre) -lt $res ]]
then

   while [[ $(length $nombre) -lt $res ]]
   do
       # Mettre des 0 après la partie entière s'il n'y a pas de partie fractionnaire
       nombre=${nombre}0
   done

elif [[ $(length $nombre) -gt $res ]]
    then
        arrondir=$((`length $decimal` - $2))

        for i in $(seq $arrondir)
        do

            if [[ $(partie_entiere $decimal `length $decimal`) -gt 4 ]]
            then
                arg=$(caractere $decimal $((`length $decimal` - 1)))
                if [[ $arg -eq 10 ]]
                then
                    reste=1
                else
                    arg=$(($arg + 1))
                    reste=0
                fi
                decimal=$(fractionaire $decimal $((`length $decimal` - 2)))$arg
            else
                decimal=$(fractionaire $decimal $((`length $decimal` - 1 )))
            fi
        done
        nombre=${entier}.${decimal}
fi
# Afficher le nombre décimal avec sa partie fractionnaire
echo $nombre
exit 0