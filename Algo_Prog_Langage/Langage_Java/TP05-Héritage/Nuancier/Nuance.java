import javax.swing.*;
import java.awt.*;

public class Nuance extends JFrame {

  public static JPanel Palette(String color) {
    int rouge, vert, bleu;
    JPanel nuance = new JPanel();
	
    GridLayout gestionnaire = new GridLayout(2,1);
    nuance.setLayout(gestionnaire);

    /* Conversion en entier de base 16 */
    rouge = Integer.parseInt(color.substring(1, 3), 16);
    vert = Integer.parseInt(color.substring(3, 5), 16);
    bleu = Integer.parseInt(color.substring(5, 7), 16);
    
    String rgb = rouge + "," + vert + "," + bleu;
    JPanel fond = new JPanel();
    fond.setBackground(Color.BLACK);
		
    JLabel head = new JLabel(rgb);
    head.setHorizontalAlignment(JLabel.CENTER);
    head.setForeground(Color.WHITE);
		
    fond.add(head);
    nuance.add(fond);
		
    JPanel couleur = new JPanel();
    couleur.setBackground(new Color(rouge, vert, bleu));
    nuance.add(couleur);
    return nuance;
  }
}