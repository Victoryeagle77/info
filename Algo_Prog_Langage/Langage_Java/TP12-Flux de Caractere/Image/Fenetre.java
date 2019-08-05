import javax.swing.*;
import java.awt.*;

public class Fenetre extends JFrame{
  public Fenetre() {
    super("Image");
    this.setSize(100, 100);
    this.setLocation(200, 200);
    this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    this.add(new Image("image.xpm"));    
  }
}