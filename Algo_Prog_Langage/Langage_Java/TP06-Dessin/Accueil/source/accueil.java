import javax.swing.JComponent;
import java.awt.*;

public class accueil extends JComponent {
  
  private Image img;
  
  public accueil() {
    super();
    img = Toolkit.getDefaultToolkit().getImage("../images/cercles.png");
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
    secondPinceau.drawRect(0,0,280,210);
    secondPinceau.setColor(new Color(54,44,97));
    secondPinceau.fillRect(0,0,280,210);

    secondPinceau.drawImage(img,0, 30, this);

    secondPinceau.setColor(new Color(238,130,238));
    secondPinceau.setFont(new Font("Courier New", 1, 24));
    secondPinceau.setColor(Color.WHITE);
    secondPinceau.drawString("IUT", 25, 40);
    secondPinceau.setFont(new Font("Courier New", 1, 18));
    secondPinceau.drawString("départements", 100, 35);
    secondPinceau.drawString("informatique", 110, 55);
    secondPinceau.setFont(new Font("Courier New", 1, 15));
    secondPinceau.drawString("login",50, 120);
    secondPinceau.drawString("password",10, 160);
  }

}