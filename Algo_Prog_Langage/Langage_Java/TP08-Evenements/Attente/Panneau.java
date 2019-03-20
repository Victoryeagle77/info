import javax.swing.*;
import java.awt.*;

public class Panneau extends JPanel{

    public Panneau(){ super(); }
    @Override
    public void paintComponent(Graphics p){
        Graphics graph = p.create();
        /* couleur de fond */
        graph.setColor(Color.GREEN);
        graph.fillRect(0,0,this.getWidth(),this.getHeight());
        graph.setColor(new Color(255,0,255));
        graph.fillOval(this.getWidth()/4,this.getHeight()/4,this.getWidth()/2,this.getHeight()/2);
    }

    public void cercle(Graphics composant){
        int hauteur = this.getHeight();
        int largeur = this.getWidth();
        Graphics graph = composant.create();
        graph.setColor(Color.GREEN);
        graph.fillRect(0,0,largeur,hauteur);
        int x[] = {0, largeur, largeur/2,largeur/2, 0, largeur};
        int y[] = {0, 0, hauteur/2, hauteur/2, hauteur, hauteur};
        sablier(composant, x, y, 6);
    }
    public void sablier(Graphics p, int[] x, int[] y, int nbr){
	    Graphics graph = p.create();
	    graph.setColor(new Color(0,255,255));
	    graph.fillPolygon(x,y,nbr);
    }
}
