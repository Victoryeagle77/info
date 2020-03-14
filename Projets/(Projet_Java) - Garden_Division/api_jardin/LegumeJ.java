package api_jardin;
import java.util.*;
import java.time.Month;
import java.time.format.TextStyle;

/**
 * 
 */
public class LegumeJ implements Legume {

    private String nom;

    private FamilleLegume famille;
    
    // Map dont la clé est un enum (ici des mois) et la valeur correspondant à chaque clé est un booléen indiquant si on peut semer à ce mois.
    private EnumMap<Month, Boolean> mapSemis = new EnumMap<Month, Boolean>(Month.class);

    // Map dont la clé est un enum (ici des mois) et la valeur correspondant à chaque clé est un booléen indiquant si on peut récolter à ce mois.
    private EnumMap<Month, Boolean> mapRecolte = new EnumMap<Month, Boolean>(Month.class);

    // constructeur
    public LegumeJ(String nom, FamilleLegume famille){
        this.nom = nom;
        this.famille = famille;
        // par défaut les mois ne sont pas OK pour le semis ou la récolte (c'est à l'utilisateur de mettre à vrai les mois correct avec recolteOK).
        for (Month m : Month.values()){
            this.mapSemis.put(m,false);
            this.mapRecolte.put(m,false);
        }
    }

    // teste si le kième bit est 1 (en comptant à partir de la droite)
    public static boolean isKthBitSet(int n, int k){
        return (((n >> (k-1)) & 1 ) == 1);
    }

    // Autre constructeur
    // @param semis, recolte : entiers sur 12 bits. De droite à gauche les mois (decembre bit 12 ... janvier bit 1).
    public LegumeJ(String nomLegume, FamilleLegume famille, int semis, int recolte){
        this(nomLegume,famille);        // appel du constructeur ci-dessus
        if (semis < 0 || semis > 0b111111111111){
            throw new IllegalStateException("semis doit être la valeur entière dont l'écriture binaire est sur 12 bits, un bit par mois de janvier à décembre de droite à gauche");
        }
        if (recolte < 0 || recolte > 0b111111111111){
            throw new IllegalStateException("recolte doit être la valeur entière dont l'écriture binaire est sur 12 bits, un bit par mois de janvier à décembre de droite à gauche");
        }
        // Gestion des mois avec semis et recolte
        // on utilise le fait que les valeurs des mois sont 1, 2, 3, ...
        for (Month m : Month.values()){
            if (this.isKthBitSet(semis,m.getValue()))
                { this.semisOK(m); }
            if (this.isKthBitSet(recolte,m.getValue()))
                { this.recolteOK(m); }
        }
    }
    
    /** 
     * autorise le semis pour le mois donné en argument
     * @param m un mois (voir Month.java)
     * @return void
     */
    public void semisOK(Month m){
        this.mapSemis.put(m, true);
    }

    /** 
     * autorise le semis pour le mois donné en argument
     * @param m un mois (voir Month.java)
     * @return void
     */
    public void recolteOK(Month m){
        this.mapRecolte.put(m, true);
    }


    public Boolean getSemis(Month m){
        return this.mapSemis.get(m);
    }

    public Boolean getRecolte(Month m){
        return this.mapRecolte.get(m);
    }

    public String getNom(){ return nom; }

    public FamilleLegume getFamille(){ return famille; }
    
    public String toString(TextStyle t){
        // Stringbuilder is the most efficient method of building a String like datastructure incrementally. 
        StringBuilder sb = new StringBuilder( this.nom + " (" + this.famille + "), semis ");
        for (Month m : Month.values()){
            if (this.mapSemis.get(m))
                sb.append(String.format("%s ",m.getDisplayName(t, Locale.FRANCE)));
        }
        sb.append(", récolte ");
        for (Month m : Month.values()){
            if (this.mapRecolte.get(m))
                sb.append(String.format("%s ",m.getDisplayName(t, Locale.FRANCE)));
        }
        sb.append("%n");
        return sb.toString();
    }

    
    public static void main(String[] args) {
        // tests manuels.
        // On peut utiliser le main d'une classe pour y placer des tests.
        // ou bien utiliser Junit dans une autre classe.

        // enum des mois, voir Java.time.Month
        // Month.APRIL
        // Month.AUGUST
        // Month.DECEMBER
        // Month.FEBRUARY
        // Month.JANUARY
        // Month.JULY
        // Month.JUNE
        // Month.MARCH
        // Month.MAY
        // Month.NOVEMBER
        // Month.OCTOBER
        // Month.SEPTEMBER

        // Quelques légumes par famille.
        // Composées (Astéracées) : artichaut, cardon, chicorée, laitue, pissenlit, salsifi, scorsonère, topinambour
        // Ombellifères (Apiacées) : carotte, céleri, cerfeuil, fenouil, panais
        // Liliacées (Alliacées) : ail, asperge, échalote, oignon, poireau
        // Légumineuses (Fabiacées) : fève, haricot, lentille, pois
        // Chénopodiacées : betterave, épinard, poirée (blette),
        // Cucurbitacées : concombre, courge, melon, potiron
        // Solanacées : aubergine, coqueret du Pérou, pomme de terre, tomate, piment, poivron
        // Labiées : crosne
        // Crucifères (Brassicacées) : choux, cresson, navet, radis, roquette
        // Autres : mâche, maïs, oseille, tétragone, pourpier

        // Familles retenues, voir FamilleLegume.java 
        // AUTRE, ALLIACEES, CHENOPODES, CUCURBITACEES, CRUCIFERES, LEGUMINEUSES, OMBELLIFERES, SOLANACEES;

        // Constructeur "à la main"
        Legume poireau = new LegumeJ("Poireau de Carentan", FamilleLegume.ALLIACEES);
        poireau.semisOK(Month.MARCH);
        poireau.recolteOK(Month.AUGUST);
        poireau.recolteOK(Month.SEPTEMBER);
        poireau.recolteOK(Month.OCTOBER);
        poireau.recolteOK(Month.NOVEMBER);
        System.out.printf(poireau.toString(TextStyle.FULL));

        // Constructeur "à la main"
        Legume beet = new LegumeJ("Betterave Crapaudine", FamilleLegume.CHENOPODES);
        beet.semisOK(Month.APRIL);
        beet.semisOK(Month.MAY);
        beet.recolteOK(Month.JULY);
        beet.recolteOK(Month.AUGUST);
        beet.recolteOK(Month.SEPTEMBER);
        beet.recolteOK(Month.OCTOBER);
        beet.recolteOK(Month.NOVEMBER);
        System.out.printf(beet.toString(TextStyle.NARROW));

        // Constructeur magique
        Legume poireau2 = new LegumeJ("Poireau de Carentan", FamilleLegume.ALLIACEES, 0b000000000100, 0b011111111000);
        System.out.printf(poireau2.toString(TextStyle.FULL));
        Legume beet2 = new LegumeJ("Betterave Crapaudine", FamilleLegume.CHENOPODES,0b000000011000, 0b011111000000);
        System.out.printf(beet2.toString(TextStyle.NARROW));
        Legume pot2 = new LegumeJ("Potiron galeuse d´eysines", FamilleLegume.CUCURBITACEES, 0b000000111100, 0b001100000000);
        System.out.printf(pot2.toString(TextStyle.NARROW));
        Legume rock2 = new LegumeJ("Roquette sauvage", FamilleLegume.CRUCIFERES,                    0b000111111100, 0b011111110000);
        System.out.printf(rock2.toString(TextStyle.NARROW));
        Legume bb2 = new LegumeJ("Feve extra precoce a grano violetto", FamilleLegume.LEGUMINEUSES, 0b000000000110, 0b000001110000);
        System.out.printf(bb2.toString(TextStyle.NARROW));
        Legume car2 = new LegumeJ("Carotte cosmic purple", FamilleLegume.OMBELLIFERES, 0b000000111100, 0b011111100000);
        System.out.printf(car2.toString(TextStyle.NARROW));
        Legume tat2 = new LegumeJ("Pomme de terre bleue d´Artois", FamilleLegume.SOLANACEES , 0b000000011000, 0b000111000000);
        System.out.printf(tat2.toString(TextStyle.NARROW));
    }

}


