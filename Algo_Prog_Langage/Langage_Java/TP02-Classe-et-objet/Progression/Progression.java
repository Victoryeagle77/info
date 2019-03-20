/*
Question 1 : Progression. 
Utilisez la classe Compteur pour écrire un programme qui affiche les entiers de 5 à 9 en binaire.
*/

public class Progression {
  public static void main(String[] args) {
    Compteur compte = new Compteur();

    for (int i=0; i<=9; i++) {
    if(i>=5)
       System.out.println(i + " = " + compte.toString());
      compte.plusUn();
    }
  }
}