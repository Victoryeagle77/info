import java.awt.*;
import javax.swing.*;

/**
* La classe <code>Build</code> permet de pr&eacute;parer une fenetre graphique,
* avec ces &eacute;l&eacute;ments graphiques pour la construction du labyrinthe par l'utilisateur.
*/
public class Build extends JFrame {
  private int largeur, hauteur;
  static final JButton decr = new JButton("-");
  static final JButton incr = new JButton("+");
  static final JButton aleatoire = new JButton("Aleatoire");
  static final JButton sauver = new JButton("Sauvegarder");
  private JPanel panneau = new JPanel();
  private JPanel labyrinthe = new JPanel();

  /**
  * @see Build#Build(int l, int h)
  * Prend en param&egrave;tre
  * @param l La largeur 
  * @param h La hauteur 
  * De la fenetre &agrave; afficher et y ordonne les boutons.
  */
  public Build(int l, int h){
    largeur = l; hauteur = h;
    /* Taille de la fenêtre récupérée pour y adapter les éléments qui la compose. */
    setSize(l, h);
    setTitle("Algorithme d'Ariane");
    setLocationRelativeTo(null);
    setResizable(false);
    setLayout(null);
    /* Ajustement des boutons dans la fenêtre */
    panneau.setSize(largeur/2, hauteur/5);
    panneau.setLocation(largeur/4 - 10, 0);
    /* Bouton d'augmentation et diminution de la grille du labyrinthe. */
    panneau.add(decr);
    panneau.add(incr);
    /* Bouton de génération aléatoire des obstacles */
    panneau.add(aleatoire);
    /* Bouton de sauvegarde de la grille */
    panneau.add(sauver);

     
    /* Ajustement de la grille du labyrinthe sur la fenêtre */
    labyrinthe.setLayout(new GridLayout(4,4));
    labyrinthe.setSize(3*largeur/5, 3*hauteur/5);
    labyrinthe.setLocation(largeur/5 - 5, hauteur/5);
		
    /**
    * @see Editor#Editor(JPanel e)
    * Prend en param&egrave;tre
    * @param labyrinthe JPanel qui g&egrave;re la grille de construction du labyrinthe.
    * @see Stat#Stat
    * Permet de g&eacute;rer les cases et leur &eacute;tat de construction.
    */
    Editor ctrl = new Editor(labyrinthe);
    State[] cases = new State[16];
    /* Pour toutes les cases remplissant la grille */
    for (int i = 0; i < cases.length; i++) {
      /* Rendre interactive les cases et leur attribuer un état booléen pour la construction. */
      cases[i] = new State(ctrl);
      labyrinthe.add(cases[i]);
    }
    /* Rendre tous les boutons interactifs */
    decr.addActionListener(ctrl);
    incr.addActionListener(ctrl);
    aleatoire.addActionListener(ctrl);
    sauver.addActionListener(ctrl);
    /* Ajouter à l'affichage de la fenêtre */
    add(panneau);
    add(labyrinthe);
    /* Ajouter intéractivitée du contrôle à la souris*/
    addMouseListener(ctrl);
  }	
}
