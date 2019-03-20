/*
Question 2 : Arguments. 
Le paramètre args de la méthode principale contient tous les arguments donnés à l'exécution du programme (après le nom de la classe). 
Écrivez une application qui reçoit sur sa ligne de commande une liste de noms et qui salue chacune des personnes citées.

bob@box:~$ java Bonjour Denis Luc Pierre
Bonjour Denis
Bonjour Luc
Bonjour Pierre
*/

public class arguments {
  public static void main(String[] args) {
  	if(args.length == 0){
  		System.err.println("Usage : <String>");
  		System.exit(0);
  	}
    for(int i = 0; i < args.length; i++)
  	  System.out.println("Bonjour " + args[i]);
	}
}