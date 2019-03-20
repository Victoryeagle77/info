import javax.swing.*;
import java.awt.*;

public class Fenetre extends JFrame {
	public Fenetre() {
		super("Balle");
		this.setLocation(100, 100);
		this.setSize(380, 580);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		Fond fond = new Fond();
		Actions action = new Actions(fond);
		
		fond.addMouseMotionListener(action);
		fond.addMouseListener(action);
		this.add(fond);
	}
}