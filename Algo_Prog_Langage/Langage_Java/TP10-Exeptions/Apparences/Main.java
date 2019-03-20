import javax.swing.*;
import java.awt.*;
import java.lang.*;

public class Main {
	public static void main(String[] args) {
		
		try {
			UIManager.setLookAndFeel("toto");
		} catch (InstantiationException e) {
			System.err.println("InstantiationException !");
		} catch (ClassNotFoundException e) {
			System.err.println("ClassNotFoundException !");
		} catch (IllegalAccessException e) {
			System.err.println("IllegalAccessException !");
		} catch (UnsupportedLookAndFeelException e) {
			System.err.println("UnsupportedLookAndFeelException !");
		} catch (ClassCastException e) {
			System.err.println("ClassCastException !");
		}

		JFrame fenetre = new JFrame("Fond");
		fenetre.setLocation(100,100);
		fenetre.setSize(200,200);
		fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		JPanel entier = new JPanel();
		Action observateur = new Action(entier);

		JPanel panneau = new JPanel();
		JButton cyan = new JButton("Cyan");
		JButton jaune = new JButton("Jaune");
		JButton magenta = new JButton("Magenta");

		cyan.addActionListener(observateur);
		jaune.addActionListener(observateur);
		magenta.addActionListener(observateur);

		panneau.setLayout(new GridLayout(3,1));

		panneau.add(cyan);
		panneau.add(jaune);
		panneau.add(magenta);

		entier.add(panneau);

		fenetre.add(entier,BorderLayout.CENTER);

		fenetre.setVisible(true);
	}
}