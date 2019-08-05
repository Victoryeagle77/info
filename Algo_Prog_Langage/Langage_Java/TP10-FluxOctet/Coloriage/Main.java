/*
Question 2 : Coloriage. 
Écrivez une application qui prend une couleur sur la ligne de commande,
et génère un fichier image au format décrit au premier exercice,
et dont tous les pixels sont de la couleur donnée.

bob@box:~$ java Coloriage #88E900

Modifiez ensuite cette application pour que l'on puisse lui passer une seconde couleur en ligne de commande, 
auquel cas le fichier généré contiendra un damier de huit lignes et huit colonnes alternant les deux couleurs.
*/

import java.io.*;
import javax.swing.*;
import java.awt.*;

public class Main{
  public static void main(String[] args){

    if(args.length != 3) {
      System.err.print("Usage : ");
      for(int i=0; i<3; i++)
        System.err.print("'<#0x000000>' ");
      System.out.print("\n");
      return;
    }

    Color couleur = Color.decode(args[0]);
    JFrame fenetre = new JFrame();
    JPanel panneau = new JPanel();

    fenetre.setSize(300, 300);
    fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    fenetre.setLocationRelativeTo(null);

    panneau.setBackground(couleur);
    fenetre.add(panneau);
    fenetre.setVisible(true);

    BufferedWriter arg = null; 

    try {
      arg = new BufferedWriter(new FileWriter("coloriage.bin"));
      for(int i=0; i<4; i++){
        for(int j=0; j<4; j++)
          arg.write(args[i] + " ");
      }
    } catch(IOException e) {
      System.err.println("Erreur de fermeture : " + e.getMessage());
    }
    /* finally dans la méthode nettoie puis ferme le FileWriter */
    finally{
      try{
        if(arg != null) { arg.close(); }
      } catch (IOException e) {
        System.err.println("Erreur de fermeture : " + e.getMessage());
      }
    }
  }
}