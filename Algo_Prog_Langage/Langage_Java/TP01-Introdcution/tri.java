/*
Question 4 : Tri. 
Reprenez le programme de l'exercice précédent, et au lieu d'afficher la somme, affichez la liste des entiers en ordre croissant. 
Une autre méthode de classe va vous y aider : la méthode sort de la classe Arrays.

Arrays.sort(tab); // trie le tableau tab par ordre croissant

La classe Arrays fait partie d'une bibliothèque (en Java on dit un package) qu'il faut inclure. 
Il suffit pour cela d'ajouter au tout début du fichier source la ligne suivante :

import java.util.Arrays;
*/

import java.util.Arrays;

public class tri {
  public static void main(String[] args) {
    int i;
    if(args.length < 1) {
      System.err.println("Usage <entier> ++");
      System.exit(0);
    }
    int tab[]=null;
    // Création d'un tableau d'entier selon la chaine de caractère des arguments entrés
    tab = new int[args.length];
    for(i=0; i<args.length; i++){
      tab[i] = Integer.parseInt(args[i]);
    }
    Arrays.sort(tab);
    System.out.println(Arrays.toString(tab));
  }
}