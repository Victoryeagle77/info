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
    # Returns length of $1
    expr length $1
}

char-at-index(){
    # Returns char of $1 at index $2
    expr substr $1 $2 1
}

str-from-index(){
    # Returns part of $1 from index $2 to the end of $1
    expr substr $1 $2 $(length $1)
}

str-till-index(){
    # Returns part of $1 from index 1 to index $2
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

separateur=$(expr index $1 .)
if [[ $separateur == 0 ]] # No fractionnal part
then
    entier=$1
else
    entier=$(str-till-index $nombre $(($separateur - 1)))
    decimal=$(str-from-index $nombre $(($separateur + 1)))
fi

# Adds . to the end of $nombre if required
if [[ $decimal == "" && $(char-at-index $nombre $(expr length $nombre)) != "." ]]
then
    nombre=${nombre}.
fi

final_length=$(($(length $entier) + $2 + 1))

if [[ $(length $nombre) -lt $final_length ]]
then

   while [[ $(length $nombre) -lt $final_length ]]
   do
       nombre=${nombre}0
   done

elif [[ $(length $nombre) -gt $final_length ]]
    then
        rafraichir=$((`length $decimal` - $2))

        for i in $(seq $rafraichir)
        do

            if [[ $(str-from-index $decimal `length $decimal`) -gt 4 ]]
            then
                newlast=$(char-at-index $decimal $((`length $decimal` - 1)))
                if [[ $newlast -eq 10 ]]
                then
                    reste=1
                else
                    newlast=$(($newlast + 1))
                    reste=0
                fi
                decimal=$(str-till-index $decimal $((`length $decimal` - 2)))$newlast
            else
                decimal=$(str-till-index $decimal $((`length $decimal` - 1 )))
            fi
        done
        nombre=${entier}.${decimal}
fi

echo $nombre
exit 0