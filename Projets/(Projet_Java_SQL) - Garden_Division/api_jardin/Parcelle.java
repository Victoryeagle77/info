package api_jardin;
import java.util.*;
import java.time.*;

/**
* Classe <code>Parcelle</code>
* Interface principale de l'API
* Explicite les méthodes permettant de gérer les parcelles (taille, structure, navigation)
* et les actions sur ces dernières.
*/
public interface Parcelle{

    /**
    * @return un itérateur sur les actions réalisées,
    * sur la parcelle mais pas sur une ancêtre de celle-ci.
    */
    public Iterator<Action> getActions();

    /**
    * @return un itérateur sur les actions vraiment réalisées sur la parcelle 
    */
    @SuppressWarnings("unchecked")
    public Iterator<Action> getAllActions();
    
    /**     
    * ajoute une action à la parcelle.
    */
    public void addAction(Action a);
    
    /**
    * @return le type de split de la parcelle null si pas de sous-parcelle
    */
    public Orientation getSplit();

    /**
    * @return la sous parcelle gauche (si split vertical) ou haute (si split horizontal).
    * IllegalStateException si la parcelle n'a pas de sous-parcelle
    */
    public Parcelle getFirst();

    /**
    * @return la sous parcelle droite (si split vertical) ou basse (si split horizontal).
    * IllegalStateException si la parcelle n'a pas de sous-parcelle
    */
    public Parcelle getSecond();

    /**
    * réunit les sous-parcelles (on oublie les sous-parcelles)
    */
    public void reset();
    
    /**
    * @return la parcelle mère de la parcelle
    */
    public Parcelle getMother();

    /**
    * @return la parcelle racine de la parcelle
    */
    public Parcelle getRoot();

    /**
    * @return l'abscisse du coin en haut à gauche de la parcelle
    */
    public int getx0();
    
    /**
    * @return l'ordonnée du coin en haut à gauche de la parcelle
    */
    public int gety0();
    
    /**
    * @return l'abscisse du coin en bas à droite de la parcelle
    */
    public int getx1();
    
    /**
    * @return l'ordonnée du coin en bas à droite de la parcelle
    */
    public int gety1();
    
    /**
    * @return le nom du jardin de la parcelle
    */
    public String getNomJardin();

    /**
    * découpe la parcelle actuelle en crééant deux sous-parcelles selon l'orientation passée en argument.
    * Les parcelles sont de taille quasi-identique. La dimension qui est divisé par deux sera arrondi à l'entier supérieur pour la première parcelle. 
    */
    public void SplitParcelle(Orientation o);

    /**
    * @see Parcelle#myToString
    * une parcelle avec les actions ssi withActions est True (mais pas son ses sous-parcelles éventuelles.)
    */
    public default String myToString(Boolean withActions){
        // Stringbuilder is the most efficient method of building a String like datastructure incrementally.
        StringBuilder sb = new StringBuilder("Parcelle");
        if (this.getMother() == this) sb.append(" mère");
        sb.append(String.format(" du jardin " + this.getNomJardin() + " coordonnées (%d,%d) x (%d,%d)",
            this.getx0(), this.gety0(), this.getx1(), this.gety1()));
        if (this.getSplit() == Orientation.VERTICAL)
            sb.append(", découpée verticalement en 2 sous-parcelles.");
        if (this.getSplit() == Orientation.HORIZONTAL)
            sb.append(", découpée horizontalement en 2 sous-parcelles.");
        
        if (withActions) {
            sb.append("%n");
            Iterator<Action> i = getActions();
            
            while (i.hasNext()){
                Action a = i.next();
                sb.append(a.toString());
            }
        }
        /* retour à la ligne géré à l'appel */
        return sb.toString();
    }
    
    /**
    * pretty print une parcelle récursivement et avec les actions ssi withActions est True
    * tab est un paramètre permettant de décaler l'affichage (on recommande un appel initial avec la chaîne vide).
    */
    public default String myRecToString(Boolean withActions, String tab){
        StringBuilder sb = new StringBuilder(tab);
        sb.append(tab + this.myToString(withActions));
        sb.append("%n");
        if (this.getSplit() != null){
            String newTab = tab + "  ";
            sb.append(tab + ((ParcelleJ)getFirst()).myRecToString(withActions, newTab));
            sb.append(tab + ((ParcelleJ)getSecond()).myRecToString(withActions, newTab));
        }
        return sb.toString();
    }

}
