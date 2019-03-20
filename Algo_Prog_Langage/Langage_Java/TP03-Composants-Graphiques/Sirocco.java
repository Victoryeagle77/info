/* 
Question 1 : Sirocco. 
En vous inspirant de l'exemple donné, écrivez un programme qui ouvre une fenêtre de 500 pixels de large, 300 pixels de haut, collée dans le coin supérieur gauche de l'écran. 
Cette fenêtre devra contenir le texte «Sirocco» dans son coin inférieur droit. 
*/

import javax.swing.*;
import java.awt.*;

public class Sirocco {
  public static void main(String[] args) {
    JFrame fenetre = new JFrame();
    fenetre.setSize(500, 300);
    fenetre.setLocation(0, 0);
    fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    JLabel etiquette = new JLabel("Sirocco");
    etiquette.setHorizontalAlignment(JLabel.RIGHT);
    fenetre.add(etiquette, BorderLayout.SOUTH);
    fenetre.setVisible(true);
  }
}
