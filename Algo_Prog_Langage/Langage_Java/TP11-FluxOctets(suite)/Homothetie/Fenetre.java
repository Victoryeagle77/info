import javax.swing.*;
import java.awt.*;
import java.io.IOException;

public class Fenetre extends JFrame{
  public Fenetre() {
    super("Fenetre");
    this.setSize(500, 500);
    this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    try{
      /* Affiche la forme */
      Polygone fenetre = new Polygone("./data/polygone.bin", 2);
      this.add(fenetre);
    }catch (IOException e) {
      System.err.println("Erreur" + e.getMessage());
    } 
  }
}