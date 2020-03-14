package src;
import api_jardin.ParcelleJ;
import api_jardin.JardinFactoryJ;
import javax.swing.*;
import javax.swing.JComboBox;
import javax.swing.border.*;
import java.awt.*;
import java.awt.event.*;
import java.time.LocalDate;

/**
* @author Arthur Chenu
* @author Julien Carcau
* @version final
*/

/** 
* La classe <code>View</code>
* permet la gestion de toutes les fenetres, de leur succession et mise en forme.
*/
public class View extends JFrame {
  private CardLayout diapo = new CardLayout();
  /* Dimension de l'écran */
  private Dimension taille = Toolkit.getDefaultToolkit().getScreenSize();
  /* Champs de textes pour entrer les dimensions du terrain */
  protected final static JTextField nom = new JTextField(), 
    longueur = new JTextField(), largeur = new JTextField();
  protected JComboBox<String> liste = new JComboBox<>();
  protected final static JButton charg = new JButton("Charger jardin"), 
  retour = new JButton("Retour");
  protected final static JPanel jardin = new JPanel();
  /* Actions du controleur sur les boutons */
  private Interaction ctrl = new Interaction(this);

  /** 
  * @see View#View()
  * Affiche le titre sur tous les pages, et lance la première page.
  */
  public View() {
    /* Utilisation généralisée du titre */
    super("Parcelle (@Chenu-Carcau)");
    depart();
  }

  /** 
  * @see View#depart()
  * Affiche la premi&eacute;re fenetre ou plusieurs choix sont possibles.
  */
  public void depart(){
    setMinimumSize(new Dimension((taille.width/2), (taille.height/2)));
    setResizable(false);
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    /* Défileur de carte du cardLayout */
    setLayout(diapo);

    JPanel accueil = new JPanel();
    accueil.setBackground(new Color(30,30,30));
    accueil.setLayout(new FlowLayout(FlowLayout.CENTER, 0, 60));
    /* Données d'édition des textes */
    JLabel titre = new JLabel("Garden Division");
    titre.setFont(new Font("Courier New", Font.BOLD, 21));
    titre.setForeground(Color.WHITE);

    JButton modelisation = new JButton("Mod\u00e9liser");

    /* JPanel d'ajustement des éléments dans la fenêtre */
    JPanel ajustement = new JPanel();
    ajustement.add(titre);
    
    /* Nom du jardin a etnrer */
    ajustement.add(new JLabel(
      "<html><font color='white'>Entrez un titre</font></html>"
      )); ajustement.add(nom);
    
    /* Longueur du jardin à entrer */
    ajustement.add(new JLabel(
      "<html><font color='white'>Entrez une longueur [entre 20 et 1000]</font></html>"
      )); ajustement.add(longueur);
    
    /* Largeur du jardin à entrer */
    ajustement.add(new JLabel(
      "<html><font color='white'>Entrez une largeur [entre 20 et 1000]</font></html>"
      )); ajustement.add(largeur);
    
    /* Séléctionner un jardin à entrer */
    ajustement.add(new JLabel(
      "<html><font color='white'>S\u00e9l\u00e9ctionner un jardin</font></html>"
      )); ajustement.add(liste); 
    /* Récupération des noms dans la base de données */
    Model db = new Model();
    String[] tab = db.getNom().toArray(
      new String[db.getNom().size()]);
    for (int i=0; i<tab.length; i++) 
      liste.addItem(tab[i]);

    /* Charger un jardin */
    ajustement.add(new JLabel(
      "<html><font color='white'>Chargez un jardin</font></html>"
      )); ajustement.add(charg);
    
    /* Créer un nouveau jardin */
    ajustement.add(new JLabel(
      "<html><font color='white'>Cr\u00e9er un jardin</font></html>"
      )); ajustement.add(modelisation);
    
    /* Fond transparent pour voir l'image de fond */
    ajustement.setOpaque(false);
    /* Ajustement au centre et espace entre les éléments */
    ajustement.setLayout(new GridLayout(13, 1));

    /* Actions du contrôleur sur les boutons */
    charg.addActionListener(ctrl);
    modelisation.addActionListener(ctrl);

    accueil.add(ajustement);

    /* 1ère carte du cardLayout */
    add(accueil, "Menu");
    /* Réadaptation de la fenêtre en fonction des éléments présents */
    pack();
    /* Ajoute au Cardlayout */
    affichage("Menu");
  }

  /** 
  * @see View#terrain()
  * est la m&eacute;thode permettant de visualiser un jardin,
  * ainsi que d'y faire des actions.
  */
  public void terrain(boolean charger){ 
    JPanel jardin = new JPanel();
    /* Efface le contenu pour préparer le contenu suivant. */
    jardin.removeAll();
    setResizable(true);

    JButton supp = new JButton("Supprimer Jardin");

    /* fenetre principale */
    JPanel fenetre = new JPanel();
    JTabbedPane onglet_jardin = new JTabbedPane();
    fenetre.setBackground(new Color(150, 150, 150));
    fenetre.setLayout(new BorderLayout(0, 0));
    JPanel container = new JPanel();
    container.setLayout(new BorderLayout(0, 0));
    onglet_jardin.add("Jardin " + nom.getText(), container);

    /* Barre d'option et sélection */
    JPanel option = new JPanel();
    if (charger == true)
      option.add(new JLabel(setParam()));
    else
      option.add(new JLabel(getParam()));
    option.add(liste); option.add(charg); option.add(supp);
    option.setLayout(new GridLayout(4, 1));
    option.setBackground(new Color(190, 190, 190));
    option.setBorder(new BevelBorder(BevelBorder.RAISED));
    container.add(new JScrollPane(option), BorderLayout.WEST);

    /* Création de parcelle à partir de la parcelle racine */
    ParcelleJ parcelle = new ParcelleJ(nom.getText(), 
      Integer.parseInt(longueur.getText()), 
      Integer.parseInt(largeur.getText()));
    JPanel racine = new JPanel();
    racine.setLayout(new BorderLayout(0, 0));
    /* Nouvel onglet pour le jardin et voir le détail d'une parcelle */  
    racine.setBackground(new Color(110, 110, 110));
    racine.add(new Parcelage(parcelle));
    container.add(racine, BorderLayout.CENTER);

    /* Bouton retour au menu */
    container.add(retour, BorderLayout.SOUTH);

    /* Controleur pour les actions */
    charg.addActionListener(ctrl);
    supp.addActionListener(ctrl); 
    retour.addActionListener(ctrl);

    fenetre.add(onglet_jardin);

    jardin.setLayout(new GridLayout(1, 1));
    jardin.add(fenetre);

    /* 2ème carte du CardLayout */
    add(jardin, "Terrain");
    /* Réadaptation de la fenêtre en fonction des éléments présents */
    pack();
  }

  /**
  * @see View#getParam()
  * est la m&eacute;thode permettant de relever les param&egrave;tres :
  * @param nom du jardin
  * @param longueur du jardin
  * @param largeur du jardin
  * Et g&egrave;re les erreurs d'entr&eacute;e d'arguments, avec la m&eacute;thode :
  * @see ParcelleJ#ParcelleJ(String nomJardin, int dimx, int dimy)
  */
  public String getParam() {
    String nomJardin = nom.getText();
    int dimx = Integer.parseInt(longueur.getText()), 
    dimy = Integer.parseInt(largeur.getText());

    /* Evite de créer une chaine de caractère avec que des espaces. */
    String[] tab = nomJardin.split(" ");
    String verification = "";
    for (int i=0; i<tab.length; i++) {
      if (!tab[i].equals("")){ verification += tab[i]; }
    }
    verification = verification.trim();
    nomJardin = verification;
    
    /* On fixe une longueur et hauteur entre 1000m et 20m.
    Pour éviter d'obtenir un jardin totalement disproportionné.
    On évite aussi que le nom soit une chaine vide. */
    if((nomJardin.length()==0) || ((dimx < 20) || (dimx > 1000)) 
      || ((dimy < 20) || (dimy > 1000)))
      throw new IllegalArgumentException("Problème d'argument");
    else{
      new JardinFactoryJ().AddJardin(nomJardin, dimx, dimy);
      return "<html>&nbsp; CONFIGURATION" + 
      "<br>&nbsp;- Date : " + LocalDate.now() +
      "<br>&nbsp;- Nom : " + nomJardin + " &nbsp; " +
      "<br>&nbsp;- Longueur : " + dimx + 
      "m<br>&nbsp;- Largeur : " + dimy + "m</html>";
    }
  }

  /**
  * @see View#setParam()
  * est la m&eacute;thode permettant de relever les param&egrave;tres,
  * pour les charger depuis la base de donn&eacute;es :
  */
  public String setParam() {
    String nomJardin = liste.getSelectedItem().toString();
    ConfigJardin dimJardin = new ConfigJardin(nomJardin);
    String[] dimensions = new String[dimJardin.getDimensions().size()];
    dimensions = dimJardin.getDimensions().toArray(dimensions);

    int dimx = Integer.parseInt(dimensions[0]), 
    dimy = Integer.parseInt(dimensions[1]);

    new JardinFactoryJ().AddJardin(nomJardin, dimx, dimy);
    return "<html>&nbsp; CONFIGURATION" + 
    "<br>&nbsp;- Date : " + LocalDate.now() + " &nbsp;" +
    "<br>&nbsp;- Nom : " + nomJardin +
    "<br>&nbsp;- Longueur : " + dimx + 
    "m<br>&nbsp;- Largeur : " + dimy + "m</html>";
  }
  
  /** 
  * @see View#affichage()
  * est la m&eacute;thode permettant d'afficher, avec le param&egrave;tre 
  * @param carte repr&eacute;sentant une carte du CardLayout.
  */
  public void affichage(String carte) {
    /* getContentPane() est un JPanel caché, qui contient tout les éléments de chaque fenetre. */
    diapo.show(getContentPane(), carte);
  }
} 