import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.Random;
import javax.swing.filechooser.FileNameExtensionFilter;

/**
* @author Arthur Chenu
* @version final
*/

/**
* La classe <code>Editor</code> est le mod d'&eacute;dition du labyrinthe.
* - Elle permet de configurer sa taille.
* - De cr&eacute;er un labyrinthe avec l'interactivit&eacute;e de la souris,
* - De placer la source et la destination
* - Et d'ouvrir une fenetre graphique pour sauvegarder le labyrinthe.
*/
public class Editor implements ActionListener, MouseListener {
  private JPanel labyrinthe;
  private int taille;
  private State cases;
  private JFrame fenetre = new JFrame();
  int clique;
  private Component[] config;
    
  /**
  * @see Editor#Editor(JPanel panneau)
  * Permet de r&eacute;p&eacute;rer 
  * @param panneau La grille repr&eacute;sentant le labyrinthe.
  * Et d'initialiser la taille au minimum.
  */
  public Editor(JPanel panneau){
    this.labyrinthe = panneau;
    this.taille = 4;
  }
  /**
  * @see Editor#actionPerformed(ActionEvent e)
  * Permet de d&eacute;finir la taille du labyrinthe et de r&earencer;f&earencer;rencer, 
  * avec les boutons le lancement de la g&earencer;n&earencer;ration aléatoire et la sauvegarde.
  */
  public void actionPerformed(ActionEvent e) {
    if (e.getActionCommand().equals("+")) {
      /* Tant qu'on appuie sur le bouton "+",
      on augmente la dimension de la grille du labyrinthe jusqu'à 10,
      (10 par 10 étant la taille maximale) */
      taille++;	
      if (taille > 10) { taille--; }
      config_labyrinthe();
    } else if (e.getActionCommand().equals("-")) {
      /* Tant qu'on appuie sur le bouton "+",
      on augmente la dimension de la grille du labyrinthe jusqu'à 4,
      (4 par 4 étant la taille minimale) */
      taille--;
      if (taille < 4) { taille++; }
      config_labyrinthe();
    } else if (e.getActionCommand().equals("Aleatoire"))
      grille_aleatoire();
    else if (e.getActionCommand().equals("Sauvegarder"))
      sauvegarder_labyrinthe(e);
  }
    
  /**
  * @see Editor#config_labyrinthe()
  * Permet de redimensioner la grille du labyrinthe,
  * en fonction de la variation de la taille d&eacute;finie dans  
  * @see Editor#actionPerformed(ActionEvent e)
  */
  public void config_labyrinthe() {
    /* Rafraichissement de la grille du labyrinthe */
    labyrinthe.removeAll();
    labyrinthe.repaint();
    /* Revalidation des éléments interactifs */
    labyrinthe.revalidate();
    labyrinthe.setLayout(new GridLayout(taille, taille));
		
    State[] etat_cases = new State[taille*taille];
    for (int i = 0; i < etat_cases.length ; i++) {
      etat_cases[i] = new State(this);
      labyrinthe.add(etat_cases[i]);
    }
  }

  /**
  * @see Editor#mouseClicked(MouseEvent e)
  * Permet de placer la destination, la source et les obstacles
  * En fonction du clique de la souris effectu&eacute;.
  */
  public void mouseClicked(MouseEvent e) {
    /* Détecte l'action clique droit, définie par SwingUtilities */
    if ((SwingUtilities.isRightMouseButton(e))){
      /* Compteur de clique droit */
      switch(clique){
        case 0 : clique++; break;
        case 1 : clique++; break;
        case 2 : clique = 0; break;
      }
      /* Détecte l'action clique gauche, définie par SwingUtilities */
    } else if ((SwingUtilities.isLeftMouseButton(e))) {
      /* Permet de récupérer l'état du composant et le réutilisé pour la sauvegarde */
      config = labyrinthe.getComponents();
      cases = (State) e.getSource();
      if (clique == 0) {
        cases.deblockage();
        /* Effacer et remplacer */
        cases.repaint();
      } else if(clique == 1) {
        for (int i = 0; i < config.length; i++) {
          /**
          * Attribue un &eacute;tat de construction aux cases 
          * Avec les informations et param&egrave;tres de la classe <code>State</code>.
          */
          State constr_etat = (State) config[i];
          constr_etat.bouger_destination(); constr_etat.repaint();
        }
        /* Efface la case précédente et la remplace par la sortie */
        if (cases.lock() | cases.source())
          cases.invalide();
        cases.placer_destination(); cases.repaint();
      } else if (clique == 2) {
        for (int i = 0; i < config.length; i++) {
          State constr_etat = (State) config[i];
          constr_etat.bouger_source(); constr_etat.repaint();
        }
        /* Efface la case précédente et la remplace par Thésée */
        if (cases.lock() | cases.source())
          cases.invalide();
        cases.placer_source(); cases.repaint();
      }
    }
  }
  public void mouseEntered(MouseEvent e) {}
  public void mouseExited(MouseEvent e) {}
  public void mousePressed(MouseEvent e) {}
  public void mouseReleased(MouseEvent e) {}

  /**
  * @see Editor#grille_aleatoire()
  * G&eacute;n&egrave;re al&eacute;atoirement des obstacles dans le labyrinthe
  * en fonction de ses dimensions.
  */
  public void grille_aleatoire() {
    /* Rafraichissement */
    labyrinthe.removeAll();		
    labyrinthe.setLayout(new GridLayout(taille, taille));
    State[] etat_cases = new State[taille*taille];
    /* Pour toutes case présente dans la grille du labyrinthe */
    for (int i = 0; i < etat_cases.length ; i++) {
      etat_cases[i] = new State(this);
      /* Génération aléatoire entre 0 et 1 */
      if (new Random().nextInt(2) == 1) {
        etat_cases[i].deblockage();
        etat_cases[i].repaint();
      }
      labyrinthe.add(etat_cases[i]);
    }
    fenetre = (JFrame) SwingUtilities.windowForComponent(this.labyrinthe);
    fenetre.revalidate();
  }
  /**
  * @see Editor#sauvegarder_labyrinthe(ActionEvent e)
  * Permet de sauvegarder la grille avec 
  * @see Saving#sauvegarde_config(String chemin)
  */
  public void sauvegarder_labyrinthe(ActionEvent e) {

    State[] etat_cases = new State[taille*taille];
    config = labyrinthe.getComponents();

    boolean dst = false, src = false;
    /* On vérifie pour toutes les cases de la grille du labyrinthe */
    for (int i = 0; i < etat_cases.length ; i++) {
      etat_cases[i] = (State) config[i];
      /* Permet de retirer le focus, le fait qu'un composant soit activé. */
      etat_cases[i].setFocusPainted(false);

      if (etat_cases[i].destination()) { dst = true; }
      if (etat_cases[i].source()) { src = true; }
    }
    /* On enregistre uniquement si Thésée et la sortie sont placés. */
    if (dst & src) {
      JFrame fenetre = (JFrame) SwingUtilities.windowForComponent(
        (JButton) e.getSource());
      /* Relever les tailles de la Jframe */
      fenetre.getWidth();
      fenetre.getHeight();
      /* Ferme la fenetre après la sauvegarde */
      fenetre.dispose();
      /* Permet d'ouvrir directement dans le répértoire courant,
      pour faciliter la recherche, en l'occurence PT21_2018 */
      JFileChooser selecteur = new JFileChooser("./../data");
      selecteur.setDialogTitle("Sauvegarde d'un labyrinthe");
      /* Filtre les fichiers séléctionnable uniquement pour les faire ressortir */
      FileNameExtensionFilter filtre = new FileNameExtensionFilter(
        ".lab", ".lab", "lab");
      selecteur.setFileFilter(filtre);
      int retour = selecteur.showSaveDialog(new JButton("Enregistrer"));
      /* Si aucun fichier n'est séléctionner ou que la touche n'est pas enregistrer */
      if((selecteur.getSelectedFile() == null) || (retour != JFileChooser.APPROVE_OPTION)){
        System.err.println("Aucun fichier cr\u00E9\u00E9 !");
        return;    
      } else if(retour == JFileChooser.APPROVE_OPTION)
        new Saving(config).sauvegarde_config(selecteur.getSelectedFile().getPath());
    }
  }
}