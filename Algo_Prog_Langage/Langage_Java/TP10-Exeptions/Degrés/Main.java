import javax.swing.*;
import java.awt.*;
import java.awt.event.*;


public class Main {
public static void main(String[] args) {

		JFrame fenetre = new JFrame();
		fenetre.setSize(300, 300);
		fenetre.setLocation(0, 0);
		fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		JTextField C = new JTextField(15);
		JTextField F = new JTextField(15);
		JPanel panel = new JPanel();
		
		Commande ctrl = new Commande(panel);
		panel.add(C);
		panel.add(F);
		fenetre.add(panel, BorderLayout.CENTER);
		C.addActionListener(ctrl);
		F.addActionListener(ctrl);

		fenetre.setVisible(true);
	}
}