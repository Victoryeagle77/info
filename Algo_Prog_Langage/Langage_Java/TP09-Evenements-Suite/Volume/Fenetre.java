import javax.swing.*;
import java.awt.*;

public class Fenetre extends JFrame {
  public Fenetre(){
    super("Fenetre");
    this.setSize(1520, 200);
    this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
    Forme roleur = new Forme();
    Evenement e = new Evenement(roleur);
		
    this.addMouseWheelListener(e);
    this.add(roleur);
  }
}