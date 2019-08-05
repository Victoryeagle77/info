/*
Question 3 : Accueil. 
Une interface graphique est souvent améliorée par le travail d'un graphiste. 
Cette image vous donne la base d'un écran d'authentification. 
Concevez une application qui ouvre une fenêtre ayant l'apparence imposée et dans laquelle on peut entrer ses identifiants. 
*/

import javax.swing.JFrame;
import java.awt.*;
import javax.swing.*;

public class Main {
  public static void main(String[] args) {
    JFrame fenetre = new JFrame();
    fenetre.setLayout(null);
    fenetre.setSize(280,210);
    fenetre.setLocation(0,0);
    fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    fenetre.setContentPane(new accueil());
        
    JTextField Login = new JTextField();
    JTextField Password = new JTextField();
        
    Login.setBackground(Color.WHITE);
    Login.setLocation(120,100);
    Login.setSize(120,25);
    Password.setLocation(120,140);
    Password.setSize(120,25);
    fenetre.add(Password);
    fenetre.add(Login);
    fenetre.setVisible(true);
  }
}