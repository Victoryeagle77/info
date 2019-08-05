import javax.swing.JComponent;
import java.awt.Graphics;
import java.awt.Point;

public class Polyligne extends JComponent {
  private ProducteurDePoints tmp;
  private int nb_points;

  public Polyligne(ProducteurDePoints t, int nb) {
    tmp=t;
    nb_points=nb;
  }
  
  @Override
  public void paintComponent(Graphics pinceau) {
    Graphics secondPinceau = pinceau.create();
    Point n=tmp.suivant();
    Point p;

    for (int i=0; i<nb_points; i++) {
      p=tmp.suivant();
      secondPinceau.drawLine((int)n.getX(),(int)p.getX(),
                             (int)n.getY(),(int)p.getY());
      n=p;
    }
  }
}