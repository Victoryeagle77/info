import javax.swing.JComponent;
import java.awt.*;

public class Sautoir extends JComponent {
  
  private Image img;
  
  public Sautoir() {
    super();
    img = Toolkit.getDefaultToolkit().getImage("cercles.png");
  }

  @Override
  public void paintComponent(Graphics pinceau) {
    int x[] = {0,100,50,100,0,50,0};
    int y[] = {0,0,50,100,100,50,0};
    int[] forme=null;
    forme = new int[x.length];
    System.arraycopy(x, 1, forme, 1, 2) ;
    // on crée un nouveau pinceau pour pouvoir le modifier plus tard
    Graphics secondPinceau = pinceau.create();
    // si le composant n'est pas censé être transparent
    if (this.isOpaque()) {
      // on repeint toute la surface avec la couleur de fond
      secondPinceau.setColor(this.getBackground());
      secondPinceau.fillRect(0, 0, this.getWidth(), this.getHeight());
    }
    secondPinceau.setColor(Color.CYAN);
    for (int r=0; r<5; r++) {
        for (int i=0; i<5; i++) {
            secondPinceau.drawPolygon(x,y,7);
            secondPinceau.fillPolygon(x,y,7);
            for (int f=0; f<x.length; f++) 
               x[f]=x[f]+100;  
    }

    x = new int[]{0,100,50,100,0,50,0};
    for (int g=0; g<y.length; g++) 
      y[g]=y[g]+100;
    }
  } 
}