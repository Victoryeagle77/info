import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Commande implements ActionListener{
	private JPanel panel;

	public Commande(JPanel p){
      this.panel=p;
      panel.setBackground(Color.YELLOW);
	}
	
	public void actionPerformed(ActionEvent e){
		String temp = e.getActionCommand();
		if(temp.equals("")){
			Calcul calc = new Calcul();
		}else if(temp.equals("")){
			Calcul calc = new Calcul();
		}
	}
}




