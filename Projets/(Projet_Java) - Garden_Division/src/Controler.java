package src;
import api_jardin.Parcelle;
import api_jardin.Orientation;
import java.awt.event.*;
import javax.swing.*;
import java.awt.*;

/**
* @author Arthur Chenu
* @author Julien Carcau
* @version final
*/

/**
* La classe <code>Controler</code> permet de d&eaucte;t&eaucte;rminer des &eaucte;v&eaucte;nements,
* liant une action faite sur une parcelle &agrave; chaque bouton cliqu&eacute;.
*/
public class Controler implements ActionListener {
	private JPanel terrain;
	private Parcelle parcelle;

	public Controler(Parcelle parcelle, JPanel terrain){
		this.parcelle = parcelle;
		this.terrain = terrain;
	}

	public void actionPerformed(ActionEvent e){
		/* Relevé de l'activation d'un bouton */
		JButton bouton = (JButton)e.getSource();
		/* Définition de la parcelle mère */
		JPanel mere = (JPanel)bouton.getParent().getParent();
		/* Définition de la parcelle fille */
		JPanel fille = (JPanel)bouton.getParent();

		JTabbedPane niveau = new JTabbedPane();

		mere.remove(fille);
		mere.add(terrain);

		/* Voir en détail une parcelle */
		if(e.getActionCommand().equals("D\u00e9tail")){
			/* Détail d'un niveau de parcelle */
			niveau.add("D\u00e9tail niveau", terrain);
			((Parcelage)mere.getParent()).add(niveau);
		/* Supprimer une parcelle */
		}else if(e.getActionCommand().equals("X")){
			parcelle.reset();
			mere.add(terrain);
			mere.remove(fille);
			((Parcelage)mere.getParent()).active();
		/* Planter des cultures */
		}else if(e.getActionCommand().equals("Planter"))
			((Parcelage)mere.getParent()).planter(); 
        
        /* Division horizontal */
		if(e.getActionCommand().equals("Horizontal")){
			parcelle.SplitParcelle(Orientation.HORIZONTAL);
			/* Création de sous parcelle */
			((Parcelage)mere.getParent()).active();
		/* Division vertical */
		}else if(e.getActionCommand().equals("Vertical")){
			parcelle.SplitParcelle(Orientation.VERTICAL);
			/* Création de sous parcelle */
			((Parcelage)mere.getParent()).active();
		}
		mere.revalidate();
	}
}