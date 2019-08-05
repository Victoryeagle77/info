/*
Question 2 : Moyenne. 
On désire concevoir une classe qui puisse calculer la moyenne d'une collection hétéroclite de valeurs. 
On imagine une méthode add pour ajouter une valeur, 
et une méthode getAverage pour obtenir la moyenne des valeurs données jusque là. 
Le problème est que les valeurs peuvent appartenir à n'importe quel type primitif parmi byte, 
short, int, long, float et double.

  a) La solution la plus simple consiste à exploiter la surcharge.
  Définissez la classe demandée en fournissant une version différente de la méthode add pour chaque type possible.
  b) La première solution est longue à écrire, et nécessite une évolution si on ajoute un nouveau type à la liste. 
  Nous allons profiter du fait que tous les valeurs d'un type primitif peuvent être transformées en objets, 
  et que les classes de ces objets héritent toutes de la classe abstraite Number. 
  Modifiez la définition de la classe précédente pour qu'il n'y ait plus qu'une seule version de la méthode add.
*/

public class Main {
  public static void main(String[] args) {
    if(args.length < 0){
      System.err.println("Usage : <int> ++");
      System.exit(0);
    }
    Moyenne moyenne = new Moyenne();
    for(int i=0; i<args.length; i++)
      moyenne.add(Integer.parseInt(args[i]));
    System.out.println(moyenne.getAverage());
  }
}