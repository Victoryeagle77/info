import javax.swing.JComponent;
import java.awt.*;

public class Forme extends JComponent{
	// Compteur de cercle coloriés 
	private int compte;
    // 7 cercles seront coloriés en jaune (initialisés)
	public Forme(){ this.compte=7; }
    // Redéfinition basique
	@Override
	public void paintComponent(Graphics pinceau) {
		Graphics secondPinceau = pinceau.create();
		int disques = 20;
		if (this.isOpaque()) {
			// on repeint toute la surface avec la couleur de fond
			secondPinceau.setColor(this.getBackground());
			secondPinceau.fillRect(0, 0, this.getWidth(), this.getHeight());
		}
		secondPinceau.setColor(new Color(100,100,100));
		secondPinceau.fillRect(0, 0, this.getWidth(), this.getHeight());
		for (int i = 0 ; i < 10 ; i++) {
			/* 10 cercles alignés */
			secondPinceau.setColor(new Color(200,200,200));
			if (i<compte)
				secondPinceau.setColor(Color.YELLOW);

			secondPinceau.fillOval(disques + i * (this.getHeight()-40) + i* 20,
			 20, this.getHeight()-40, this.getHeight()-40);
		
		}
		
	}

	public void ajout(){
		if (compte < 10) { compte++; }
	}
	public void deletion(){
		if (compte > 0) { compte--; }
	}
}