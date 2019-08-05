import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Fond implements ActionListener{
	private JPanel panneau;

	public Fond(JPanel panel){ this.panneau=panel; }
	
	public void actionPerformed(ActionEvent e){
		String bouton = e.getActionCommand();

		if(nomButton.equals("Cyan"))
			panneau.setBackground(Color.CYAN);
		else if(bouton.equals("Magenta"))
			panneau.setBackground(Color.MAGENTA);
		else if(bouton.equals("Jaune"))
			panneau.setBackground(Color.YELLOW);
	}	
}