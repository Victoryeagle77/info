import javax.swing.*;
import java.awt.*;

public class Nuance extends JFrame {

	public static JPanel Palette(String color) {
		String rouge, vert, bleu;
		int red, green, blue;
		JPanel nuance = new JPanel();
		GridLayout gestionnaire = new GridLayout(2,1);
		nuance.setLayout(gestionnaire);

		rouge = color.substring(1,3);
		vert = color.substring(3,5);
		bleu = color.substring(5,7);
		// Conversion en entier de base 16
		red = Integer.parseInt(rouge,16);
		green = Integer.parseInt(vert,16);
		blue = Integer.parseInt(bleu,16);
		
		String rgb = red + "," + green + "," + blue;
		JPanel fond = new JPanel();
		fond.setBackground(Color.BLACK);
		
		JLabel head = new JLabel(rgb);
		head.setHorizontalAlignment(JLabel.CENTER);
		head.setForeground(Color.WHITE);
		
		fond.add(head);
		nuance.add(fond);
		
		JPanel couleur = new JPanel();
		couleur.setBackground(new Color(red,green,blue));
		nuance.add(couleur);
		return nuance;
	}
}