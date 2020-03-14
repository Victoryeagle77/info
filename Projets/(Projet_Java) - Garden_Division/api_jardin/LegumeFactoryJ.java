package api_jardin;
import java.util.*;
import java.time.Month;

public class LegumeFactoryJ implements AbstractLegumeFactory {

    // map de légumes (nom, legume).
    protected Map<String,Legume> legumes = new HashMap<String,Legume>();

    
    // ajoute un nouveau légume
    public Legume AddLegume(String nomLegume, FamilleLegume famille, int semis, int recolte){
        if(legumes.containsKey(nomLegume)) {
            throw new IllegalStateException("Impossible d'ajouter le légume "+ nomLegume + " car il existe déjà.");
        }
        // Je suis une factory pour des légumesJ
        Legume l = new LegumeJ(nomLegume, famille, semis, recolte);
        
        legumes.put(nomLegume,l);
        return l;
    }

    // supprime si existant le légume.
    // remarque : legume ne connaît pas parcelle, actionlegumes etc.
    public void DeleteLegume(String nomLegume){
        if(legumes.containsKey(nomLegume)) legumes.remove(nomLegume);
        else throw new IllegalStateException("Impossible de supprimer "+ nomLegume + " , car ce nom ne correspond à aucun légume connu. Veuillez vérifier l'orthographe et la casse.");
    }
    
    // cherche légumes connus.
    public Iterator<Legume> getLegumes(){
        // je copie la collection legumes.values() pour éviter un changement du map legumes.
        // Attention. la copie n'est pas profonde. Ce sont potentiellement les mêmes objets légumes.
        return Collections.unmodifiableCollection(legumes.values()).iterator();
    }

    // cherche légumes connus par famille.
    public Iterator<Legume> getLegumes(FamilleLegume famille){
        throw new UnsupportedOperationException("Désolé, fonction non supporté.");
    }

    // cherche légumes connus.
    // retourne un légume connu si la chaîne de caractère mot apparaît dans le nom de ce dernier.
    public Iterator<Legume> getLegumes(String mot){
        throw new UnsupportedOperationException("Désolé, fonction non supporté.");
    }

}
