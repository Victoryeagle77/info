/*
Question 1 : Image. 
Le fichier image.bin représente une image de 768 pixels de large par 1024 pixels de haut, 
dans un format non standard. 
Chaque pixel de cette image est décrit par trois octets successifs : rouge, vert puis bleu. 
Les pixels sont décrits les uns à la suite des autres, de gauche à droite puis de haut en bas.

Écrivez une application qui lit ce fichier puis ouvre une fenêtre de la taille adéquate,
dans laquelle apparaît l'image correspondante.

Remarque La méthode getImage vue précédemment n'est pas compatible avec le format employé ici ; 
vous devrez donc inventer votre propre méthode pour la remplacer. 
Le stockage de l'image dans l'application peut prendre la forme d'un objet de la classe BufferedImage 
(une classe dérivée de Image). 
*/

public class Main {
  public static void main(String[] args) {
    Fenetre fenetre = new Fenetre("Image");
    fenetre.setVisible(true);
  }
}