/*
Question 2 : Boutons. 
Écrivez un programme qui ouvre une fenêtre contenant cinq boutons. 
Testez ce programme et observez ce qui se passe quand on redimensionne la fenêtre. 
Choisissez ensuite un texte très long (20 caractères environ) pour l'un des boutons. 
Comment la disposition en est-elle affectée ? Faites le test avec chaque bouton successivement. 
*/

import javax.swing.*;
import java.awt.*;

public class Boutons {

  public static void main(String[] args) {
    JFrame fenetre = new JFrame();

    fenetre.setSize(300,200);
    fenetre.setLocation(100,100);
    fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

    JButton bouton1 = new JButton("Bouton 1");
    JButton bouton2 = new JButton("Bouton 2");
    JButton bouton3 = new JButton("Bouton 3");
    JButton bouton4 = new JButton("Bouton 4");
    JButton bouton5 = new JButton("Bouton 5");

    fenetre.add(bouton1,BorderLayout.CENTER);
    fenetre.add(bouton2,BorderLayout.NORTH);
    fenetre.add(bouton3,BorderLayout.EAST);
    fenetre.add(bouton4,BorderLayout.WEST);
    fenetre.add(bouton5,BorderLayout.SOUTH);

    fenetre.setVisible(true);
  }
}