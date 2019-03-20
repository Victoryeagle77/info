import  javax.swing.*;
import  java.awt.*;
import  java.awt.event.*;

public class Combinaison extends JFrame implements ActionListener{
  public static boolean cyan;
  public static boolean magenta;
  public static boolean jaune;
  public static JPanel panel = new JPanel();
  public static Combinaison ctrl = new Combinaison();

  public Combinaison(){
    JFrame fenetre = new JFrame();
    fenetre.setSize(300, 300);
    fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    /* Cases à cocher */
    JCheckBox cyan = new JCheckBox("cyan");
    JCheckBox magenta = new JCheckBox("magenta");
    JCheckBox jaune = new JCheckBox("jaune");  

    panel.add(cyan);
    panel.add(magenta);
    panel.add(jaune);

    fenetre.add(panel, BorderLayout.CENTER);
    cyan.addActionListener(ctrl);
    magenta.addActionListener(ctrl);
    jaune.addActionListener(ctrl);

    fenetre.setVisible(true);
  }
  
  public void actionPerformed(ActionEvent e){
    if(e.getActionCommand()=="cyan"){
      panel.setBackground(Color.CYAN);
      if (cyan==true) { cyan=false; }
      else { cyan=true; }
    
    } else if(e.getActionCommand()=="magenta"){
      panel.setBackground(Color.MAGENTA);
      if (magenta==true) { magenta=false; }
      else {  magenta=true; }
    
    }else if(e.getActionCommand()=="jaune"){
      panel.setBackground(Color.YELLOW);
      if (jaune==true) { jaune=false; }
      else { jaune=true; }
    }

    if (cyan==false && magenta==false && jaune==false)
        panel.setBackground(Color.WHITE);
    if (magenta==true && jaune==true) 
        panel.setBackground(Color.RED);
    if (cyan==true && jaune==true) 
        panel.setBackground(Color.GREEN);
    if (magenta==true && cyan==true) 
        panel.setBackground(Color.BLUE);
    if (cyan==true && magenta==true && jaune==true) 
      panel.setBackground(Color.BLACK);
  }
  
}
 	
