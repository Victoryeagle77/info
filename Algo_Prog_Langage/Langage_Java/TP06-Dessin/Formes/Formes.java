import javax.swing.JComponent;
import java.awt.*;

public class Formes extends JComponent {
  
  private Image img;
  
  public Formes() {
    super();
    /* Outil d'insertion d'image */
    img = Toolkit.getDefaultToolkit().getImage("cercles.png");
  }

  @Override
  public void paintComponent(Graphics pinceau) {
    /* on crée un nouveau pinceau pour pouvoir le modifier plus tard */
    Graphics secondPinceau = pinceau.create();
    /* si le composant n'est pas censé être transparent */
    if (this.isOpaque()) {
      /* on repeint toute la surface avec la couleur de fond */
      secondPinceau.setColor(this.getBackground());
      secondPinceau.fillRect(0, 0, this.getWidth(), this.getHeight());
    }
    /* maintenant on fait ce que l'on veut */
    secondPinceau.setColor(this.getForeground());
    secondPinceau.drawRect(10,10,50,50);
    /* Carré Blanc à bordure Cyan */
    secondPinceau.setColor(Color.CYAN);
    secondPinceau.fillRect(10,10,51,51);
    secondPinceau.setColor(Color.WHITE);
    secondPinceau.fillRect(12,12,47,47);
    /* Cercle */
    secondPinceau.drawOval(150,20,25,25);
    secondPinceau.setColor(Color.GREEN);
    secondPinceau.fillOval(150,20,25,25);
    /* Ecrire texte Graphiquement */
    secondPinceau.setColor(new Color(238,130,238));
    secondPinceau.setFont(new Font("Courier New", 1, 24));
    secondPinceau.drawString(">o<", 10, 100);
    /* Image */
    secondPinceau.drawImage(img, 100, 70, this);
  }  
}