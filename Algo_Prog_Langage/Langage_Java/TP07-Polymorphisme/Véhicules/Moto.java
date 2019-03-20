public class Moto implements Vehicules {
	String nom;
	int nb_roue;

	Moto() {
		this.nom="Moto";
		this.nb_roue=2;
	}

	public String sorte() { return this.nom; }

	public int nbRoues() { return this.nb_roue; }
}