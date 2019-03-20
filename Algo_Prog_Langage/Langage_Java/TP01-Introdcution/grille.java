/* Question 5 :  Grille. 
Écrivez un programme qui affiche une grille dont la taille est donnée sur la ligne de commande.

bob@box:~$ java Grille 2
+-+-+
| | |
+-+-+
| | |
+-+-+
*/

public class grille {
	public static void main(String[] args) {
		if (args.length==0) {
			System.err.println("Usage: <entier>");
			System.exit(0);
		}
		int taille = Integer.parseInt(args[0]);
		System.out.print("+");
		
		for (int i=0; i<=taille; i++) 
			System.out.print("-+");

		System.out.println(" ");
		
		for (int i=0; i<taille; i++) {
			System.out.print("|");
			for (int j=0; j<taille+1; j++) 
				System.out.print(" |");
			System.out.println("");
			System.out.print("+");
			for (int j=0;j<taille+1; j++)
				System.out.print("-+");
			System.out.println("");
		}
		
	}
}