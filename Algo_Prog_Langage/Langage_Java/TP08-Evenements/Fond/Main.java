/* Question 1 : Fond. 
Écrivez une application qui ouvre une fenêtre contenant trois boutons marqués «Cyan», «Magenta» et «Jaune».
Appuyer sur l'un de ces boutons devra changer la couleur de fond en la couleur indiquée.

! Remarque ! La méthode setBackground n'a pas d'effet visible sur une fenêtre, 
donc vous devrez utiliser un panneau pour contrôler la couleur de fond.
*/

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;


public class Main {
public static void main(String[] args) {

	JFrame fenetre = new JFrame();
	fenetre.setSize(200, 200);
       	fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

       	JButton cyan = new JButton("Cyan");
	JButton magenta = new JButton("magenta");
       	JButton jaune = new JButton("jaune");

       	JPanel panel = new JPanel();	
       	Fond ctrl = new Fond(panel);

       	panel.add(cyan);
       	panel.add(magenta);
       	panel.add(jaune);

       	fenetre.add(panel, BorderLayout.CENTER);
       	cyan.addActionListener(ctrl);
       	magenta.addActionListener(ctrl);
       	jaune.addActionListener(ctrl);

       	fenetre.setVisible(true);
	}
}
