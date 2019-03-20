/*
Question 5 : Commande. 
Créer une fenêtre contenant un unique champ de texte.
Si l'utilisateur tape dans ce champ de texte «Cyan», «Magenta» ou «Jaune» puis valide, 
la couleur de fond doit changer conformément. Quelque soit le texte entré, en validant on doit vider le champ de texte. 
*/

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Main {
	public static void main(String[] args) {

		JFrame fenetre = new JFrame();
		fenetre.setSize(200, 200);
		fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		JTextField couleur = new JTextField(15);
		JPanel panneau = new JPanel();	
		Commande commande = new Commande(panneau);

		panneau.add(couleur);
		fenetre.add(panneau, BorderLayout.CENTER);
		couleur.addActionListener(commande);

		fenetre.setVisible(true);
	}
}