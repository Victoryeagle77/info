import javax.swing.*;
import java.awt.event.*;
import java.awt.*;

/**
* @author Arthur Chenu
* @version final
*/

/**
* La classe <code>Action</code>
* permet de g&eacute;rer les interactions &agrave; la souris, 
* et les &eacute;venements qui doivent suivre sur les activations d&eacute;finis dans la classe :
* @see View 
*/
public class Action implements ActionListener {
  View vue;
  private Model mod;
  private int[][] cases;
  private int taille;
    
  /**
  * @see Action#Action(View vue, Model mod)
  * Permet de cr&eacute;er des constructeurs r&eacute;utilisables pour la classe :
  * @see <code>View</code>
  */
  public Action(View vue, Model mod) {
    this.vue = vue;
    this.mod = mod;
  }
    
  /**
  * @see Action#getData(String chemin)
  * @return taille
  * D&eacute;dinie dans par : 
  * @see Model#getSize()
  * Dans les donn&eacute;es d'un fichier r&eacute;cup&eacute;r&eacute; avec :
  * @param chemin
  */
  public int getData(String chemin) {
    this.cases = mod.charge_config(chemin);
    this.taille = mod.getSize();
    return taille;
  }

  /**
  * @see Action#actionPerformed(ActionEvent e)
  * E&eacute;cup&egrave;re les chaines de caract&eacute;res de 
  * @see View#View()
  * On utilise equals(String) pour comparer les chaines de caract&egrave;re,
  * Avec celles pr&eacute;sente dans les JButton.
  * On d&eacute;finit ainsi les activations qui doivent suivre.
  */
  public void actionPerformed(ActionEvent e) {
        
    /* Relevé de l'activation d'un bouton */
    JButton activation = (JButton)e.getSource();

    /* Selection du labyrinthe à résoudre */
    if(activation.getText().equals("Construire un labyrinthe"))
      vue.construire_labyrinthe();
    else if(activation.getText().equals("Charger un labyrinthe"))
      vue.charger_labyrinthe();
    else if(activation.getText().equals("Quitter"))
      System.exit(0); /* bouton quitter */
        
    /* Mod construction */
    else if(activation.getText().equals("Construction"))
      new Build(400, 400).setVisible(true);

    /* Mod de résolution */
    else if (activation.getText().equals("Mod aleatoire"))
      vue.visuel_resolution(true);
    else if (activation.getText().equals("Automate Deterministe"))
      vue.visuel_resolution(false);

    /* Mod de visionnage de la résolution */
    else if (activation.getText().equals("Visuel automatique"))
      vue.affichage_automatique(cases, true);
    else if (activation.getText().equals("Visuel manuel"))
      vue.affichage_automatique(cases, false);
  }
}