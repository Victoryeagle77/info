package api_jardin;
import java.util.*;
import java.time.Month;
//import java.time.format.TextStyle;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;

// Cette classe n'est pas mutable.

public class ActionLegume extends Action {

    private Legume legume;

    private ActionLegumeType type;

    public Legume getLegume(){ return legume; }

    public ActionLegumeType getType(){ return type; }
    
    public ActionLegume(LocalDate date, Parcelle parcelle, Legume legume, ActionLegumeType type){
        this.date = date;
        this.parcelle = parcelle;
        this.legume = legume;
        this.type = type;
    }

    public String toString(){
        return this.date.format(DateTimeFormatter.ofPattern("dd-MM-YYYY")) + " dans "+ parcelle.myToString() + " : " + type + " " + legume.getNom() + "%n";
    }


    public static void main(String[] args) {
        LocalDate now = LocalDate.now();
        Parcelle p0 = new ParcelleJ("Eden", 100, 300);
        Legume poireau = new LegumeJ("Poireau de Carentan", FamilleLegume.ALLIACEES);
        poireau.semisOK(Month.MARCH);
        poireau.recolteOK(Month.AUGUST);
        poireau.recolteOK(Month.SEPTEMBER);
        poireau.recolteOK(Month.OCTOBER);
        poireau.recolteOK(Month.NOVEMBER);

        ActionLegume a = new ActionLegume(now, p0, poireau, ActionLegumeType.TRANSPLANTER);

        System.out.printf(a.toString());
        
    }
}


