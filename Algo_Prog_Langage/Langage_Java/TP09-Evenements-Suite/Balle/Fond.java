import javax.swing.*;
import java.awt.*;

public class Fond extends JComponent {
	Image balle, terre;
	int x, y;

	public Fond() {
		super();
		this.balle = Toolkit.getDefaultToolkit().getImage("image/balle.png");
		this.terre = Toolkit.getDefaultToolkit().getImage("image/terre.jpg");
		this.x = 150;
		this.y = 300;
	}

	public void paintComponent(Graphics pinceau) {
		Graphics secondPinceau = pinceau.create();
		secondPinceau.drawImage(this.terre, 0, 0, this);
		secondPinceau.drawImage(this.balle, this.x, this.y, this);
	}

	public int etat_x() { return this.x; }

	public int etat_y() { return this.y; }

	public void bouger(int a, int b) {
		this.x = a-17;
		this.y = b-17;
		// Repeindre en remplaçant les coordonnées
		this.repaint();
	}
}