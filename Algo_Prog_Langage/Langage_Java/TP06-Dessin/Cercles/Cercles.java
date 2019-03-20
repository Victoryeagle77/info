import javax.swing.JComponent;
import java.awt.*;

public class Cercles extends JComponent {
  
  private Image img;
  
  public Cercles() {
    super();
    img = Toolkit.getDefaultToolkit().getImage("cercles.png");
  }

  @Override
  public void paintComponent(Graphics pinceau) {
    int longueur=0, hauteur=0, rouge=1;
    int vert=1, bleu=1;
    // on crée un nouveau pinceau pour pouvoir le modifier plus tard
    Graphics secondPinceau = pinceau.create();
    // si le composant n'est pas censé être transparent
    if (this.isOpaque()) {
      // on repeint toute la surface avec la couleur de fond
      secondPinceau.setColor(this.getBackground());
      secondPinceau.fillRect(0, 0, this.getWidth(), this.getHeight());
    }
    // On décrit les cercles
    secondPinceau.setColor(Color.GREEN);
    for (int i=0; i<5; i++){
      for (int j=0; j<5; j++) {
        vert+=9; bleu+=5; rouge+=5;
        secondPinceau.drawOval(longueur,hauteur,50,50);
        secondPinceau.setColor(new Color(rouge,vert,bleu));
        secondPinceau.fillOval(longueur,hauteur,50,50);
        // Entérieur du cercle
        secondPinceau.setColor(Color.WHITE);
        secondPinceau.drawOval(longueur+10, hauteur+10, 30, 30);
        secondPinceau.fillOval(longueur+10, hauteur+10, 30, 30);
        longueur+=50; // Espace entre les colonnes de cercles
      }
      longueur=0;
      hauteur+=50;    
      }
    }
}