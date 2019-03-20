/*
Question 2 : Attente. 
Écrivez une application qui ouvre une fenêtre contenant un disque magenta sur fond vert. 
Lorsque la fenêtre est en arrière-plan, le cercle doit être remplacé par un sablier. 
*/

import javax.swing.*;
import java.awt.*;

public class Main{
    public static void main(String args[]){
        Attente fenetre = new Attente();
        fenetre.setSize(500,500);
        fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        fenetre.setVisible(true);
    }
}
