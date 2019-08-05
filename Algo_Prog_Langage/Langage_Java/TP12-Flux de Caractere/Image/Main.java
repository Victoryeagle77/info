/*
Question 2 : Image. 
Le fichier image.xpm représente une image dans un format standard (mais inusité).

Écrivez une application qui lit ce fichier puis ouvre une fenêtre de la taille adéquate,
dans laquelle apparaît l'image correspondante.

! Remarque ! 
Pour isoler les données contenues dans le fichier, 
vous aurez sans doute besoin des méthodes charAt, split et substring de la classe String.

*/

public class Main {
  public static void main(String[] args) {
    Fenetre fenetre = new Fenetre();
    fenetre.setVisible(true);
  }
}