import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Fond implements ActionListener{
	private JPanel panneau;

	public Fond(JPanel panel){ this.panneau=panel; }
	
	public void actionPerformed(ActionEvent e){
		String nomButton = e.getActionCommand();

		if(nomButton.equals("Cyan"))
			panneau.setBackground(Color.CYAN);
		else if(nomButton.equals("Magenta"))
			panneau.setBackground(Color.MAGENTA);
		else if(nomButton.equals("Jaune"))
			panneau.setBackground(Color.YELLOW);
	}	
}




