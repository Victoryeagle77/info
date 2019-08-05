import javax.swing.*;
import java.awt.*;

public class Fenetre extends JFrame {
  public Fenetre(String nom) {
    super(nom);
    this.setSize(768, 1024);
    this.setLocation(0, 0);
    this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    Image img = new Image("./data/image.bin", 768, 1024);
    this.add(img);
  }
}