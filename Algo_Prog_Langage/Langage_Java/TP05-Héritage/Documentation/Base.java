/*
Faites un programme qui converti un entier donné en base 8, en base 16.
*/

public class Base {
  public static void main(String[] args) {
    int x = 0;
    if (args.length < 1) return;
    for (int i=0; i<args.length; i++) {
      x = Integer.parseInt(args[i], 8);
      System.out.println(Integer.toHexString(x));
    }
  }
}