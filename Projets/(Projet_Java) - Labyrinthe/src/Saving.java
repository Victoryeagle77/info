import java.awt.*;
import javax.swing.*;
import java.io.*;
import java.util.*;

/**
* @author Arthur Chenu
* @version final
*/

/**
* La classe <code>Saving</code> permet la sauvegarde des &eacute;l&eacute;ments d&eacute;finissant un tableau
* En fonction de la configuration de celui-ci.
*/
public class Saving {
  private State[] cases;
  private int grille, taille;
  private int dst_x, dst_y, src_x, src_y; 
  private byte[] labyrinthe;
  /**
  * @see Saving#Saving(Component[] config)
  * Prend en param&egrave;tre
  * @param config
  * Composant d&eacute;finie dans la classe
  * @see <code>Saving</code>
  */
  public Saving(Component[] config){
    cases = new State[config.length];
    /* Pour toutes cases du labyrinthe */
    for (int i = 0; i <  cases.length; i++) 
      /* On extrait la configuration de l'état de chaque touche */
      cases[i] = (State) config[i];
    taille = (int) Math.sqrt(cases.length);
    
    /* Pour toutes cases du labyrinthe */
    for (int i = 0;  i < cases.length; i++) {
      /* Sortie du labyrinthe */
      if (cases[i].destination()) {
        /* Si ses coordonnées sont comprises,
        entre les dimensions limite de la taille du labyrinthe */
        dst_x = i / taille;
        dst_y = i % taille;
      }
      /* Entrée du labyrinthe (Thésée) */
      if (cases[i].source()) {
        src_x = i/taille;
        src_y = i%taille;
      }
    }
    grille = cases.length/8;
    if (cases.length%8 >= 1) { grille++; }

    labyrinthe = new byte[grille];
    /* Pour le décalage préparé pour la conversion en binaire, 
    on définie la représentation sur 8 bits. */
    for (int i = 0; i < labyrinthe.length; i++) 
      labyrinthe[i] = 00000000;
  }

  /**
  * @see Ecriture#sauvegarde_config(String chemin)
  * Permet l'&eacute;criture dans un fichier des param&egrave;tres d'un labyrinthe
  * @param taille
  * @param src_x
  * @param src_y
  * @param dst_x
  * @param dst_y
  * En ajoutan l'extension .lab sur un fichier dont le chemin est :
  * @param chemin
  */
  public void sauvegarde_config(String chemin){
    try {
      /* Lecture sur l'entrée standard du flux de donnés d'un fichier, 
      que l'on trouvera par son chemin. Ajout d'une extension .lab au nom choisit */
      FileOutputStream file = new FileOutputStream(chemin + ".lab");
      DataOutputStream flux = new DataOutputStream(file);
      flux.write(taille); /* Dimensions du labyrinthe */
      /* Coordonnées en ligne et colonne de l'entrée du labyrinthe */
      flux.write(src_x); flux.write(src_y);
      /* Coordonnées en ligne et colonne de la sortie du labyrinthe */
      flux.write(dst_x); flux.write(dst_y);

      int val = -1, curseur = 0;
      /* Pour les cases de la grille du labyrinthe */
      for (int i = 0; i < taille; i++) {          
        for (int j = 0; j < taille ; j++) {
          val++;
          if (val == 8) { curseur++; val = -1; }
          /* Si la coordonnée de la case est celle d'un obstacle */
          if (cases[i + (j * taille)].lock()) 
            labyrinthe[curseur] ++;
          /* Décalage bit à bit à gauche labyrinthe[curseur] << 1,
          avec la position parcouru du bit actuel */
          labyrinthe[curseur] <<= 1;
        }
      }
      /* Si case multiple de 8 */
      if (cases.length % 8 != 0) {
        for (int i = 0; i < (8 - (cases.length % 8)); i++) 
          labyrinthe[labyrinthe.length-1] <<=1;
      }
      flux.write(labyrinthe, 0, labyrinthe.length);
      /* Fermeture du flux de donnés traités */
      flux.close();
    /* Traitement des erreurs */
    }catch(IOException e){
      System.err.println("Erreur d'\u00E9criture : " + e.getMessage());
    }
  } 
}