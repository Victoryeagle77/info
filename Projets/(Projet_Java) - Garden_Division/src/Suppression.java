package src;
import java.sql.*;

/**
* La classe <code>Suppression</code> permet la suppression d'un jardin,
* de la liste d&eacute;roulante et de la base de donn&eacute;es.
*/
public class Suppression {
    /**
    * @see Suppression#Suppression(String nom)
    * est la m&eacute;thode permettant de se connecter &agrave; la base de donn&eacute;es,
    * de supprimer de la liste d&eacute;roulant un jardin,
    * en prenant en param&egrave;tre le nom d'un jardin
    * @param nom
    * Et supprime tous les param&egrave;tre de celui-ci.
    */
    public Suppression(String nom) {
        /* Initialisation de la connexion */
        Connection c = null;
        try{
            /* Connexion à la base de données phpMyAdmin */
            Class.forName("org.mariadb.jdbc.Driver");
            c = DriverManager.getConnection("jdbc:mariadb://dwarves.iut-fbleau.fr/" 
                + "chenu", "chenu", "Algorithme77");
            /* Supprime les attributs liés à un jardin */
            PreparedStatement s = c.prepareStatement("DELETE FROM Jardin WHERE nom = ?;");
            s.setString(1, nom);
            ResultSet res = s.executeQuery();
            /* Fermeture de la connexion */
            c.close();
        /* Attrape les erreurs liées à un porblème de connexion,
        ou de données non-existante. */
        }catch (SQLException e){
            System.err.println("Erreur : " + e.getMessage());
        }catch (Exception e){
            System.err.println("Erreur : " + e.getMessage());
        }
    }
}