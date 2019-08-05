/*
Question 5 : Cercles 
Écrivez une application qui ouvre une fenêtre contenenant des cercles,
dont la couleur effectue un dégradé de couleur du vert au bleu.
*/

import javax.swing.JFrame;

public class Main {
  public static void main(String[] args) {
    JFrame fenetre = new JFrame();
    fenetre.setSize(260,290);
    fenetre.setLocation(0,0);
    fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    fenetre.setContentPane(new Cercles());
    fenetre.setVisible(true);
  }
}