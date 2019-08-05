import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;

public class Activation implements WindowListener {
  public JFrame fenetre;
  public JPanel data;

  public Activation(JFrame fenetre, JPanel data) {
    this.fenetre = fenetre;
    this.data = data;
  }

  public void windowActivated(WindowEvent evenement) {/* premier plan */}
  public void windowClosed(WindowEvent evenement) {/* après fermeture */}    
  public void windowClosing(WindowEvent evenement) {
    try {
      /* Ecriture sur la sortie standard dans le fichier */
      FileOutputStream fichier = new FileOutputStream("./data/save.dat");
      DataOutputStream flux = new DataOutputStream(fichier);
      /* Ecriture dans le fichier "save.dat" les données suviantes */
      flux.writeInt(this.fenetre.getX()); /* Coordonnée par rapport à l'écran en abscisse */
      flux.writeInt(this.fenetre.getY()); /* Coordonnée par rapport à l'écran en ordonnée */
      flux.writeInt(this.fenetre.getWidth()); /* Largeur de la fenêtre */
      flux.writeInt(this.fenetre.getHeight()); /* Hauteur de la fenêtre */
      /* Retient la coloration rgb déterminer par les boutons */
      flux.writeInt(this.data.getBackground().getRed()); 
      flux.writeInt(this.data.getBackground().getGreen());
      flux.writeInt(this.data.getBackground().getBlue());
      /* Fermeture du flux de donné */
      flux.close();
    } catch (FileNotFoundException e) {
      System.err.println("Erreur de sauvegarde" + e.getMessage());
    } catch (IOException e) {
      System.err.println("Erreur de sauvegarde" + e.getMessage());
    }
  }
	
  /* Avant fermeture */
  public void windowDeactivated(WindowEvent evenement){/* arrière-plan */}
  public void windowDeiconified(WindowEvent evenement){/* restauration */}
  public void windowIconified(WindowEvent evenement){/* réduction de la fenêtre */}   
  public void windowOpened(WindowEvent evenement){/* après ouverture */}    
}