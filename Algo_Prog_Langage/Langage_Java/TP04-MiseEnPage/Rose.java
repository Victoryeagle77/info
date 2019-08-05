/*
Question 4 : Rose. 
Écrivez une application qui ouvre une fenêtre ayant l'apparence suivante : 

-----------------------------
|Mystral   Tramontane   Grec|
|                           |
|                           |
|                           |
|                           |
|Ponant               Levant|
|                           |
|                           |
|                           |
|Libeccio    Marin   Sirocco|
-----------------------------
*/

import javax.swing.*;
import java.awt.*;

public class Rose{
  public static void main(String[] args) {
    GridLayout grille = new GridLayout(3, 3);
    JFrame fenetre = new JFrame();
    fenetre.setSize(300, 300);
    fenetre.setLocation(1500,100);
    fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    fenetre.setLayout(grille);
        
    JLabel mystral = new JLabel("Mystral");
    fenetre.add(mystral);
    mystral.setVerticalAlignment(JLabel.NORTH);

    JLabel tramontane = new JLabel("Tramontane");
    fenetre.add(tramontane);
    tramontane.setVerticalAlignment(JLabel.NORTH);
    tramontane.setHorizontalAlignment(JLabel.CENTER);

    JLabel grec = new JLabel("Grec");
    fenetre.add(grec);
    grec.setVerticalAlignment(JLabel.NORTH);
    grec.setHorizontalAlignment(JLabel.RIGHT);

    JLabel ponant = new JLabel("Ponant");
    fenetre.add(ponant);

    JLabel vide = new JLabel("");
    fenetre.add(vide);
    vide.setHorizontalAlignment(JLabel.CENTER);

    JLabel levant = new JLabel("Levant");
    fenetre.add(levant);
    levant.setHorizontalAlignment(JLabel.RIGHT);

    JLabel libeccio = new JLabel("Libeccio");
    fenetre.add(libeccio);
    libeccio.setVerticalAlignment(JLabel.BOTTOM);

    JLabel marin = new JLabel("Marin");
    fenetre.add(marin);
    marin.setVerticalAlignment(JLabel.BOTTOM);
    marin.setHorizontalAlignment(JLabel.CENTER);

    JLabel sirocco = new JLabel("Sirocco");
    fenetre.add(sirocco);
    sirocco.setVerticalAlignment(JLabel.BOTTOM);
    sirocco.setHorizontalAlignment(JLabel.RIGHT);

    fenetre.setVisible(true);
  }
}