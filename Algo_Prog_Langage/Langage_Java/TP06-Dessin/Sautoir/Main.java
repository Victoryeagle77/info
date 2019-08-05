/* Question 2 : Sautoir.
Écrivez une application qui ouvre une fenêtre ayant l'apparence d'un damier,
avec des losanges à la place de carré : */

import javax.swing.JFrame;

public class Main {
  public static void main(String[] args) {
    JFrame fenetre = new JFrame();
    fenetre.setSize(500,430);
    fenetre.setLocation(0,0);
    fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    fenetre.setContentPane(new Sautoir());
    fenetre.setVisible(true);
  }
}