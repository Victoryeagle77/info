/* 
Question 4 : Piège
Écrivez une application qui ouvre une fenêtre ayant l'apparence suivante : 

-----------------------
|		1		 |    |
------------------    |
|	|			 |	  |
|	|			 |	  |
|	|	   5	 | 2  |
| 4	|			 |	  |
|	|			 |	  |
|	|			 |    |
|	-------------------
|	|	    3		  |
-----------------------

Cet exercice est un piège ! Les gestionnaires de mise en page que nous avons vu ne permettent pas de réaliser une telle configuration, 
même en combinaison. Il est possible dans ce cas de poser les composants «manuellement». On désactive d'abord le gestionnaire actuel avec :

fenetre.setLayout(null);

Puis on peut décider de la position et de la taille d'un composant en utilisant 
ses méthodes setLocation et setSize (comme pour une fenêtre).

! Remarque !
Cette façon de faire est rarement employée car la mise en page n'est plus dynamique : 
en cas de redimensionnement, les composants ne s'adaptent pas. 
*/

import javax.swing.*;
import java.awt.*;

public class Piege {
	public static void main(String[] args) {
	    JFrame fenetre = new JFrame();
	    fenetre.setSize(400, 430);
	    fenetre.setLocation(0, 0);
	    fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	    // Empêche une action après l'activation d'un bouton
	    fenetre.setLayout(null);
		// Bouton en haut à gauche
		JButton button1 = new JButton("1");
		button1.setLocation(0, 0);
		button1.setSize(300, 100);
		fenetre.add(button1);
		// Bouton en haut et au milieu à droite
		JButton button2 = new JButton("2");
		button2.setLocation(300, 0);
		button2.setSize(100, 300);
		fenetre.add(button2);
		// Bouton en bas à droite
		JButton button3 = new JButton("3");
		button3.setLocation(100, 300);
		button3.setSize(300, 100);
		fenetre.add(button3);
		// Bouton en bas et au milieu à gauche
		JButton button4 = new JButton("4");
		button4.setLocation(0, 100);
		button4.setSize(100, 300);
		fenetre.add(button4);
		// Bouton au milieu
		JButton button5 = new JButton("5");
		button5.setLocation(100, 100);
		button5.setSize(200, 200);
		fenetre.add(button5);
		
		fenetre.setVisible(true);
	}
}