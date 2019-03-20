# Question 1 : mult_mat.sh #

# On écrit le script mult_mat.sh qui utilise deux arguments numériques entiers positifs
# ARG1, ARG2. Il affiche sous forme de matrice la table de multiplication de
# {ARG1, ARG1+1,...,ARG2} par {ARG1, ARG1+1,...,ARG2} :

# $ ./mult_mat.sh 7
# Usage: ./mult_mat.sh <NUM_ARG1> <NUM_ARG1>
# $ ./mult_mat.sh 7 11
# 49   56   63   70    77
# 56   64   72   80    88
# 63   72   81   90    99
# 70   80   90   100  110
# 77   88   99   110  121

#!/bin/bash

clear

if [[ $# -ne 2 ]]
then
    echo "Usage : $0 <unsigned int> <unsigned int>"
    exit 1;
fi

for (( i=$1; i<=$2; i++ ))
do
    for (( j=$1; j<=$2; j++ ))
    do
        printf "%6d" $((i*j))
    done
    echo
done

exit 0