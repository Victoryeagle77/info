package api_jardin;
import java.util.*;
import java.time.*;

import java.time.format.TextStyle;

public class Example{

    public static void main(String[] args) {
        // tests manuels.
        // On n'utilise pas de base de données pour l'instant.
        // Les classes concrètes avec le suffixe J sont non persistantes mais permettent de tester l'API.

        System.out.printf("*** *** *** *** *** *** *** *** *** ***%n");
        System.out.printf("   Tests sans base de données          %n");
        System.out.printf("*** *** *** *** *** *** *** *** *** ***%n");
                
        // Il faut une factory pour faire des jardins
        AbstractJardinFactory jf = new JardinFactoryJ();
        // Il faut une factory pour faire des légumes
        AbstractLegumeFactory lf = new LegumeFactoryJ();

        System.out.printf("*** Création des factory %n");

        Parcelle p0 = jf.AddJardin("Eden", 100, 300);
        
        p0.SplitParcelle(Orientation.HORIZONTAL);
        Parcelle p00 = p0.getFirst();
        Parcelle p01 = p0.getSecond();
        p00.SplitParcelle(Orientation.VERTICAL);
        Parcelle p001 =p00.getSecond();
        p01.SplitParcelle(Orientation.HORIZONTAL);
        Parcelle p010 = p01.getFirst();
        System.out.printf("*** Création du jardin Eden %n");
        
        LocalDate now = LocalDate.now();
        
        ActionSol a1 = new ActionSol(now, p0, ActionSolType.FUMER);        
        p0.addAction(a1);
        ActionSol a2 = new ActionSol(now, p00, ActionSolType.PAILLER);        
        p00.addAction(a2);
        System.out.printf("*** Ajout d'actions Sol au jardin Eden %n");
        
        Legume poireau = lf.AddLegume("Poireau de Carentan", FamilleLegume.ALLIACEES, 0b000000000100, 0b011111111000);
        // poireau.semisOK(Month.MARCH);
        // poireau.recolteOK(Month.AUGUST);
        // poireau.recolteOK(Month.SEPTEMBER);
        // poireau.recolteOK(Month.OCTOBER);
        // poireau.recolteOK(Month.NOVEMBER);
        Legume beet = lf.AddLegume("Betterave Crapaudine", FamilleLegume.CHENOPODES,0b000000011000, 0b011111000000);
        // beet.semisOK(Month.APRIL);
        // beet.semisOK(Month.MAY);
        // beet.recolteOK(Month.JULY);
        // beet.recolteOK(Month.AUGUST);
        // beet.recolteOK(Month.SEPTEMBER);
        // beet.recolteOK(Month.OCTOBER);
        // beet.recolteOK(Month.NOVEMBER);
        System.out.printf("*** Création de légumes %n");
        System.out.printf(poireau.toString(TextStyle.FULL));
        System.out.printf(beet.toString(TextStyle.FULL));
        
        ActionLegume a3 = new ActionLegume(now, p0, poireau, ActionLegumeType.TRANSPLANTER);
        p0.addAction(a3);

        ActionLegume a4 = new ActionLegume(LocalDate.of(2019, Month.MAY, 1), p00, beet, ActionLegumeType.SEMER);
        ActionLegume a5 = new ActionLegume(LocalDate.of(2019, Month.JULY, 14), p001, beet, ActionLegumeType.ECLAIRCIR);
        ActionLegume a6 = new ActionLegume(LocalDate.of(2019, Month.AUGUST, 15), p001, beet, ActionLegumeType.RECOLTER);
        ActionLegume a7 = new ActionLegume(LocalDate.of(2019, Month.AUGUST, 31), p001, beet, ActionLegumeType.RECOLTER);
        ActionLegume a8 = new ActionLegume(LocalDate.of(2019, Month.SEPTEMBER, 15), p001, beet, ActionLegumeType.ARRACHER);
        p00.addAction(a4);
        p001.addAction(a5);
        p001.addAction(a6);
        p001.addAction(a7);
        p001.addAction(a8);

        System.out.printf("Affichage long %n");
        System.out.printf(p00.myLongToString());

        System.out.printf("Affichage long %n");
        System.out.printf(p001.myLongToString());
        
        // System.out.printf(p0.myToString(true)+"%n");
        
        // System.out.printf(p00.myToString(true)+"%n");
        // System.out.printf(p001.myToString(true)+"%n");

        System.out.printf("Affichage récursif %n");
        System.out.printf(p0.myRecToString(true,""));

        p00.reset();
        System.out.printf("Affichage récursif après reset%n");
        System.out.printf(p0.myRecToString(true,""));

        System.out.printf("*** *** *** *** *** *** *** *** *** ***%n");
        System.out.printf("   Tests avec base de données          %n");
        System.out.printf("*** *** *** *** *** *** *** *** *** ***%n");

        // Il faut une factory pour faire des légumes
        // pas le droit de faire de new pour les singletons :(
        // AbstractLegumeFactory lfbd = new LegumeFactoryBD();
        // mais on peut faire un get :)
        AbstractLegumeFactory lfbd = LegumeFactoryBD.getLegumeFactoryBD();
        System.out.printf("*** Création de légumes avec la LegumeFactoryBD%n");
        Legume poireauBD = null;
        Legume beetBD = null;
        try {
            poireauBD = lfbd.AddLegume("Poireau de Carentan", FamilleLegume.ALLIACEES, 0b000000000100, 0b011111111000);
            System.out.printf(poireauBD.toString(TextStyle.FULL));
        } catch(IllegalStateException e) {
            System.out.printf(e.getMessage());
        }
        try {
            beetBD = lfbd.AddLegume("Betterave Crapaudine", FamilleLegume.CHENOPODES,0b000000011000, 0b011111000000);
            System.out.printf(beetBD.toString(TextStyle.FULL));
        } catch(IllegalStateException e) {
            System.out.printf(e.getMessage());
        }
    }   
}
