# Question 8 : networking.sh #

# Ecrire un script qui prend en argument un nom/ip de machine, et qui affiche les noeuds traversés.
# La commande ping, et les options -c, -t, -W. Un exemple de la sortie attendue :

# ./trace.sh www.archlinux.org
# 1 : gatekeeper.arda (172.16.1.254)
# 2 : 37.58.131.238 (37.58.131.238)
# 3 : 100.65.0.27 (100.65.0.27)
# 4 : c4-stg.e6-stg.backbone.adista.fr (128.127.131.113)
# 5 : c4-stg.e6-stg.backbone.adista.fr (128.127.131.113)
# 6 : decix-gw.hetzner.de (80.81.192.164)
# 7 : core24.fsn1.hetzner.com (213.239.252.42)
# 8 : ex9k2.dc8.fsn1.hetzner.com (213.239.229.22)
# 9 : apollo.archlinux.org (138.201.81.199)

#!/bin/bash

clear

if [[ $# != 1 ]]; 
then
     echo '<lien url>'
     exit 1
fi

# retourne "no reply" s'il y a un problème dans les pipes de nb_noeud
set -o pipefail

i=0
noeud=1
while [[ $noeud != 0 ]]
do
   i=$((i + 1))
   # Effectue un ping et élimine avec egrep et sed,
   # les informations qu'on ne souhaite pas garder.
   nb_noeud=$(ping -c 1 -W 1 -t $i $1 \
       | egrep '[Ff]rom' \
       | sed -E 's/^.*[Ff]rom ([^\)]+\)).*$/'$i' : \1/' )
   noeud=$?
   # Si le nombre de noeud est valide par rapport au ping, on continue 
   if [[ ! -z $nb_noeud ]]
   then
       echo $nb_noeud
   else # On quitte dans le cas contraire
       echo "$i : no reply"
   fi
done

set +o pipefail
