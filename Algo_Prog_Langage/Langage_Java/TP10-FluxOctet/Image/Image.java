import javax.swing.*;
import java.awt.*;
import java.io.*;

public class Image extends JComponent {
  public String fichier;
  public int largeur;
  public int hauteur;

  /* L'image et son format */
  public Image(String fichier, int largeur, int hauteur) {
    this.fichier=fichier;
    this.largeur=largeur;
    this.hauteur=hauteur;
  }

  @Override
  public void paintComponent(Graphics pinceau) {
    Graphics secondPinceau = pinceau.create();
    int rouge, vert, bleu;
    /* Gestion prévisionnelle des erreurs de fichier */
    try {
      /* Ouverture du fichie sur l'entrée standard */
      FileInputStream fichier = new FileInputStream("./data/image.bin");
      /* Lecture du fichier dans le flux de données */
      DataInputStream flux = new DataInputStream(fichier);
      for (int i=0; i<1024; i++) {
        for (int j=0; j<768; j++) {
          /* Le fichier lit par octet la composition des couleurs : 
          De 768 par 1024 */
          rouge = flux.read();
          vert = flux.read();
          bleu = flux.read();
          /* Charge la couleur de l'image en fonction des couleurs */
          secondPinceau.setColor(new Color(rouge, vert, bleu));
          secondPinceau.fillRect(j, i, 1, 1);
        }
      }
      /* Fermeture du flux du fichier */
      flux.close();
      /* Gestion des erreurs */
    } catch (FileNotFoundException e) {
      System.err.println("Le fichier de l'image n'est pas disponible");
    } catch (IOException e) {
      System.err.println("IOException");
    }
  }
}