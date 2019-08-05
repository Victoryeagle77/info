/*
Question 4 : Période. 
En vous appuyant sur la classe des deux exercices précédents, 
définissez une classe qui réprésente un intervalle de temps (au jour près). Prévoyez :

  ° un constructeur,
  ° une méthode toString,
  ° une méthode qui prolonge la période d'une journée,
  ° une méthode qui renvoie le nombre de jours contenus dans l'intervalle.
*/
    
public class Main {
  public static void main(String[] args) {
    if(args.length == 0){
      System.err.println("Usage : <annee>/<mois>/<jour>/<periode>");
      System.exit(0);
    }
    int year = Integer.parseInt(args[0]);
    int month = Integer.parseInt(args[1]);
    int day = Integer.parseInt(args[2]);
    int interval = Integer.parseInt(args[3]);
    
    Periode date = new Periode(year,month,day,interval);
    System.out.println(date);
  }
}