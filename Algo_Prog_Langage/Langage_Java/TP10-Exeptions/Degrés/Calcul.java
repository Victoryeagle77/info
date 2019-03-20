public class Calcul {
  
  private double temp;
  public String toString(){
    return (this.temp);
  }
  public double Fahrenheit(double x){
    this.temp=x;
    return ((double)9/(double)5)*x-(double)32;
  }

  public double Cellcus(double x){
    this.temp=x;
    return ((x-(double)32)*(double)5)/(double)9;
  }

}