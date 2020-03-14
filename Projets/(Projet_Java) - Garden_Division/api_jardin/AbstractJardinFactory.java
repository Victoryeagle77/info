package api_jardin;
import java.util.*;

public interface AbstractJardinFactory{

    // ajoute si possible un nouveau jardin et retourne la parcelle mère de ce jardin.
    // Si pas possible lance une IllegalStateException
    public Parcelle AddJardin(String nomJardin, int dimx, int dimy);

    // supprime (si existant) le jardin.
    // Si pas possible lance une IllegalStateException
    public void DeleteJardin(String nomJardin);

    // retourne (si existant) le jardin.
    // Si pas possible lance une IllegalStateException
    public Parcelle getJardin(String nomJardin);
    
}
