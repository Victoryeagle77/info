public class Moyenne {
	
	private double somme;
	private int nombre;

	Moyenne() {
		this.somme=0;
		this.nombre=0;
	}

	public void add(Number nombre) {
		this.somme+=nombre.doubleValue();
		this.nombre++;
	}

	public Number getAverage() {
		return this.somme/this.nombre;
	}
}