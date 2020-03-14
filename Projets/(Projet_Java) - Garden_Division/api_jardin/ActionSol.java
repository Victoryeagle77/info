package api_jardin;
import java.util.*;

import java.time.Month;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;

public class ActionSol extends Action {

    private ActionSolType type;

    public ActionSolType getType() { return type; }

    public ActionSol(LocalDate date, Parcelle parcelle, ActionSolType type){
        this.date=date;
        this.parcelle = parcelle;
        this.type=type;
    }

    public String toString(){
        return this.date.format(DateTimeFormatter.ofPattern("dd-MM-YYYY")) + " dans "+ parcelle.myToString() + " : " + type + " " + "%n";
    }

    public static void main(String[] args) {
        LocalDate now = LocalDate.now();
        Parcelle p0 = new ParcelleJ("Eden", 100, 300);
        ActionSol a = new ActionSol(now, p0, ActionSolType.FUMER);        
        System.out.printf(a.toString());
        
    }
}


