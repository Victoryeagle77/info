package api_jardin;
import java.util.*;
import java.time.Month;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.ResultSet;

// singleton class pour gérer la persistance des légumes avec une base de données
//
// pour faire fonctionner cette classe vous devez :
// _ gérer d'une manière ou d'une autre votre mot de passe et votre login ci-dessous
// _ crééer une table de légumes sur votre base (voir fichier legumes.sql)
//
// NB. Je ne l'ai pas fait, mais ça serait probablement une bonne idée d'avoir comme ici un singleton pour toutes les factory. 
public class LegumeFactoryBD implements AbstractLegumeFactory {

    // static variable single_instance of type Singleton 
    private static LegumeFactoryBD single_instance = null; 
    
    // private constructor restricted to this class itself 
    private LegumeFactoryBD(){
        // rien à faire, permet juste de rendre privé le constructeur par défaut.
    } 
  
    // static method to create instance of Singleton class 
    public static LegumeFactoryBD getLegumeFactoryBD(){ 
        if (single_instance == null) 
            single_instance = new LegumeFactoryBD(); 
        return single_instance; 
    }

    // détails connexion base de donnée
    String bd_url  = "jdbc:mariadb://dwarves.iut-fbleau.fr/";
    String bd_user = "chenu";
    String bd_pwd  = "Algorithme77"; // pas sûr que ce soit mon mot de passe...

    // tente d'ajouter le légume à la base de données
    public Legume AddLegume(String nomLegume, FamilleLegume famille, int semis, int recolte){
        if (semis < 0 || semis > 0b111111111111){
            throw new IllegalStateException("Erreur : semis doit être la valeur entière dont l'écriture binaire est sur 12 bits, un bit par mois de janvier à décembre de droite à gauche");
        }
        if (recolte < 0 || recolte > 0b111111111111){
            throw new IllegalStateException("Erreur : recolte doit être la valeur entière dont l'écriture binaire est sur 12 bits, un bit par mois de janvier à décembre de droite à gauche");
        }
        Boolean problem = false;
        StringBuilder sb = new StringBuilder("Erreur : Il y a eu un problème. Ci-dessous le log de connexion à la base de données.%n");
        Connection con = null;
        Statement stmt = null;
        String sql = "INSERT INTO Legumes(nomLegume, familleLegume, semis, Recolte) " +
            "VALUES (\""+
            nomLegume + "\", " +
            famille.ordinal() + ", " +
            "b\'" + String.format("%12s", Integer.toBinaryString(semis)).replace(" ", "0") + "\', " +
            "b\'" + String.format("%12s", Integer.toBinaryString(recolte)).replace(" ", "0") +
            "');";
        //ResultSet rs = null;
        // For an update it is an int.
        try {
            // pas nécessaire mais utile pour détecter un mauvais classpath
            Class.forName("org.mariadb.jdbc.Driver");

            try {
                con = DriverManager.getConnection(bd_url+bd_user, bd_user, bd_pwd);
                
                if(!con.isClosed()) {
                    sb.append("   OK : BD connexion réussie.%n");
                    try {
                        stmt = con.createStatement();
                        sb.append("   OK : BD création de la déclaration réussie.%n");
                        try{
                            stmt.executeUpdate(sql);
                            sb.append("   OK : BD exécution de la requête réussie.%n");
                        } catch(SQLException e) {
                            sb.append("   KO : insertion ratée (exception SQL ci-dessous).%n");    
                            sb.append(e);
                            problem = true;
                        } finally {
                            try {
                                stmt.close();
                                sb.append("   OK : BD fermeture de la déclaration réussie.%n");
                            } catch(SQLException e) {
                                sb.append("   KO : BD fermeture de la déclaration ratée.%n");
                                problem = true;
                            }
                            stmt = null;
                        }
                    } catch(SQLException e) {
                        sb.append("   KO : BD creation de la déclaration ratée (exception SQL ci-dessous).%n");    
                        sb.append(e);
                        problem = true;
                    }
                } else {
                    sb.append("   KO : BD connexion prématurément fermée.%n");    
                    problem = true;
                }
                try {
                    con.close();
                    sb.append("   OK : BD fermeture de la connexion réussie.%n");    
                } catch(SQLException e) {
                    sb.append("   KO : BD fermeture de la connexion ratée.%n");    
                    problem = true;
                }
            } catch(SQLException e) {
                sb.append("   KO : BD connexion ratée.%n");    
                problem = true;
            }
        }
        catch(ClassNotFoundException e) {
            sb.append("   KO : BD pas de pilote MariaDB dans les chemins de classes disponibles!%n");
            sb.append("        passez à java le bon classpath. À l'iut il faut :%n");
            sb.append("        -cp \"/export/documents/mariadb-client.jar:.\"%n");
            problem = true;
        }
        // ouf on a fini les try catch
        if (problem) { throw new IllegalStateException(sb.toString()); }
        // ici retourner un LegumeJ
        LegumeJ l = new LegumeJ(nomLegume,famille,semis,recolte);
        return l;
    }
    
    // supprime si existant le légume.
    // remarque : legume ne connaît pas parcelle, actionlegumes etc.
    // Il faudra faire attention si vous enlevez un légume
    // Si votre base modélise les autres concepts en lien avec légumes et dispose de clés étrangères adaptées alors un on delete cascade devrait marcher.
    // 
    public void DeleteLegume(String nomLegume){
        throw new UnsupportedOperationException("Désolé, fonction non supporté.");
    }
    
    // cherche légumes connus.
    public Iterator<Legume> getLegumes(){
        throw new UnsupportedOperationException("Désolé, fonction non supporté.");
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
