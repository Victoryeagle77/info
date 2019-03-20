/*
Question 5 : Nuancier. 
On souhaite écrire une application qui se comporte comme un nuancier : elle permet de voir des couleurs côte à côte.

Pour cela, nous allons commencer par définir un composant graphique spécialisé nommé Nuance. 
Celui-ci devra avoir une taille préférée de 100 pixels de large par 100 pixels de haut, 
et devra indiquer les composants RVB de sa couleur de fond dans sa partie haute. De quelle classe pouvez-vous hériter ?

Écrivez une application qui prend une liste de couleurs sur la ligne de commande (au format #RRVVBB) 
et qui affiche ces couleurs horizontalement à l'aide du composant défini plus haut.

bob@box:~$ java Nuancier "#88E900" "#0088E9" "#E90088"

! Remarque ! 
Pour que la fenêtre prenne une taille adaptée à son contenu plutôt qu'une taille arbitraire, 
utilisez la méthode pack à la place de la méthode setSize. */


import javax.swing.*;
import java.awt.*;

public class Main {
	public static void main(String[] args) {
		if(args.length != 3){
			System.err.print("Usage : ");
			for(int i=0; i<3; i++)
				System.err.print("'<#0x000000>' ");
			System.out.print("\n");
			return;
		}
		Nuance fenetre = new Nuance();
		fenetre.setSize(10*args.length + 100*args.length, 150);
		fenetre.setLocation(100,100);
		GridLayout gestionnaire = new GridLayout(1,args.length);
		fenetre.setLayout(gestionnaire);
		fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		for (int i=0; i<args.length; i++)
			fenetre.add(Nuance.Palette(args[i]));

		fenetre.setVisible(true);
	}
}