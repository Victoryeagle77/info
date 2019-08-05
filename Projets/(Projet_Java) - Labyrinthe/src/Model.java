import java.io.*;
import java.awt.*;
import javax.swing.*;
import java.util.*;

/**
* @author Arthur Chenu
* @version final
*/

/** 
* La classe <code>Model</code>
* permet de lire un fichier et stocker les valeurs qui doivent etre comptablis&eacute;es comme param&egrave;tre du labyrinthe.
* Celle-ci effectue cette lecture et ce stockage avec les variables : 
* @param [][] cases : Représente un case du labyrinthe
* @param taille : Dimension du labyrinthe
* @param i : Incrémentation en ligne
* @param j : Incrémentation en colonne 
* @param val : Variable tampon initialis&eacute;e &agrave; 0, r&eacute;cup&eacute;rant les bits
* @param src_x : Coordonnée en ligne de la source (position initiale de Th&eacute;s&eacute;e dans le labyrinthe).
* @param src_y : Coordonnée en colonne de la source (position initiale de Th&eacute;s&eacute;e dans le labyrinthe).
* @param dst_x : Coordonnée en ligne de la destination (position finale que doit atteindre Th&eacute;s&eacute;e dans le labyrinthe).
* @param dst_y : Coordonnée en colonne de la destination (position finale que doit atteindre Th&eacute;s&eacute;e dans le labyrinthe).
*/
public class Model {
  private int[][] cases;
  private byte taille, i, j;
  private byte src_x, src_y, dst_x, dst_y;
  byte val = 0;

  /**
  * @see Model#charge_config(String chemin)
  * Prend le chemin du fichier 
  * @param chemin
  * d&eacute;fini par le JFileChooser de :
  * @see View#charger_labyrinthe()
  * Prend un fichier en mode lecture et le converti en binaire
  * pour interpr&egrave;ter en donn&eacute;es les
  * dimension du labyrinthe (nombre de cases), l'entr&eacute;e et l'arriv&egrave;e. 
  * @return cases
  */
  public int[][] charge_config(String chemin) {
    try{
      /* Lecture sur l'entrée standard du flux de donnés d'un fichier, 
      que l'on trouvera par son chemin */
      FileInputStream file = new FileInputStream(chemin);
      DataInputStream flux = new DataInputStream(file);
      try {
        /* Lecture bite par bite des fichiers contenant les paramètres d'un labyrinthe. */
        taille = flux.readByte();
        src_y = flux.readByte(); src_x = flux.readByte();
        dst_y = flux.readByte(); dst_x = flux.readByte();
        /**
        * @param cases
        * Devient un tableau double dimension pour la hauteur et la largeur du labyrinthe.
        * -> cases[][] = 0 : Case sur le labyrinthe libre.
        * -> cases[][] = 1 : Case sur le labyrinthe bloqu&eacute;e. 
        * -> cases[][] = 2 : Source, point de d&eacute;part.
        * -> cases[][] = 3 : Destination, point d'arriv&eacute;e.
        */
        cases = new int[taille][taille];
        /* Pour les cases de la grille du labyrinthe */
        for (i=0; i<taille; i++) {
          for (j=0; j<taille; j++) {
            /* On converti en binaire le contenu des fichiers qu'on lira,
            puis on s'occupe de calculer l'état d'une case */
            if (((i*taille + j) % 8) == 0)
              val = flux.readByte();
            /* On calcul en bianire pour voir si une cases vaut 0 ou 1
            (Rappel : Accessible ou pas) 2^(7-dim) % 8*/
            if ((val & (byte)Math.pow(2, (7 - (i*taille+j) % 8))) != 0){
              cases[i][j] = 1;
            } else { cases[i][j] = 0; }
          }
        }
        /* Entrée du labyrinthe */
        cases[src_x][src_y] = 2;
        /* Sortie du labyrinthe */
        cases[dst_x][dst_y] = 3;
        /* Traitement des erreurs */
      }catch (IOException e) {
        System.err.println("Erreur d'ouverture : " + e.getMessage());
      }
      /* Fermeture du flux de donnés traités */
      flux.close();
    }catch(IOException e){
      System.err.println("Erreur d'ouverture : " + e.getMessage());
    }
    return cases;
  }
    
  /**
  * @see Model#getSize()
  * @return taille
  */
  public int getSize() { return taille; }
}