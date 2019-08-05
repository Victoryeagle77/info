import java.awt.event.*;

/**
* @author Arthur Chenu
* @version final
*/

/**
* La classe <code>Controller</code>
* permet en utilisant les méthodess de la classe KeyEvent la d&eacute;t&eacute;ction des touches du clavier,
* et faire avancer manuellement l'algorithme avec le paramètre :
* @param ctrl
* Faisant office de controleur.
*/
public class Controller implements KeyListener {
  private Ariane ctrl;

  /** 
  * @see Controller#Controller(Ariane ctrl)
  * Permet d'interagir sur l'algorithme de r&eacute;solution :
  * @see <code>Ariane</code>
  */
  public Controller(Ariane ctrl) { this.ctrl = ctrl; }
    
  /**
  * @see Controller#keyPressed(KeyEvent e)
  * Permet la d&eacute;t&eacute;ction et reconnaissance d'une touche lorsqu'elle est appuy&eacute;e,
  * en l'occurence la touche espace, avec le param&egrave;tre d'&eacute;v&egrave;nements KeyEvent :
  * @param e
  */
  public void keyPressed(KeyEvent e) {
    if (e.getKeyCode() == KeyEvent.VK_SPACE)
      ctrl.deplacement();
        /* Rafraichissment des images pour permettre qu'elles se succèdent */
    ctrl.repaint();
  }
  public void keyReleased(KeyEvent e) {}
  public void keyTyped(KeyEvent e) {}
}