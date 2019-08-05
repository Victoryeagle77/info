/*
Question 2 : Question 
Écrivez une application qui ouvre une fenêtre ayant une question afffichée
La question et les réponses devront rester au centre de la fenêtre en cas de redimensionnement. 
*/

import javax.swing.*;
import java.awt.*;
import java.util.*;

public class Question {
  public static void main(String[] args) {
    JFrame fenetre = new JFrame("Question");
    fenetre.setSize(500,300);
    fenetre.setLocation(100,100);
    fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    fenetre.setMinimumSize(new Dimension(500,100));

    GridLayout grille = new GridLayout(2,1);
    fenetre.setLayout(grille);

    JLabel zoneDeTexte = new JLabel("Aimez vous le SQL ?");
    zoneDeTexte.setHorizontalAlignment(JLabel.CENTER);
    zoneDeTexte.setVerticalAlignment(JLabel.BOTTOM);
    fenetre.add(zoneDeTexte, BorderLayout.CENTER);

    JPanel panneau = new JPanel();
    JButton bouton = new JButton("Oui");
    panneau.add(bouton);
    JButton bouton2 = new JButton("Non");
    panneau.add(bouton2);
    JButton bouton3 = new JButton("NSPP");
    panneau.add(bouton3);
    fenetre.add(panneau,BorderLayout.NORTH);

    fenetre.setBackground(Color.WHITE);
    fenetre.setVisible(true);
  }
}