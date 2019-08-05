/*
Question 4 : Homothétie
Le fichier polygone.bin contient la liste des points formant un polygone. 
Pour chaque point, un int décrit d'abord l'abcisse, puis un autre int décrit l'ordonnée.

Écrivez une application qui affiche ce polygone dans une fenêtre à l'aide de la méthode fillPolygon.

Le polygone est cependant un peu petit. 
Écrivez une application qui lit un fichier au format décrit plus haut et génère un nouveau fichier,
décrivant un polygone deux fois plus grand.
*/

public class Main {
  public static void main(String[] args) {
    Fenetre fenetre = new Fenetre();
    fenetre.setVisible(true);
  }
}