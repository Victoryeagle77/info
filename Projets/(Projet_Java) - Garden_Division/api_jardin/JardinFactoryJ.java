package api_jardin;
import java.util.*;

/**
* Classe <code>JardinFactoryJ</code>
* Factory concrète qui va crééer des objets ParcelleJ.
*/
public class JardinFactoryJ implements AbstractJardinFactory{
    /* map des jardins (nom, parcelle racine). */
    private Map<String,Parcelle> jardins = new HashMap<String,Parcelle>();

    /**
    * @see JardinFactoryJ#AddJardin
    * ajoute si possible un nouveau jardin
    * @return p : la parcelle mère de ce jardin. 
    */
    public Parcelle AddJardin(String nomJardin, int dimx, int dimy){
        if(jardins.containsKey(nomJardin))
            throw new IllegalStateException(
                "Impossible d'ajouter le jardin "+ nomJardin + " car il existe déjà.");
        Parcelle p = this.newJardin(nomJardin, dimx, dimy);
        jardins.put(nomJardin,p);
        return p;
    }

    /**
    * @see JardinFactoryJ#DeleteJardin
    * supprime (si existant) le jardin. 
    */
    public void DeleteJardin(String nomJardin){
        if(jardins.containsKey(nomJardin)) jardins.remove(nomJardin);
        else throw new IllegalStateException("Impossible de supprimer "+ nomJardin + " , car ce nom ne correspond à aucun jardin connu. Veuillez vérifier l'orthographe et la casse.");
    }

    /**
    * @see JardinFactoryJ#getJardin
    * @return jardins : (si existant) le jardin. 
    */
    public Parcelle getJardin(String nomJardin){
        if(jardins.containsKey(nomJardin))
            return jardins.get(nomJardin);
        throw new IllegalStateException("Impossible de trouver le jardin "+ nomJardin + ".");
    }

    /**
    * @see JardinFactoryJ#newJardin
    * Constructeur pour un nouveau jardin. 
    * @return ParcelleJ : la parcelle initiale du jardin
    */
    public Parcelle newJardin(String nomJardin, int dimx, int dimy){
        return new ParcelleJ(nomJardin, dimx, dimy);
    }
    
}
