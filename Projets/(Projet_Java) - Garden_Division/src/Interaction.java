package src;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

/** 
* La classe <code>Interaction</code> permet de d&eacute;terminer les &eacute;venements,
* et les li&eacute;s au fait de passer de panel en panel sur la meme fenetre.
*/
public class Interaction extends JButton implements ActionListener{
  private View vue;

  /** 
  * @see Interaction#Interaction(View v)
  * est la m&eacute;thode qui prend en param&egrave;tre
  * @param v de type View,
  * pour permettre d'indiquer la carte actuelle, 
  * suivante et pr&eacute;c&eacute;dente du cardLyout
  */
  public Interaction(View v){ this.vue = v; }

  /** 
  * @see actionPerformed(ActionEvent e)
  * est la m&eacute;thode qui prend en param&egrave;tre
  * @param e de type ActionEvent,
  * pour interpréter le clique de souris sur un bouton et ainsi d&eacute;finir, 
  * &agrave; partir de la chaine de caract&egrave;re de celui-ci,
  * l'action qui doit s'effectuer.
  */
  public void actionPerformed(ActionEvent e){
    /* Relevé de l'activation d'un bouton */
    JButton activation = (JButton)e.getSource();
    /* Si le bouton contenant la chaine "Modéliser" est cliqué */
    if(e.getActionCommand().equals("Mod\u00e9liser")){
      /* Création du jardin dans la base de donnée */
      new Creation(vue.nom.getText(), Integer.parseInt(vue.longueur.getText()),
        Integer.parseInt(vue.largeur.getText()));
      vue.liste.addItem(vue.nom.getText());
      vue.terrain(false); /* Affiché l'éditeur de parcelle */
      vue.affichage("Terrain"); /* Afficheur de carte du cardLayout */
    }else if (e.getActionCommand().equals("Supprimer Jardin")){
      String supp = vue.liste.getSelectedItem().toString();
      if (supp != vue.nom.getText()){
        Suppression suppr = new Suppression(supp);
        vue.liste.removeItem(supp);
      }else
        System.out.println("Suppression Impossible !");
    /* Retour au menu */
    }else if(e.getActionCommand().equals("Retour"))
      vue.depart();
    /* Charger un jardin */
    else if(e.getActionCommand().equals("Charger jardin")) {
      vue.terrain(true);
      vue.affichage("Terrain"); 
    }
  }
}