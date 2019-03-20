import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Action implements ActionListener {
	private JPanel panneau;

	public Action(JPanel pan) {
		super();
		this.panneau=pan;
	}

	public void actionPerformed(ActionEvent evenement) {
		String composant = evenement.getActionCommand();
		if (composant.equals("Cyan"))
			this.panneau.setBackground(new Color(0,255,200));
		else if (composant.equals("Magenta"))
			this.panneau.setBackground(new Color(255,0,255));
		else if (composant.equals("Jaune"))
			this.panneau.setBackground(new Color(255,255,0));
	}
}