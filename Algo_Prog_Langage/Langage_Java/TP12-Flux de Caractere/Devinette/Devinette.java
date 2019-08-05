import java.io.*;
import java.util.Random;

public class Devinette {
  public static void main(String[] args) {
    System.out.println("Entrer un nombre entre 0 et 100");
    Random valeur = new Random(); /* Méthode Random() */
    int nombre = valeur.nextInt(100); /* Méthode nextInt() avec la valeur aléatoire 
    de la méthode Random() entre 0 et 100 */
    String proposition; 
    int nombre_essai, i=5;
    BufferedReader flux = new BufferedReader(new InputStreamReader(System.in)); 
    /* Méthode BufferedReader() qui saisie un flux de donné au clavier
    InputStreamReader(System.in) permet de lire les caractères un à un saisie par le clavier */ 
    while(i!=0){
      i--;
      try{
        proposition = flux.readLine();
        nombre_essai=Integer.parseInt(proposition); /* Réalise une variable ou est converti en entier
        la chaine de caractère String "proposition" */	   
        if(nombre_essai!=nombre){ /* Si le nombre d'essai n'est pas égale au nombre aléatoire */
          System.out.println("Indice : ");
          if(nombre_essai>nombre){ System.out.println("-"); }
          else{ System.out.println("+"); }
        }
        if(nombre_essai==nombre)
          System.out.println("Trouvé, il s'agissait bien de " + nombre);	
      }
      catch(IOException e){
        System.err.println(e.getMessage());
      };
    }
    System.out.println("La valeur exacte était " + nombre);	
  }
}