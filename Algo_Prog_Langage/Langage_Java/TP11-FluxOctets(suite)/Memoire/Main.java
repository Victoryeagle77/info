/* Question 3 : Mémoire

Faite un programme qui ouvre une fenêtre avec des boutons changeant la couleur de fond,
et faites en sorte qu'à chaque démarrage de l'application,
la fenêtre reprenne la position et les dimensions qu'elle possédait à la fin de l'exécution précédente. 
Faites en sorte que l'application mémorise également la couleur de fond choisie.

! Remarque !
On souhaite ici stocker dans un fichier à la fois une position (un objet de la classe Point), 
une taille (un objet de la classe Dimension), et une couleur (un objet de la classe Color).
*/

public class Main {
  public static void main(String[] args) {
    Fenetre fenetre = new Fenetre();
    fenetre.setVisible(true);
  }
}