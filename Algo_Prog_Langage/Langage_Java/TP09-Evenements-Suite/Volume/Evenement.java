import java.awt.event.*;

public class Evenement implements MouseWheelListener {
	/* Implémantation des fonctions d'actions de la souris */
	private Forme roleur;

	public Evenement(Forme roleur){
		this.roleur=roleur;
	}
    /* Mouvement de molette */
	public void mouseWheelMoved(MouseWheelEvent evenement){
		if (evenement.getWheelRotation() < 0)
			roleur.ajout();
		else { roleur.deletion(); }
		roleur.repaint();
	}
}