/*
Question 2 : Grisaille. 
Définissez une classe Gris qui dérive de la classe Color mais ne permet de créer que des gris 
(c'est à dire des couleurs où les trois composantes sont égales). 
Pouvez-vous utiliser un objet de la classe Gris avec la méthode setBackground pour choisir 
la couleur de fond d'un composant ? 
*/

import javax.swing.*;
import java.awt.*;

public class Main {
  public static void main(String[] args) {
    if (args.length != 1){ 
      System.err.println("Usage : <int>");
      return; 
    }
        
    JPanel panneau = new JPanel();
    JFrame fenetre = new JFrame();

    fenetre.setSize(200, 200);
    fenetre.setLocation(100, 100);
    fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

    panneau.setBackground(new Gris(Integer.parseInt(args[0])));    	
		
    fenetre.add(panneau);
    fenetre.setVisible(true);
  }
}