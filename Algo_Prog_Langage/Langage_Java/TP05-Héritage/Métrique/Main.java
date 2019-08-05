/*
Question 3 : Métrique. 
La classe Paper sert à représenter la géométrie d'une feuille de papier (dans le but de faire des impressions). 
Malheureusement, cette classe utilise le système impérial obsolète pour toutes ses mesures.

  ° Écrivez la définition d'une classe dérivée de Paper, 
  dont le constructeur sans argument crée une feuille au format A4 avec une marge de 1,5cm de chaque coté.
  ° Ajoutez une méthode getMetric... pour chaque méthode get..., 
  utilisant les millimètres plutôt que les 1/72ème de pouce.
  ° Idem pour les méthodes set....
  ° Testez votre travail à chaque étape par un court programme !
*/

public class Main {
  public static void main(String[] args) {
    Papier paper = new Papier();
    System.out.println(paper);
  }
}