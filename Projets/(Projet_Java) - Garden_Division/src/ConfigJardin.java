package src;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;

/**
* La classe <code>ConfigJardin</code> permet la r&eacute;cup&eacute;ration,
* le traitement, et la transmission de valeur dans la base de donn&eactue;e.
*/
public class ConfigJardin {
    List<String> resultats = new ArrayList<String>();
    public ConfigJardin(String nomJardin){
        Connection c = null;
        try{
            Class.forName("org.mariadb.jdbc.Driver");
            c = DriverManager.getConnection("jdbc:mariadb://dwarves.iut-fbleau.fr/" 
                + "chenu", "chenu", "Algorithme77");
            PreparedStatement s = c.prepareStatement("Select dimX, dimY from Jardin WHERE nom = ?;");
            s.setString(1, nomJardin);
            ResultSet res = s.executeQuery();
            /* Récupération test */
            while(res.next()) {
                resultats.add(res.getString(1));
                resultats.add(res.getString(2));
            }
            c.close();
        }catch (SQLException e){
            System.err.println("Erreur : " + e.getMessage());
        }catch (Exception e){
            System.err.println("Erreur : " + e.getMessage());
        }
    }

    /**
    * @see Model#getDimensions()
    * est la m&eacute;thode permettant de rappeler dans la liste d&eacute;roulante,
    * la liste des noms de jardins.
    */
    public List<String> getDimensions(){ return resultats; }
}