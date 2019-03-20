import java.awt.Point;
 
public class Etoile implements ProducteurDePoints {
  private static final int x = 100;
  private static final int y = 100;
  private static final double rayon = 90.0;
  private static final double angle = Math.PI/4.0;
  private static final double i = (4.0*Math.PI)/5.0;
  private double numero;

  public Etoile() { this.numero = 0.0; }
  public Point suivant() {
    Point point = null;
    if (this.numero < 6.0) {
      double angle = Etoile.angle + this.numero * Etoile.i;
      point = new Point((int)(Etoile.rayon * Math.cos(angle)),
                    (int)(Etoile.rayon * Math.sin(angle)));
      point.translate(Etoile.x, Etoile.y);
      this.numero++;
    } else { this.numero = 0.0; }
    return point;
  }
}