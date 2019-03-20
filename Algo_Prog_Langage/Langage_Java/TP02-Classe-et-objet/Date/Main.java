/*
Question 2 : Date. 
Supposons qu'un projet nécessite la création d'une classe pour représenter une date au jour près 
(il existe déjà plusieurs classes similaires en Java, mais nous ne souhaitons pas les employer). 
Pour commencer, définissez une telle classe en prévoyant un constructeur et une méthode toString qui renvoie une chaîne décrivant la date au format ISO 8601 (AAAA-MM-JJ). 
Testez votre classe avec un programme simple. 
*/

public class Main {
	public static void main(String[] args) {
		if(args.length == 0){
			System.err.println("Usage : <annee>/<mois>/<jour>");
			System.exit(0);
		}
		int year = Integer.parseInt(args[0]);
		int month = Integer.parseInt(args[1]);
		int day = Integer.parseInt(args[2]);

		Date date = new Date(year,month,day);
		Date lendemain = new Date(0,0,0);
		
		System.out.println("Date actuelle = " + date.toString());
		System.out.println("Date du jours suivant = " + date.ajouter());
		if (date.strcmp_methode(lendemain) == true)
			System.out.println(date.toString()+ " et " 
				+ lendemain.toString() + " sont la même date");
			// if (strcmp(date, lendemain) == true) { Vrai; } else { Faux; }
	}
}