import javax.swing.JComponent;
import java.awt.*;
import java.io.*;


public class Polygone extends JComponent{
  public int taille;
  public int[] y, x;

  public Polygone(String chemin_fichier, int proportions) throws IOException{
    FileInputStream fichier = new FileInputStream(chemin_fichier);
    DataInputStream flux = new DataInputStream(fichier);

    taille = flux.available()/(4*2);
    x = new int[taille];
    y = new int[taille];
    /* Lecture par octet dans le fichier "polugone.bin" */
    for (int i=0; i<taille; i++) {
      y[i] = flux.readInt() * proportions;				
      x[i] = flux.readInt() * proportions;			
    }
    flux.close();
  }

  @Override
  public void paintComponent(Graphics pinceau) {
    Graphics secondPinceau = pinceau.create();
    secondPinceau.setColor(Color.RED);
    secondPinceau.fillPolygon(x,y,taille);
  }
}