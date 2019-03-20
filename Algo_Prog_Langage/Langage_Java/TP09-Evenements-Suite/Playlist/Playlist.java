import javax.swing.*;
import java.awt.*;

public class Playlist extends JFrame {
	JPanel fond;
	JLabel[] etiquette;
	boolean[] selection;
	int playlist, cyan, gris;

	public Playlist(String titre, String[] tab) {
		super(titre);
		this.cyan =- 1;
		this.gris =- 1;
		this.playlist = tab.length;
		this.setSize(300, this.playlist*50);
		this.setLocation(300, 100);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setResizable(false);

		this.selection = new boolean[playlist];
		
		for (int i=0; i<this.playlist; i++)
			this.selection[i] = false;
		
		this.fond = new JPanel();
		this.etiquette = new JLabel[this.playlist];
		this.fond.setLayout(new GridLayout(this.playlist, 1));
		
		for (int i=0; i<this.playlist; i++) {
			etiquette[i] = new JLabel("   " + tab[i]);
			etiquette[i].setOpaque(true);
			fond.add(etiquette[i]);
		}
		Actions action = new Actions(this);
		this.fond.addMouseMotionListener(action);
		this.addKeyListener(action);
		this.fond.addMouseListener(action);
		this.setFocusTraversalKeysEnabled(false);

		this.add(fond);
	}

	public void changeCyan(int y) {
		int c = y/50;
		if (c != this.cyan) {
			this.cyan=c;
			this.redessiner();
		}
	}

	public void changeGrey(int y) {
		double x = (double)this.getHeight()
		/ (double)(this.playlist);
		int g = (int)(y/x);
		if (g != this.gris) {

			for (int i=0; i<this.playlist; i++)
				this.selection[i]=false;

			this.gris=g;
			this.selection[this.gris]=true;
			this.redessiner();
		}
	}

	public void ajouterGrey(int y) {
		int g = y/50;
		if (this.selection[g]) {
			this.selection[g]=false;
			this.gris=g;
			this.etiquette[g].setForeground(Color.BLACK);
		} else {
			this.selection[g]=true;
			this.gris=g;
			this.etiquette[g].setForeground(Color.BLUE);
		}
	}

	public void redessiner() {
		for (int i=0; i<this.playlist; i++) {
			if (this.selection[i]) {
				this.etiquette[i].setBackground(new Color(150,150,150));
				this.etiquette[i].setForeground(Color.BLUE);
			} else {
				this.etiquette[i].setBackground(new Color(230,230,230));
				this.etiquette[i].setForeground(Color.BLACK);
			}
		}
		this.etiquette[this.cyan].setBackground(Color.CYAN);
	}
}