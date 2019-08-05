import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Actions implements MouseListener, MouseMotionListener, KeyListener {
  Playlist playlist;
  boolean controle;

  public Actions(Playlist panneau) {
    this.playlist = panneau;
    this.controle = false;
  }

  /**** Bouton de souris ****/
  public void mouseClicked(MouseEvent e) {
    if (this.controle){ this.playlist.ajouterGrey(e.getY()); }
    else{ this.playlist.changeGrey(e.getY()); }
  } 
  /* Bouton cliqué */
  public void mouseEntered(MouseEvent evenement) {/* debut du survol */}
  public void mouseExited(MouseEvent evenement) {/* fin du survol */}
  public void mousePressed(MouseEvent evenement){/* bouton appuyé */} 
  public void mouseReleased(MouseEvent evenement){/* bouton relâché */}
  public void mouseDragged(MouseEvent event) {/* mouvement appuyé */}
  public void mouseMoved(MouseEvent event) {
    /* Mouvement libre */
    this.playlist.changeCyan(event.getY());
  }

  /**** Touche clavier ****/
  public void keyPressed(KeyEvent e) {
    /* Séléction multiples de plusieurs morceaux
    de musique dans la playlist */
    if (e.getKeyCode() == KeyEvent.VK_CONTROL)
      /* Touche du clavier "Ctrl" */
      this.controle = true;
  }
  public void keyReleased(KeyEvent e) {
    /* Garde la séléction multiples de plusieurs morceaux 
    de musique dans la playlist */
    if (e.getKeyCode() == KeyEvent.VK_CONTROL)
      this.controle = false;
  }
  public void keyTyped(KeyEvent e) {}
}