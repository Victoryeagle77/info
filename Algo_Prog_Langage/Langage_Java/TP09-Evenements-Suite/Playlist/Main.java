/* Question 3 : Multiple. 
On souhaite créer une playlist en permettant de sélectionner plusieurs morceaux à la fois. 
Si on clique sur un morceau en maintenant la touche «Contrôle» enfoncée, 
le morceau doit être ajouté à la sélection (ou retiré de la sélection s'il en fait déjà partie). */

public class Main {
  public static void main(String[] args) {
    String[] titre = {
      "Dreaming in the Daylight", 
        "Just Keep on living",
        "Stand Alone",
        "I'm Dangerous",
        "Man of Fire",
        "Legendary",
        "Still holding on",
        "Chosen ones",
        "Night of your life",
        "Eyes of Storm"
    };
    Playlist fenetre = new Playlist("Playlist [EPICK ROCK]", titre);
    fenetre.setVisible(true);
  }
}