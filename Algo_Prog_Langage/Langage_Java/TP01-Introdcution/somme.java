/*
Question 3 : Somme. 
Écrivez une application qui prend une liste d'entiers sur la ligne de commande et affiche leur somme. 
Pour cela, il va falloir transformer les arguments (qui sont des objets de la classe String) en int. 
On utilise une méthode de classe (une méthode qui ne s'applique pas à un objet mais à la classe elle-même).

String nombre = "27";
int n = Integer.parseInt(nombre); // n vaut 27
*/

public class somme {
  public static void main(String[] args) {
    int i, n=0;
    if(args.length < 1) {
      System.err.println("Usage : <entier> ++");
      System.exit(0);
    }
    for (i=0;i<args.length ;i++ )
      // Conversion des arguments en ligne de commande en entier
      n += Integer.parseInt(args[i]);
    System.out.println(n);
  }
}