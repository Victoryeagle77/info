package api_jardin;
import java.util.*;

public interface AbstractLegumeFactory {

    // ajoute un nouveau légume
    // @param semis, recolte : entiers sur 12 bits. De droite à gauche les mois (decembre bit 12 ... janvier bit 1).
    public Legume AddLegume(String nomLegume, FamilleLegume famille, int semis, int recolte);

    // supprime si existant le légume.
    public void DeleteLegume(String nomLegume);
    
    // cherche légumes connus.
    public Iterator<Legume> getLegumes();

    // cherche légumes connus par famille.
    public Iterator<Legume> getLegumes(FamilleLegume famille);

    // cherche légumes connus.
    // retourne un légume connu si la chaîne de caractère mot apparaît dans le nom de ce dernier.
    public Iterator<Legume> getLegumes(String mot);

}
