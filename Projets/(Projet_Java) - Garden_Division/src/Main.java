package src;
import javax.swing.UIManager;
import javax.swing.plaf.nimbus.NimbusLookAndFeel;

/**
* La classe <code>Main</code> permet de lancer la classe
* <code>View</code>
*/
public class Main{
  public static void main(String[] args) throws Exception{
  	/* NimbusLookAndFeel permet un meilleur aspect visuel de l'interface graphique. */
    UIManager.setLookAndFeel(new NimbusLookAndFeel());
    new View().setVisible(true);
  }
}