import javax.swing.*;
import java.awt.*;
import java.io.*;

public class Fenetre extends JFrame {
  public Fenetre() {
    JPanel data = new JPanel();
    Action observateur = new Action(data);
    Activation ctrl = new Activation(this, data);
    
    try {
      /* Lecture sur l'entrée standard dans le fichier */
      FileInputStream fichier = new FileInputStream("./data/save.dat");
      DataInputStream flux = new DataInputStream(fichier);
      /* Lecture des paramètres suviants */
      int pos_x = flux.readInt();
      int pos_y = flux.readInt();
      int largeur = flux.readInt();
      int hauteur = flux.readInt();
      int rouge = flux.readInt();
      int vert = flux.readInt();
      int bleu = flux.readInt();
      /* Chargé le fond de la fenêtre avec les couleur rgb lues */
      data.setBackground(new Color(rouge,vert,bleu));
      this.setLocation(pos_x, pos_y);
      this.setSize(largeur, hauteur);
      flux.close();
    } catch (FileNotFoundException e) {
      /* Position et taille par défault si erreur de fichier de sauvegarde */
      this.setLocation(0, 0);
      this.setSize(200, 200);
    } catch (IOException e) {
      System.err.println("Problème fichier \"save.dat\"" + e.getMessage());
    }
    this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    this.addWindowListener(ctrl);
    /* Boutons d'activation */
    JPanel panneau = new JPanel();
    JButton cyan = new JButton("Cyan");
    JButton jaune = new JButton("Jaune");
    JButton magenta = new JButton("Magenta");

    cyan.addActionListener(observateur);
    jaune.addActionListener(observateur);
    magenta.addActionListener(observateur);
    /* Gestionnaire d'ordonnement des boutons */
    panneau.setLayout(new GridLayout(3,1));

    panneau.add(cyan);
    panneau.add(jaune);
    panneau.add(magenta);

    data.add(panneau);

    this.add(data,BorderLayout.CENTER);
  }
}