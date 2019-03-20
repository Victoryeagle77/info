/*
Question 1 : Véhicules. 
Faites marcher ce programme incomplet :

import javax.swing.JOptionPane;
 
public class Test {
  public static void main(String[] args) {
    Vehicule v;
    Object[] choix = {"Voiture", "Moto"};
 
    int reponse = JOptionPane.showOptionDialog(null,
      "Quel v\u00E9hicule choisissez-vous ?",
      "Question",
      JOptionPane.DEFAULT_OPTION,
      JOptionPane.QUESTION_MESSAGE,
      null,
      choix,
      null);
    if (reponse == 0)
      v = new Voiture();
    else
      v = new Moto();
    System.out.println("Une "+v.sorte()+" poss\u00E8de "+v.nbRoues()+" roues.");
  }
}

Il n'y a pas besoin de modifier ce code ; il suffit de le placer dans un fichier nommé Test.java. 
Par contre, il ne pourra compiler que quand vous aurez écrit des définitions pour les classes Voiture et Moto ainsi que pour l'interface Vehicule.

*/

import javax.swing.JOptionPane;
 
public class Main {
  public static void main(String[] args) {
    Vehicules v;
    Object[] choix = {"Voiture", "Moto"};
    int reponse = JOptionPane.showOptionDialog(null,
      "Quel v\u00E9hicule choisissez-vous ?",
      "Question", JOptionPane.DEFAULT_OPTION,
      JOptionPane.QUESTION_MESSAGE, null, choix, null);
    if (reponse == 0) { v = new Voiture(); }
    else { v = new Moto(); }
    System.out.println("Une " + v.sorte() + " poss\u00E8de " 
      + v.nbRoues() + " roues.");
  }
}