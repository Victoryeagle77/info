#!/bin/bash

# Conditionnement pour qu'il y est au moins deux arguments
if [[ $# != 2 ]]; 
    then
    echo "/!\ Usage : $0 <dossier> <fichier.html>"
    exit -1
fi # Fin de la condition

chemin=$1 # Premier argument après l'exécutable
fichier=$2 # Deuxième argument après l'exécutable

courrant=`pwd` # Répertoire courrant
cd $chemin # Aller dans le dossier voulu à partir du chemin actuel

noms=`ls -a --quote-name` # Recherche par nom les fichier
objets=`find -maxdepth 1 | wc -l` # Compte le nombre d'éléments en cherchant en profondeur dans le répertoire courant.

count=0
for i in $(seq 0 $objets); do
    count=$(($count+2))
    nom[$i]=`echo $noms | awk -F "\"" -v count=$count '{print $count}'`
    droits[$i]=`stat --format %A "${nom[$i]}"` # Affichage des droits de format drwxrwxrwx.
    tailles[$i]=`stat --format %s "${nom[$i]}"` # Affihage de la taille en octets.
done

cd $courrant # Ce rendre dans le répertoire courant.

# Contenu html à partir des informations dans le répertoire courrant.
echo "<!DOCTYPE html>" > $fichier
echo "<html lang="FR">" >> $fichier
  echo "<head>" >> $fichier
    echo '<meta charset=UTF-8"/>' >> $fichier
    echo "<title>Elements d'un dossier</title>" >> $fichier
  echo "</head>" >> $fichier
  echo "<body>" >> $fichier
    echo "<h1>Contenu du dossier $chemin</h1>" >> $fichier
    echo "<table>" >> $fichier
    echo "<tr>" >> $fichier
    echo "<th>Nom </th>" >> $fichier
    echo "<th>Droits</th>" >> $fichier
    echo "<th>Taille</th>" >> $fichier
    echo "</tr>" >> $fichier
        
        # Instruction de remplacement dans le html par le shell.
        for i in $(seq 0 $objets); do
            echo "<tr>" >> $fichier
            repertoire=`echo ${droits[$i]} | head -c 1`
            if [[ $repertoire == 'd' ]]; 
            then # S'il s'agit d'un dossier
                echo "<td> <img src="./images/folders.png"> <a href="$chemin">${nom[$i]}</a> </td>" >> $fichier
            else # S'il s'agit d'un fichier
                echo "<td> <img src="./images/files.png"> <a href="$chemin">${nom[$i]}</a> </td>" >> $fichier
            fi
            echo "<td> ${droits[$i]} </td>" >> $fichier
            echo "<td> ${tailles[$i]} </td>" >> $fichier
            echo "</tr>" >> $fichier
        done
        # Fin de la boucle d'instrcution de remplacement.
        
    echo "</table>" >> $fichier
  echo "</body>" >> $fichier
echo "</html>" >> $fichier

# Redirection vers firefox.
firefox $fichier