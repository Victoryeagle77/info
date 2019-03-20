import java.awt.print.Paper;

public class Papier extends Paper {	
	
	private int longueur;
	private int hauteur;
	private int margin_x;
	private int margin_y;

	public Papier() {
		super();
		// 1,5cm = 15 mm et le Format A4 standard est 210 x 297
		setMetricImageableArea(15,15,210,297);
	}
	
	public Papier(int marge_x, int marge_y, int l, int h) {
		super();
		setMetricImageableArea(marge_x,marge_y,l,h);
	}

	public int getMetrichauteur() { return this.hauteur; }

	public int getMetriclongueur() { return this.longueur; }

	public int getMetricImageablelongueur() { 
		return this.longueur - this.margin_x; 
	}

	public int getMetricImageablehauteur() { 
		return this.hauteur - this.margin_y; 
	}

	public int getMetricImageableX() { return this.margin_x; }

	public int getMetricImageableY() { return this.margin_y; }

	public void setMetricImageableTaille(int l, int h) {
		this.longueur=l;
		this.hauteur=h;
	}

	public void setMetricImageableArea(int marge_x, int marge_y,
	 int l, int h) {
		this.margin_x = marge_x;
		this.margin_y = marge_y;
		this.longueur = l;
		this.hauteur = h;
	}

	public String toString() {
		return "° Longueur = " + this.longueur + "\n° Hauteur = " + 
		this.hauteur + "\n° Marge_x = " + this.margin_x + 
		"\n° Marge_y = " + this.margin_y + "\n° Taille en longueur imageable = " + 
		this.getMetricImageablelongueur() + "\n° Taille en hauteur imageable = " + 
		this.getMetricImageablehauteur();
	}

}