import javax.swing.*;
import java.awt.*;
import javax.swing.filechooser.FileNameExtensionFilter;

/**
* @author Arthur Chenu
* @version final
*/

/** 
* La classe <code>View</code>
* permet la gestion de toutes les fenêtres et de leur succession et mise en forme.
*/
public class View extends JFrame {
  private Ariane alg = new Ariane();
  private Action ctrl = new Action(this, new Model());

  private boolean choix_1;
  private int taille = 0;
    
  static final JLabel titre = new JLabel(">>> Algorithme d'Ariane <<<");
  JLabel indication = new JLabel();
  JPanel panneau = new JPanel();
  private JButton bouton_1 = new JButton();
  private JButton bouton_2 = new JButton();
  static final JButton echap = new JButton("Quitter");
  static final JButton sauvegarde = new JButton("Sauvegarder");
    
  /** 
  * @see View#View()
  * Affiche la premi&eacute;re fenetre ou l'on peut choisir :
  * Soit de construire un labyrinthe et de le sauvegarder
  * Soit d'en charger un dans un fichier octale.
  */
  public View() {
    /* Paramètrage de la fenêtre */
    setTitle("Algorithme d'Ariane");
    setLocationRelativeTo(null);
    setMinimumSize(new Dimension(350, 340));
    setResizable(false);
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    /** 
    * Faire correspondre les boutons d&eacute;finis avec :
    * @see Action#actionPerformed(ActionEvent e)
    * Pour les rendre interactifs et cliquables.
    */
    bouton_1.addActionListener(ctrl);
    bouton_2.addActionListener(ctrl);
    echap.addActionListener(ctrl);
    bouton_1.setText("Construire un labyrinthe");
    bouton_2.setText("Charger un labyrinthe");
    /* Texte permettant de renseigner l'utilisteur sur les actions possibles,
    en html pour pouvoir placer des balises de sauts de ligne "<br>" */
    indication.setText(
      "<html><br>Vous pouvez choisir entre :<br>" +
      "<br>[1] Charger un labyrinthe sauvegarder <br>" +
      "(Vous pouvez en trouver un dans le dossier <br>avec l'explorateur de fichier qui s'affichera " + 
      "<br>si vous faites ce choix : <br>PT21_2018/data/petit.lab)" + 
      "<br>[2] Construire un labyrinthe dans lequel <br>" +
      "vous pouvez placer les obstacles, la source <br>et la destination comme vous le souhaitez.</html>"
    );
    titre.setFont(new Font("Courier New", 1, 15));
    /* La paramètre panneau permet d'ajouter les boutons sur la fenêtre. */
    panneau.add(titre);
    panneau.add(indication);
    panneau.add(bouton_1);
    panneau.add(bouton_2);
    /* Ajouter les boutons et textes sur la fenêtre */
    add(panneau, BorderLayout.CENTER);
    add(echap, BorderLayout.SOUTH);
  }
    
  /** 
  * @see View#construire_labyrinthe()
  * Propose l'affichage du panneau de construction
  * Avec indication (guide)
  */
  public void construire_labyrinthe() {
    setMinimumSize(new Dimension(370, 530));
        
    indication.setText(
      "<html><br>Vous pourez construire en mod :<br>" +
      "<br>[1] Al\u00E9atoire : Les obstacles infranchissables" + 
      "<br>seront plac\u00E9s al\u00E9atoirement dans la grille." + 
      "<br>[2] Totale : La grille est vide et vous " + 
      "<br>placerez l'entr\u00E9e, la sortie ainsi que les<br> obstacles sur la grille manuellement." +
      "<br><br> === Contr\u00f4le des boutons et de la souris ===<br>Appuyez sur les boutons + et - pour augmenter <br>" + 
      "ou r\u00E9duire la taille du labyrinthe." + 
      "<br>Les dimensions de la grille peuvent aller de <br>4 par 4 jsuqu'\u00e0 10 par 10." +
      "<br>- 1 clique gauche = placer un obstacle.<br>- 2 cliques gauche sur la m\u00eame case = le retirer." + 
      "<br>- 1 cliques droit et clique gauche = placer Th\u00E9s\u00E9e." + 
      "<br>- 2 cliques droit et clique gauche = placer sortie.<br>- 3 cliques droit et clique gauche = placer obstacle." +
      "<br><br>=> Une fois que votre labyrinthe est construit et" +
      "<br>sauvegard\u00E9, r\u00E9cup\u00E9r\u00E9 le et charger le.</html>"
    );
    bouton_1.setText("Construction");
        
    panneau.add(indication);
    panneau.add(bouton_1);
    add(panneau, BorderLayout.CENTER);
    add(echap, BorderLayout.SOUTH);
  }
    
  /** 
  * @see View#charger_labyrinthe()
  * permet avec l'appel d'un JFileChooser()
  * D'ouvrir un explorateur de fichier pour choisir un fichier contenant un labyinthe.
  */
  public void charger_labyrinthe() {
    /* Permet d'ouvrir directement dans le répértoire courant,
    pour faciliter la recherche, en l'occurence PT21_2018 */
    JFileChooser selecteur = new JFileChooser("./../data");
    selecteur.setDialogTitle("Selection d'un labyrinthe");
    /* Filtre les fichiers séléctionnable uniquement pour les faire ressortir */
    FileNameExtensionFilter filtre = new FileNameExtensionFilter(
      ".lab", ".lab", "lab");
    selecteur.setFileFilter(filtre);
    int retour = selecteur.showOpenDialog(new JButton("Ouvrir"));
    /* Si aucun fichier n'est séléctionner ou que la touche n'est pas ouvrir */
    if((selecteur.getSelectedFile() == null) || (retour != JFileChooser.APPROVE_OPTION)){
      System.err.println("Aucun fichier s\u00E9l\u00E9ctionner !");
      return;     
    } else if(retour == JFileChooser.APPROVE_OPTION)
      /* Obtient le chemin relatif du fichier */
      taille = ctrl.getData(selecteur.getSelectedFile().getPath());
    choix_resolution();
  }

  /**
  * @see View#choix_resolution()
  * Permet de choisir le mod de  r&eacute;solution pour r&eacute;soudre le labyrinthe :
  * Soit un automate d&eacute;t&eacute;ministe soit un algorithme al&eacute;atoire.
  */
  public void choix_resolution() {
    indication.setText(
      "<html><br>Choisissez entre 2 types de resolution :<br>" +
      "<br>[1] Al\u00E9atoire : Chaque direction est choisie <br>" + 
      "de mani\u00E9re totalement impr\u00E9visible et <br>" + 
      " al\u00E9atoire, pour se diriger vers la sortie du <br>labyrinthe." + 
      "<br>[2] D\u00E9terministe : Emprunte toujours le " + 
      "<br>meme chemin et tente de faire en moins <br>" + 
      "d'\u00E9tapes possibles pour atteindre la sortie<br> du labyrinthe.</html>"
    );
    bouton_1.setText("Mod aleatoire");
    bouton_2.setText("Automate Deterministe");
        
    panneau.add(indication);
    panneau.add(bouton_1);
    panneau.add(bouton_2);
    add(panneau, BorderLayout.CENTER);
    add(echap, BorderLayout.SOUTH);
  }

  /**
  * @see View#visuel_resolution(boolean choix_1)
  * Permet de choisir le type d'affichage du mod de r&eacute;solution :
  * Soit manuel soit automatique, avec le param&egrave;tre bool&eacute;en :
  * @param choix_1
  * Et lance en fonction de cette variable :
  * @see affichage_automatique(int[][] cases, boolean choix_2)
  */
  public void visuel_resolution(boolean choix_1){
    this.choix_1 = choix_1;
    /* Rafraichissement */
    getContentPane().removeAll();
    getContentPane().repaint();
        
    bouton_1.setText("Visuel manuel");
    bouton_2.setText("Visuel automatique");
    indication.setText(
      "<html><br>Choisissez entre 2 types de visionnage de la<br> resolution :<br>" + 
      "<br>[1] Manuel : Tapez sur la touche SPACE pour " + 
      "<br>voir graphiquement la progression de <br>l'algorithme sur la modelisation du <br>labyrinthe." + 
      "<br>[2] Automatique : Le labyrinthe n'apparait <br>" +
      "pas et seul le nombre de coups pour <br>atteindre la sortie du labyrinthe est affich\u00E9.</html>"
    );
    panneau.add(indication);
    panneau.add(bouton_1);
    panneau.add(bouton_2);
    add(panneau, BorderLayout.CENTER);
    add(echap, BorderLayout.SOUTH);
  }
    
  /**
  * @see View#affichage_automatique(int[][] cases, boolean choix_2)
  * Permet de pr&eacute;parer la fenetre pour le mod automatique
  * En prenant comme param&eagrve;tre :
  * @param cases
  * @param choix_2 pour d&eacute;cider de lancer le mod automatique ou non
  * Pour que l'algorithme et l'automate r&eacute;utilise cette donn&eacute;e,
  * Et décider en fonction de :
  * @param choix_1 
  * De lancer le mod automatique pour l'algorithme d&eacute;t&eacute;rministe ou al&eacute;atoire.
  * @see Arianne#aleatoire(taille, cases)
  * @see Arianne#deterministe(taille, cases)
  * Et calcul ainsi le nombre d'&eacute;tapes et son affichage.
  */
  public void affichage_automatique(int[][] cases, boolean choix_2) {
    /* Rafraichissement */
    getContentPane().removeAll();
    getContentPane().repaint();
    /* Adapter la taille de la fenêtre au labyrinthe,
    et à l'affichage du mod auto. */
    setMinimumSize(new Dimension(taille*100, taille*70));
    addKeyListener(new Controller(alg));
    /* Le focus est le fait qu'un composant soit "sélectionné" ou pas. 
    Il se désactive ici donc il faut le rappeler pour la fenêtre actuelle. */
    requestFocusInWindow();

    add(echap, BorderLayout.SOUTH);
    if (choix_2 != true) { add(alg); }
    if (choix_2){
      /* Ferme la JFrame précédente */
      dispose(); 
      JOptionPane.showMessageDialog(null, ">>> G\u00E9n\u00E9ration automatique du chemin vers la sortie : " 
                 + alg.automatique(taille, cases, choix_1 != true) + " \u00E9tapes <<<", null,
                 JOptionPane.CLOSED_OPTION);
      /* Fermeture du programme */
    } else if (choix_1 && choix_2 != true) 
      /* Moyenne sur 100 simulations */
      alg.aleatoire(taille, cases);
    else { alg.deterministe(taille, cases); }
  }
}