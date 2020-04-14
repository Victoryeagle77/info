package src;
import java.sql.*;

/**
* La classe <code>Model</code> permet la r&eacute;cup&eacute;ration,
* le traitement, et la transmission de valeur dans la base de donn&eactue;e.
*/
public class Creation{
    /**
    * @see Creation#Creation(String nomJardin, int dimx, int dimy)
    * est la m&eacute;thode permettant de se connecter &agrave; la base de donn&eacute;es,
    * et de cr&eacute;er un jardin avec ses attributs d&eacute;finis par les param&egrave;tre
    * @param nomJardin
    * @param dimx
    * @param dimy
    */
    public Creation(String nomJardin, int dimx, int dimy){
        /* Initialisation de la connexion */
        Connection c = null;
        try{
            /* Connexion à la base de données phpMyAdmin */
            Class.forName("org.mariadb.jdbc.Driver");
            c = DriverManager.getConnection("jdbc:mariadb://dwarves.iut-fbleau.fr/" 
                + "chenu", "chenu", "Algorithme77");
            /* Insérer dans la table Jardin de la base de données, 
            de nouveuax attributs concernant le nouveaux jardin. */
            PreparedStatement s = c.prepareStatement("INSERT INTO Jardin VALUES(?, ?, ?);");
            /* place les paramètres en tant qu'attributs */
            s.setString(1, nomJardin);
            s.setInt(2, dimx);
            s.setInt(3, dimy);
            ResultSet res = s.executeQuery();
            /* Récupération test */
            while(res.next())
                System.out.println(res.getString(1));
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