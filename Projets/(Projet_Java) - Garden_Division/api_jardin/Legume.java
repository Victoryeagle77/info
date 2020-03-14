package api_jardin;
import java.util.*;
import java.time.Month;
import java.time.format.TextStyle;

/**
 * 
 */
interface Legume{
    
    /** 
     * autorise le semis pour le mois donné en argument
     * @param m un mois (voir Month.java)
     * @return void
     */
    public void semisOK(Month m);

    /** 
     * autorise le semis pour le mois donné en argument
     * @param m un mois (voir Month.java)
     * @return void
     */
    public void recolteOK(Month m);

    public Boolean getSemis(Month m);

    public Boolean getRecolte(Month m);

    public String getNom();

    public FamilleLegume getFamille();
    
    public default String toString(TextStyle t){
        // Stringbuilder is the most efficient method of building a String like datastructure incrementally. 
        StringBuilder sb = new StringBuilder( this.getNom() + " (" + this.getFamille() + "), semis ");
        for (Month m : Month.values()){
            if (this.getSemis(m))
                sb.append(String.format("%s ",m.getDisplayName(t, Locale.FRANCE)));
        }
        sb.append(", récolte ");
        for (Month m : Month.values()){
            if (this.getRecolte(m))
                sb.append(String.format("%s ",m.getDisplayName(t, Locale.FRANCE)));
        }
        sb.append("%n");
        return sb.toString();
    }

  
}

