public class Periode {
  // attribut
  private int jour;
  private int mois;
  private int annee;
  private int interval;

  public Periode(int a, int m, int j, int i) {
    this.jour=j;
    this.mois=m;
    this.annee=a;
    this.interval=i;
  }
  
  public void augmenter() { this.interval++; }

  public void ajouter() {
    this.jour++;
    if (this.jour>31) {
      this.jour=1;
      this.mois++;
      if (this.mois>12) {
        this.mois=1;
        this.annee++;
      }
    }

  }

  public String toString() {
    String dure;
    Periode periode = new Periode(this.annee,this.mois,this.jour,this.interval);

    for (int i=0; i<this.interval; i++) { periode.ajouter(); }

    dure = "Votre période va du ";
    dure += Integer.toString(this.annee) + "/" + 
    Integer.toString(this.mois) + "/" + Integer.toString(this.jour);
    dure += " au ";
    dure += Integer.toString(periode.annee) + "/" + 
    Integer.toString(periode.mois) + "/" + Integer.toString(periode.jour);
    dure += ".";
    return dure;
  }
}