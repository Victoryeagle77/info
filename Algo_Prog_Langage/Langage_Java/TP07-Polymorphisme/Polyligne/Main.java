/*
Question 3 : Polyligne.
Écrivez un programme qui ouvre une fenêtre affichant une polyligne : 
une ligne brisée reliant une suite de points.

Ce programme est un consommateur : il ne peut pas fonctionner sans qu'on 
lui donne les coordonnées des points à relier. 
Nous allons donc devoir lui fournir un service qui remplit ce besoin. 
Les termes de ce service sont explicités sous la forme d'une interface :

import java.awt.Point;
 
public interface ProducteurDePoints {
  Point suivant();
}

Chaque appel à la méthode suivant fournira le point suivant à relier, 
jusqu'à ce qu'il n'y ait plus de point, auquel cas la méthode renvoie null. 
Après cela, l'objet est réinitialisé et les prochains appels à suivant 
donneront à nouveau la suite des points depuis le début.

Pour vous aider à écrire le programme, voici un fournisseur possible pour ce service :

import java.awt.Point;
 
public class Etoile implements ProducteurDePoints {
  private static final int xCentre = 100;
  private static final int yCentre = 100;
  private static final double rayon = 90.0;
  private static final double angleDepart = Math.PI/4.0;
  private static final double angleIncrement = (4.0*Math.PI)/5.0;
  private double numero;
  public Etoile() {
    this.numero = 0.0;
  }
  public Point suivant() {
    Point p = null;
    if (this.numero < 6.0) {
      double angle = Etoile.angleDepart+this.numero*Etoile.angleIncrement;
      p = new Point((int) (Etoile.rayon*Math.cos(angle)),
                    (int) (Etoile.rayon*Math.sin(angle)));
      p.translate(Etoile.xCentre, Etoile.yCentre);
      this.numero++;
    } else {
      this.numero = 0.0;
    }
    return p;
  }
}

Une fois que votre programme sera opérationnel, 
remplacez le fournisseur par votre propre version qui produira des points décrivant une spirale.

! Remarque ! 
Cette substitution ne devrait nécessiter que de changer un seul mot dans la méthode principale du programme.
*/

import javax.swing.*;
import java.awt.*;

public class Main {
  public static void main(String[] args) {
    if(args.length != 1){
      System.err.println("Usage : <int [0 - 5]>");
      System.exit(0);
    }
    Polyligne test = new Polyligne(new Etoile(), Integer.parseInt(args[0]));
    JFrame fenetre = new JFrame();
    fenetre.setSize(200, 200);
    fenetre.setLocation(100, 100);
    fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    fenetre.add(test);
    fenetre.setVisible(true);
  }
}