package api_jardin;
import java.util.*;
import java.time.*;

/**
* Classe <code>ParcelleJ</code>
* Permet de stocker localement les parcelle d'un jardin
*/
public class ParcelleJ implements Parcelle{
    /* Nom du jardin à laquelle la parcelle appartient */
    private String nomJardin;

    /* abscisse coin en haut à gauche. */
    private int x0;
    /* ordonnée coin en haut à gauche. */
    private int y0;
    /* abscisse coin en bas à droite. */
    private int x1;
    /* ordonnée coin en bas à droite. */
    private int y1;

    /* En cas de découpage de la parcelle, indique si le découpage est horizontal ou vertical */
    private Orientation split;

    /* sous parcelle gauche (si split vertical) ou haute (si split horizontal). */
    private ParcelleJ sousParcelle0;
    /* sous parcelle droite (si split vertical) ou basse (si split horizontal). */
    private ParcelleJ sousParcelle1;
    /* parcelle racine du jardin */
    private ParcelleJ tilde;
    /* parcelle mère */
    private ParcelleJ pointPoint;

    /* stocke les actions réalisées sur la parcelle. */
    private ArrayList<Action> actions = new ArrayList<Action>();

    /**
    * @see ParcelleJ#getActions 
    * @return copieActions : itérateur sur les actions réalisées sur la parcelle.
    */
    @SuppressWarnings("unchecked")
    public Iterator<Action> getActions(){
        ArrayList<Action> copieActions = (ArrayList<Action>) actions.clone();
        /* nécessaire pour plus de sûreté car Iterator permet de faire un remove sur action. */
        return copieActions.iterator();
    }

    /**
    * @see ParcelleJ#getAllActions
    * @return allActions : itérateur sur les actions vraiment réalisées sur la parcelle.
    */
    @SuppressWarnings("unchecked")
    public Iterator<Action> getAllActions(){
        ParcelleJ walkingUp = this;
        ArrayList<Action> allActions = (ArrayList<Action>) actions.clone();
        while (walkingUp.pointPoint != walkingUp) {
            walkingUp = walkingUp.pointPoint; // moveUp
            ArrayList<Action> copiesActions = (ArrayList<Action>) walkingUp.actions.clone();
            allActions.addAll(copiesActions);// un peu moche ça retourne un booléen
        }
        return allActions.iterator();
    }

    /**
    * @see ParcelleJ#addAction   
    * ajoute une action à la parcelle.
    */
    public void addAction(Action a){ actions.add(a); }
    
    /**
    * @see ParcelleJ#getSplit
    * @return split : type de split de la parcelle null si pas de sous-parcelle
    */
    public Orientation getSplit(){ return split; }

    /**
    * @see ParcelleJ#getFirst
    * @return sousParcelle0 : sous parcelle gauche (si split vertical) ou haute (si split horizontal).
    */
    public Parcelle getFirst(){
        if (this.split == null || this.sousParcelle0 == null) throw new IllegalStateException(
            "La parcelle n\'a pas de sous-parcelle");
        return sousParcelle0;
    }

    /**
    * @see ParcelleJ#getSecond
    * @return sousParcelle1 : sous parcelle droite (si split vertical) ou basse (si split horizontal).
    */
    public Parcelle getSecond(){
        if (this.split == null || this.sousParcelle1 == null) throw new IllegalStateException(
            "La parcelle n\'a pas de sous-parcelle");
        return sousParcelle1;
    }

    /**
    * @see ParcelleJ#reset
    * réunit les sous-parcelles (un quasi destructeur. on oublie les sous-parcelles, 
    * le garbage collector se chargera de les détruire)
    */
    public void reset(){
        if (this.split == null || this.sousParcelle0 == null 
            || this.sousParcelle1 == null) throw new IllegalStateException(
                "Pas possible de détruire le contenu de la parcelle car elle ne contient pas deux sous-parcelles.");
        this.split=null;
        this.sousParcelle0=null;
        this.sousParcelle1=null;
    }

    /**
    * @see ParcelleJ#getMother
    * @return pointPoint : parcelle mère de la parcelle
    */
    public Parcelle getMother(){ return this.pointPoint; }

    /**
    * @see ParcelleJ#getRoot
    * @return tilde : la parcelle racine de la parcelle
    */
    public Parcelle getRoot(){ return this.tilde; }

    /**
    * @see ParcelleJ#getx0
    * @return x0 : l'abscisse du coin en haut à gauche de la parcelle
    */
    public int getx0(){ return this.x0; }

    /**
    * @see ParcelleJ#gety0
    * @return y0 : l'ordonnée du coin en haut à gauche de la parcelle
    */
    public int gety0(){ return this.y0; }

    /**
    * @see ParcelleJ#getx1
    * @return x1 : l'abscisse du coin en bas à droite de la parcelle
    */
    public int getx1(){ return this.x1; }

    /**
    * @see ParcelleJ#gety1
    * @return y1 : l'ordonnée du coin en bas à droite de la parcelle
    */
    public int gety1(){ return this.y1; }

    /**
    * @see ParcelleJ#getNomJardin
    * @return nomJardin : le nom du jardin de la parcelle
    */
    public String getNomJardin(){ return this.nomJardin; }
    
    /**
    * @see ParcelleJ#ParcelleJ
    * Constructeur pour un nouveau jardin
    */
    public ParcelleJ(String nomJardin, int dimx, int dimy){
        if (dimx <= 0 || dimy <=0) throw new IllegalArgumentException(
            "Les dimensions du nouveau jardin doivent être strictement positives");
        if (nomJardin.length()==0) throw new IllegalArgumentException(
            "Le nom du nouveau jardin ne peut pas être vide");
        this.nomJardin = nomJardin;
        this.x0=0; this.y0=0;
        this.x1=dimx; this.y1=dimy;

        this.split=null;
        this.sousParcelle0=null;
        this.sousParcelle1=null;

        this.tilde = this;
        this.pointPoint = this;
    }

    /**
    * @see ParcelleJ#ParcelleJ
    * Constructeur pour une nouvelle parcelle qui n'a pas de descendant 
    * (attention doit rester privé, usage interne seulement).
    */
    private ParcelleJ(String nomJardin, int x0, int y0, int x1, int y1, 
            ParcelleJ tilde, ParcelleJ pointPoint){
        this.nomJardin = nomJardin;
        this.x0=x0; this.y0=y0;
        this.x1=x1; this.y1=y1;

        this.sousParcelle0=null;
        this.sousParcelle1=null;

        this.tilde = tilde;
        this.pointPoint = pointPoint;
    }

    /**
    * @see ParcelleJ#SplitParcelle
    * découpe la parcelle actuelle en crééant deux sous-parcelles selon l'orientation passée en argument.
    */
    public void SplitParcelle(Orientation o){
        Objects.requireNonNull(o, "Orientation o ne doit pas être null");
        if (Objects.nonNull(this.split) || Objects.nonNull(this.sousParcelle0) 
            || Objects.nonNull(this.sousParcelle1)) throw new IllegalStateException(
                "La parcelle ne peut pas être découpée car elle contient des sous-parcelles.");
        this.split = o;
        ParcelleJ p0, p1;
        if (o == Orientation.HORIZONTAL){
            int xsplit = (x1-x0) /2 + (x1-x0) %2; // arrondi supérieur histoire de réviser le modulo.
            p0 = new ParcelleJ(this.nomJardin, this.x0, this.y0,  xsplit, this.y1, this.tilde, this);
            p1 = new ParcelleJ(this.nomJardin,  xsplit, this.y0, this.x1, this.y1, this.tilde, this);
            this.sousParcelle0 = p0;
            this.sousParcelle1 = p1;
        }
        if (o == Orientation.VERTICAL){
            int ysplit = (y1-y0) /2 + (y1-y0) %2; // arrondi supérieur histoire de réviser le modulo.
            p0 = new ParcelleJ(this.nomJardin, this.x0, this.y0, this.x1,  ysplit, this.tilde, this);
            p1 = new ParcelleJ(this.nomJardin, this.x0,  ysplit, this.x1, this.y1, this.tilde, this);
            this.sousParcelle0 = p0;
            this.sousParcelle1 = p1;
        }
    }

}
