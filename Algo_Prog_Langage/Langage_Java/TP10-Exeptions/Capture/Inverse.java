/* Question 1 : Capture

Faite un programme levant une ArithmeticException. 
Mettez l'instruction responsable de l'exception dans une autre méthode que main, 
et invoquez cette méthode dans le main. Qu'est-ce qui change lors de l'exécution ?

Ajoutez dans la méthode secondaire un bloc try...catch pour capturer l'exception et afficher un message d'erreur de votre choix.

Enlevez ensuite le bloc try...catch de la méthode secondaire, et placez-le dans le main de façon à tout de même capturer l'exception. 
Qu'est-ce que ça change ? */

import java.awt.*;

public class Main{
    public static double Main(double n){
		/* On produit ici l'exception arithmétqiue de la division 0 */
		try{ n = 1/n; } 
		catch (ArithmeticException e) {
	    	System.err.println("Pas de fonction inverse");
		}
		return n;
    }
   
    public static void main(String[] args){
		double n = Integer.parseInt(args[0]);
		n = Main.Main(n);
		System.out.println(n);
    }
}

/* En enlevant le bloc try...catch, on constate que lorsqu'il s'agit de 0,
Il affiche également "infinity" avec un double, mais une erreur avec un int. */