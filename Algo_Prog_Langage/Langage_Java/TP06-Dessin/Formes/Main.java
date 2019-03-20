/*
Question 1 : Formes. 
Écrivez une application qui ouvre une fenêtre contenant :

   ° un carré bordé de bleu de 50 pixels de côté,
   ° un disque entièrement vert de 25 pixels de rayon,
   ° le texte >o< dessiné en corps 24 gras et en violet.
   ° l'image cercle.png
*/

import javax.swing.*;
import java.awt.*;

public class Main {
	public static void main(String[] args) {
	    JFrame fenetre = new JFrame();
	    fenetre.setSize(235,150);
	    fenetre.setLocation(0,0);
	    fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	    fenetre.setMinimumSize(new Dimension(235,150));
	    fenetre.setContentPane(new Formes());
	    fenetre.setVisible(true);
	}
}