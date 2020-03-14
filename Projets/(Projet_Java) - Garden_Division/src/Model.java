package src;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;

/**
* @author Arthur Chenu
* @author Julien Carcau
* @version final
*/

/**
* La classe <code>Model</code> permet la r&eacute;cup&eacute;ration
* de valeurs dans la base de donn&eactue;es.
*/
public class Model{
    List<String> resultats = new ArrayList<String>();
    /**
    * @see Model#Model()
    * est la m&eacute;thode permettant de se connecter &agrave; la base de donn&eacute;es,
    * de r&eacute;cup&eacute;rer les noms de jardins et de les placer dans une liste.
    */
    public Model(){
        /* Initialisation de la connexion */
        Connection c = null;
        try{
            /* Connexion à la base de données phpMyAdmin */
            Class.forName("org.mariadb.jdbc.Driver");
            c = DriverManager.getConnection("jdbc:mariadb://dwarves.iut-fbleau.fr/" 
                + "chenu", "chenu", "Algorithme77");
            /* Séléctionner un nom de jardin de la table Jardin. */
            ResultSet res = c.prepareStatement("Select nom from Jardin;").executeQuery();
            /* Récupération des noms de jardins dans la base de données. */
            while(res.next()){ resultats.add(res.getString(1)); }
            /* Fermeture de la connexion */
            c.close();
        /* Attrape les erreurs liées à un porblème de connexion,
        ou de données non-existante. */
        }catch(SQLException e){
            System.err.println("Erreur : " + e.getMessage());
        }catch(Exception e){
            System.err.println("Erreur : " + e.getMessage());
        }
    }

    /**
    * @see Model#getNom()
    * est la m&eacute;thode permettant de rappeler dans la liste d&eacute;roulante,
    * la liste des noms de jardins.
    */
    public List<String> getNom(){ return resultats; }
}