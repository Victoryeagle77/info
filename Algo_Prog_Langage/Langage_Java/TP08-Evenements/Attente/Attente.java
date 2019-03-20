import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Attente extends JFrame implements WindowListener{
public Panneau panneau;
  public Attente(){
        super();
        this.panneau = new Panneau();
        this.add(panneau);
        this.addWindowListener(this);  
        setSize(400,350);  
        setVisible(true);  
  }
  /* Fonctions de la libraire "WindowsEvent" */
  public void windowActivated(WindowEvent evenement){
      this.panneau.cercle(this.getGraphics()); // premier plan
  }
  public void windowClosed(WindowEvent evenement){/* Après fermeture */ }
  public void windowClosing(WindowEvent evenement){/* Avant fermeture */}
  public void windowDeactivated(WindowEvent evenement){/* Arrière plan */} 
  public void windowDeiconified(WindowEvent evenement){/* Rafraichi */}
  public void windowIconified(WindowEvent evenement){/* Minimalise la fenêtre */}
  public void windowOpened(WindowEvent evenement){/* Lors de l'ouverture */}       
}	
