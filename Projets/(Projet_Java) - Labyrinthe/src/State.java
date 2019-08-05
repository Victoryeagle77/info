import javax.swing.*;
import java.awt.*;

/**
* @author Arthur Chenu
* @version final
*/

/**
* La classe <code>State</code> permet de d&eacute;finir le placement des cases.
*/
public class State extends JButton {
  private boolean obstacle;
  private boolean accessible;
  private boolean src, dst;
    
  /**
  * @see State#State(Editor e)
  * Permet de d&eacute;finir des &eacute;tat de construction
  * R&eacute;utilis&eacute; par la suite et d&eacute;finis &agrave; false
  * @param dst La sortie du labyrinthe (turquoise)
  * @param src Th&eacute;s&eacute;e, l'entr&eacute;e du labyrinthe (rouge)
  * @param obstacle Case inaccessible (noir)
  * @param accessible Case accessible (blanc)
  */
  public State(Editor ctrl){
    dst = false; src = false;
    accessible = false;
    obstacle = false;
    /* Action à la souris */
    addMouseListener(ctrl);
  }
  /**
  * @see State#destination()
  * La sortie, la destination.
  * @return dst
  */
  public boolean destination() { return dst; }
  /** 
  * @see State#placer_destination()
  * Permet de placer sur une case la sortie,
  * en &eacute;tablissant sa valeur bool&eacute;enne &agrave; un autre &eacute;tat,
  * Et de remplacer ce qui existait sur cette case. 
  */
  public void placer_destination() {
    dst = !dst; repaint();
  }
  /**
  * @see State#bouger_destination()
  * Permet de retirer la sortie et de le d&eacute;placer ailleurs sur la grille,
  * En la d&eacute;finissant &agrave; false.
  */
  public void bouger_destination() {
    dst = false; repaint();
  }

  /**
  * @see State#source()
  * L'entr&eacute;e, Th&eacute;s&eacute;e.
  * @return src
  */
  public boolean source() { return src; }
  /** 
  * @see State#placer_source()
  * Permet de placer sur une case l'entr&eacute;e,
  * en &eacute;tablissant sa valeur bool&eacute;enne &agrave; un autre &eacute;tat,
  * Et de remplacer ce qui existait sur cette case. 
  */
  public void placer_source() {
    src = !src; repaint();
  }
  /**
  * @see State#bouger_source()
  * Permet de retirer Th&eacute;s&eacute;e et de le d&eacute;placer ailleurs sur la grille,
  * En le d&eacute;finissant &agrave; false.
  */
  public void bouger_source(){
    src = false; repaint();
  }

  /**
  * @see State#deblockage()
  * Permet avec une valeur bool&eacute; initialis&eacute;e &agrave; flase :
  * @param obstacle
  * De définir, avec l'action d'un clic, lorsque
  * Et efface puis redessine une case blanche accessible sur la grille de bouton.
  */
  public void deblockage() {
    obstacle = !obstacle; repaint();
  }

  /**
  * @see State#lock
  * Les cases infranchissables, inaccessible.
  * @return obstacle
  */
  public boolean lock() { return obstacle; }
  
  /**
  * @see State#invalide()
  * Permet de remplacer la case pr&eacdente;c&eacdente;dente par l'&eacdente;tat utilis&eacdente;.
  */
  public void invalide() {
    dst = false; src = false;
    obstacle = false;
    accessible = false;
  }

  /**
  * @see State#paintComponent(Graphics g) 
  * Permet de d&eacute;finir les couleurs de chaque case
  * En fonction de leur &eacute;tat de construction.
  */
  @Override
  public void paintComponent(Graphics g){
    Graphics pinceau = g.create();
    /* Permet le rafraichissement pour éviter que la fenetre précédente
    se fractionne dans les boutons de la grille. */
    if (isOpaque()) {
      pinceau.setColor(getBackground());
      pinceau.fillRect(0, 0, getWidth(), getHeight());
    }
    /* Définition des couleurs selon l'état des cases */
    if (obstacle) { setBackground(new Color(50,50,50)); }
    else {
      if (src) { setBackground(new Color(200,0,0)); }	
      else {
        if (dst) { setBackground(new Color(0,100,100)); }
        else {
          if (accessible);
          else { setBackground(new Color(255,255,255)); }
        }	
      }
    }
  }
}