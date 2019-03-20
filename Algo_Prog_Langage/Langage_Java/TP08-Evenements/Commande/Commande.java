import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Commande implements ActionListener{
	private JPanel panel;

	public Commande(JPanel p){ this.panel = p; }
	
	public void actionPerformed(ActionEvent e){
		String couleur = e.getActionCommand();
		if(couleur.equals("Cyan"))
			panel.setBackground(Color.CYAN);
		else if(couleur.equals("Magenta"))
			panel.setBackground(Color.MAGENTA);
		else if(couleur.equals("Jaune"))
			panel.setBackground(Color.YELLOW);
	}
	
}