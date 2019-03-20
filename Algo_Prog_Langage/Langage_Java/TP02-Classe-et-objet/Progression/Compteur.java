public class Compteur {
  // attribut
  private int compte;
  // méthode
  public void plusUn() { this.compte++; }
  // autre méthode
  public String toString() {
    return Integer.toBinaryString(this.compte);
  }
}