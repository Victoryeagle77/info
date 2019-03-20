/*
Question 3 : Écrivez une application qui ouvre une fenetre contenant un champ de texte le long du bord inférieur, et une zone de texte occupant le reste de l'espace. 
La zone contiendra du texte vert sur fond noir, et le champ du texte vert sur fond gris.

La classe Color sert à représenter une couleur. 
Son constructeur réclame trois entiers compris entre 0 et 255 qui donnent respectivement la quantité de rouge, de vert et de bleu qui la composent. 
Un objet de cette classe peut ensuite servir d'argument à la méthode setForeground ou à la méthode setBackground qui sont définies aussi bien dans JTextArea que dans JTextField. 
On souhaite que les lignes trop longues se poursuivent automatiquement sur la ligne suivante. 
La classe JTextArea possède une méthode setLineWrap qui prend un booléen en argument et qui contrôle ce comportement. 
*/

import javax.swing.*;
import java.awt.*;

public class Contingence {

	public static void main(String[] args) {
		JFrame fenetre = new JFrame();

		fenetre.setSize(500,300);
		fenetre.setLocation(100,100);
		fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		JTextArea area = new JTextArea("--> TIERS MONDE TERMINAL <--\n");
		area.setForeground(new Color(0,200,0));
		area.setBackground(new Color(0,0,0));
		area.setLineWrap(true);
		
		JScrollPane elevator = new JScrollPane(area);
		elevator.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);

		JTextField field = new JTextField("");
		field.setBackground(new Color(200,200,200));
		field.setForeground(new Color(1,155,1));

		fenetre.add(field,BorderLayout.SOUTH);
		fenetre.add(area,BorderLayout.CENTER);
		fenetre.add(elevator,BorderLayout.EAST);

		fenetre.setVisible(true);
	}
}