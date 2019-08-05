import java.awt.image.*;
import javax.swing.JComponent;
import java.awt.Graphics;
import java.io.*;

public class Image extends JComponent {
	
  public BufferedImage image;
  public int x, y;

  public Image(String chemin){
    image = lecteur(chemin);
  }

  @Override
  public void paintComponent(Graphics pinceau) {
    /* on crée un nouveau pinceau pour pouvoir le modifier plus tard */
    Graphics secondPinceau = pinceau.create();
    /* si le composant n'est pas censé être transparent */
    if (this.isOpaque()) {
      /* on repeint toute la surface avec la couleur de fond */
      secondPinceau.setColor(this.getBackground());
      secondPinceau.fillRect(0, 0, this.Largeur(), this.Hauteur());
    }
    secondPinceau.drawImage(image, 0, 0, this);
  }

  public int Largeur(){ return x; }
  public int Hauteur(){ return y; }

  public BufferedImage lecteur(String file){
    x = 0; y = 0;
    boolean verification = true;
    int chaine=0;
    BufferedImage image=null;
    try{
      /* Lecture du fichier image */
      FileInputStream fichier = new FileInputStream(file);
      BufferedReader flux = new BufferedReader(new InputStreamReader(fichier));
      String ligne, tmp = "";
      String[] couleur = new String[0];
      char[] caractere = new char[0]; 
      try {
        String[] tab;
        while(true){
          if (flux.ready()) {
            /* Lecture de String */
            ligne = flux.readLine();
            /* Si un String commence par " */
            if(ligne.startsWith("\"")){
              /* Extrait de chaine la sous-chaîne contenant 1 caractère,
              en partant de la longeur de la chaine - 2  */
              tmp = ligne.substring(1, ligne.length()-2);
              if (verification) {
                verification = false;
                /* split() découpe le String en utilisant l'expression régulière " " */
                tab = tmp.split(" ", 4);
                /* Conversion en entier des éléments String correspondant aux dimensions du tableau */
                x = Integer.parseInt(tab[0]);
                y = Integer.parseInt(tab[1]);
                chaine = Integer.parseInt(tab[2]);
                break;
              }
            }
          } else { break; }
        }

        couleur = new String[chaine];
        caractere = new char[chaine];

        for (int i=0; i<chaine; i++) {
          ligne = flux.readLine();
          if(ligne.startsWith("\"")){
            tmp = ligne.substring(1, ligne.length()-2);
            tab = tmp.split(" c ", 2);
            System.out.println(tab[0]);
            caractere[i] = tab[0].charAt(0);
            couleur[i] = tab[1].substring(1);
          } else { i--; }
        }
        /* Lecture de l'image selon ses dimensions et son type de colorimétrie */
        image = new BufferedImage(x, y, BufferedImage.TYPE_INT_RGB);
        for (int k=0; k<y; k++) {
          ligne = flux.readLine();
          if(ligne.startsWith("\"")){
            for (int y=0; y<x; y++) {
              tmp = ligne.substring(1, x+1);							
              for (int l=0; l<caractere.length; l++) {
                /* Retourne le caractère situé à la position y de la chaine. */
                if (caractere[l] == tmp.charAt(y)) {
                  image.setRGB(y, k, Integer.parseInt(couleur[l], 16));
                }
              }
            }
          } else { k--; }
        }
        flux.close();
      }catch (IOException e) {
        System.err.println(e.getMessage());
      }
    }catch (FileNotFoundException e) {
      System.err.println("pas de fichier trouver : " + e.getMessage());
    }
    return image;
  }
}