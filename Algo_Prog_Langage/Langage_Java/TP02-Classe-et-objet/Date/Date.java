public class Date {
  // Attribut
  private int jour;
  private int mois;
  private int annee;

  public Date(int a, int m, int j) {
  	this.jour=j;
  	this.mois=m;
  	this.annee=a;
  }
  
  public String toString() {
    return Integer.toString(this.annee) + "-" + 
    Integer.toString(this.mois) + "-" + Integer.toString(this.jour);
  }

  public String ajouter() {
  	Date date = new Date(this.annee, this.mois, this.jour);
  	date.jour++;
  	if (jour>30) {
  		date.jour=0;
  		date.mois++;
  		if (date.mois>12) {
  			date.mois=1;
  			date.annee++;
  		}
  	}
  	return date.toString();
  }

  public boolean strcmp_methode(Date date) {
  	if (date.annee == this.annee) {
  		if (date.mois == this.mois) {
  			if (date.jour == this.jour) { return true; }
  		}
  	}
  	return false;
  }
}