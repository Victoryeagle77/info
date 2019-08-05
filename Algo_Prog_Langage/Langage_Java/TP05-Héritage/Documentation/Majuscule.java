/*
Écrivez un programme qui affiche tous les argument de sa ligne de commande, convertis en majuscules. 
Trouvez dans la classe String de quoi vous simplifier le travail. 
*/

public class Majuscule {
  public static void main(String[] args) {
    if (args.length < 1){
      System.err.println("Usage : <chaine>");
      return;
    }
    for (int i=0; i<args.length; i++) {
      System.out.println(args[i].toUpperCase());
    }
  }
}