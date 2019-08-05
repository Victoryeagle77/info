import java.awt.event.*;

public class Actions implements MouseListener, MouseMotionListener {
  private Fond fond;
  private boolean deplacement;

  public Actions(Fond f) {
    this.fond = f;
    this.deplacement = false;
  }

  /**** Déplacement de souris ****/
  public void mouseDragged(MouseEvent e) {
    if (this.deplacement)
      /* Déplacement en abscisse en ordonnée */
      fond.bouger(e.getX(), e.getY());
  }
  public void mouseMoved(MouseEvent e) {}
  public void mouseClicked(MouseEvent evenement){}
  public void mouseEntered(MouseEvent evenement){}
  public void mouseExited(MouseEvent evenement){}
  public void mousePressed(MouseEvent e) {
    int x = this.fond.etat_x();
    int y = this.fond.etat_y();
    /* Relever la position x et y par l'évenement Mousevent e*/
    if ((e.getX() > x) && (e.getX() < x+30))
      if ((e.getY() > y) && (e.getY() < y+30))
        this.deplacement = true;
  }
  public void mouseReleased(MouseEvent evenement){
    this.deplacement = false;
  }
}