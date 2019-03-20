/*
Question 4 : Choix.
Écrivez un programme qui ouvre une fenêtre contenant trois boutons radio les uns au-dessus des autres, nommés «Gryffondor», «Serdaigle» et «Serpentard». 
Vous pourrez constater que les boutons peuvent être sélectionnés ou déselectionnés à volonté.

En général on utilise les boutons radio pour proposer des options mutuellement exclusives, ce qui veut dire qu'il devrait être impossible de sélectionner plus d'un bouton à la fois. 
La classe ButtonGroup sert à représenter un ensemble de boutons radios qui doivent se coordonner entre eux. 
Son constructeur ne prend pas d'argument. Elle contient une méthode add qui prend un JRadioButton en argument et sert à lui faire rejoindre le groupe. 
*/

import javax.swing.*;
import java.awt.*;

public class Choix {

  public static void main(String[] args) {
    JFrame fenetre = new JFrame();

    fenetre.setSize(500,300);
    fenetre.setLocation(100,100);
    fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    // Bloquer une taille minimale 
    fenetre.setMinimumSize(new Dimension(500,100));

    JRadioButton bouton_1 = new JRadioButton("Gryffondor");
    JRadioButton bouton_2 = new JRadioButton("Serdaigle");
    JRadioButton bouton_3 = new JRadioButton("Serpentard");
    JRadioButton bouton_4 = new JRadioButton("Poufsouffle");

    ButtonGroup groupe = new ButtonGroup();
    groupe.add(bouton_1);
    groupe.add(bouton_2);
    groupe.add(bouton_3);
    groupe.add(bouton_4);

    JPanel panneau = new JPanel();
    panneau.add(bouton_1);
    panneau.add(bouton_2);
    panneau.add(bouton_3);
    panneau.add(bouton_4);

    fenetre.add(panneau,BorderLayout.NORTH);

    fenetre.setVisible(true);
  }
}

