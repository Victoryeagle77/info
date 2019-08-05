import javax.swing.JComponent;
import java.awt.*;
import java.util.Random;

/**
* @author Arthur Chenu
* @version final
*/

/** 
* La classe <code>Ariane</code>
* Cr&eacute;&eacute; le mod manuel (dessiner le labyrinthe) et automatique (nombre de d&eacute;placement) en fonction : 
* Des tailles sauvegard&eacute;es, de la position de la source et de la destination, correspondant &agrave; :
* @param taille
* @param src_x
* @param src_y
* @param dst_x
* @param dst_y
*/
public class Ariane extends JComponent {
  static final int MAX = 100; 
  int i, j;
  private int taille;
  private int cases[][];
  int etat[][] = new int[MAX*MAX][2];
  int etape = 0;
  private int src_x, src_y, dst_x, dst_y;
  private boolean etat_final = false;
  private int nb_etapes;
        
  /**
  * @see Ariane#aleatoire(int taille, int cases[][])
  * Prend en compte les param&eagrave;tre :
  * @param taille
  * @param cases
  * Pour d&eacute;terminer al&eacute;atoirement les cases que doit emprunter Thésée,
  * pour arriver vers la sortie du labyrinthe.
  * @return nb_etapes
  */ 
  public int aleatoire(int taille, int cases[][]){
    this.taille = taille;
    this.cases = cases;
    for (i=0; i<taille; i++){
      for (j=0; j<taille; j++){
        /* Si une case, positionnée à un certain endroit, correspond à la sortie, 
        les valeurs des coordonnées de la case seront celles de la destination. */
        if (cases[i][j] == 3) { dst_x = i; dst_y = j; }
        /* Si une case correspond à l'entrée, 
        Les coordonnées seront celles de la source. */
        else if (cases[i][j] == 2) { src_x = i; src_y = j; }
      }
    }
    /* Etat initiaux de la position source de Thésée */
    etat[0][0] = src_x;
    etat[0][1] = src_y;
    /* Validité d'une direction */
    etat_final = false;
    
    for(i=0; (!etat_final) && (i < MAX*MAX); ){
      src_x = etat[i][0];
      src_y = etat[i][1];
      /* Pour les 4 types de direction pouvant être empruntées
      par Thésée, générer aléatoirement le fait d'avancer ou de reculer. */
      switch(new Random().nextInt(4)){
        case 0: src_x--; break;
        case 1: src_y--; break;
        case 2: src_x++; break;
        case 3: src_y++; break;
      }

      if (((src_x >= 0) && (src_x < taille)) 
          && ((src_y >= 0) && (src_y < taille))){
        if ((cases[src_x][src_y] == 0) || (cases[src_x][src_y] == 2)){
          /* Si la case est accessible ou qu'elle est la source, 
          On incrémente l'état d'avancement. */
          etat[i+1][0] = src_x;
          etat[i+1][1] = src_y;
          i++;
        } else if (cases[src_x][src_y] == 3) {
          /* Si la case est la sortie l'état directionnel est validé, 
          et le labyrinthe est résolu. */
          etat_final = true;
          etat[i+1][0] = src_x;
          etat[i+1][1] = src_y;
        }
      }
    }
    /* Retour du nombre d'étape pour le mod automatique */
    return nb_etapes = i + 1;
  }
        
  /**
  * @see Ariane#pile(int[] chemin, int direction)
  * Permet de tester l'existence d'un passage pour une direction donn&eacute;e
  * Par un  retour bool&eacute;en 
  * @return true
  * @return false
  */
  public boolean pile(int[] chemin, int direction){
    for(int i=0 ; i<chemin.length; i++){
      if(direction == chemin[i]) { return false; }
    }
    return true;
  }
        
  /**
  * @see Ariane#deterministe(int taille, int[][] cases)
  * Simulant un automate d&eacute;terministe solvant toujours de mani&eagrave;re identique un labyrinthe.
  * Celui-ci détermine le chemin le plus court pour atteindre la sortie,
  * En fonction des param&eagrave;tres suivant :
  * @param taille
  * @param cases
  * @return nb_etapes
  */
  public int deterministe(int taille, int[][] cases){
    this.taille = taille;
    this.cases = cases;
    /* Pour ce qui concerne la source (Thésée),
    i et j deviennent coordonnées de la source. */
    for (i=0; i<taille; i++) {
      for (j=0; j<taille; j++)
        if(cases[i][j] == 2) { src_x = i; src_y = j; }
    }
    /* Etat initiaux de la source */
    etat[0][0] = src_x;
    etat[0][1] = src_y;

    int chemin[] = new int[taille*taille];
    int retour[][] = new int[taille*taille][3];
    int obstacle=0, avancement=0;

    for (i=0; i < taille*taille; i++) { chemin[i]--; }
    /* Définition de la position initiale du chemin de la source */
    chemin[0] = src_y * taille + src_x;
    		
    int x, y;
    /* Tant que l'état final n'est pas encore atteint */
    for (i=0 ; etat_final == false ; i++){
      /* 4 Différents type de déplacement de Thésée,
      initialisé à une valeur hors tableau. */
      int ouest = -1, est = -1, nord = -1, sud = -1;
      /* Poursuite d'un chemin emprunté */
      int poursuite = 0;
      y = chemin[i] / taille;
      x = chemin[i] % taille;
      etat[i + avancement][0] = x;
      etat[i + avancement][1] = y;
      /* On vérifie l'existance d'une direction pour aller vers la sorite. 
      On commence par la direction ouest (gauche). */
      if (((x-1)>=0) && ((x-1) < taille)){
        /* Pour les coordonnées d'une case selon les dimensions du labyrinthe. */
        if (cases[x-1][y] == 0 || cases[x-1][y] == 3){
          ouest = (x-1) + (y*taille);
          /* On vérifie si le chemin pour cette direction existe, 
          pour que l'algorithme continue d'avancer. */
          if (pile(chemin, ouest)){ poursuite++; }
          /* Si ce n'est pas le cas, le chemin n'existe pas dans cette direction. */
          else { ouest = -1; }
        }
      }
      /* Direction est (droite) */
      if (((x+1) >= 0) && ((x+1) < taille)){
        if (cases[x+1][y] == 0 || cases[x+1][y] == 3){
          est = (x+1) + (y*taille);
          if (pile(chemin, est)){ poursuite++; }
          else { est = -1; }
        }
      }
      /* Direction sud (bas) */
      if (((y-1) >= 0) && ((y-1) < taille)){
        if (cases[x][y-1] == 0 || cases[x][y-1] == 3){
          sud = x + ((y-1)*taille);
          if (pile(chemin, sud)){ poursuite++; } 
          else { sud = -1; }
        }
      }
      /* Direction nord (haut) */
      if (((y+1) >= 0) && ((y+1) < taille)){
        if (cases[x][y+1] == 0 || cases[x][y+1] == 3){
          nord = x + ((y+1)*taille);
          if (pile(chemin, nord)){ poursuite++; }
          else { nord = -1; }
        }
      }
    			
      for (j = taille*taille-1; (j-poursuite)>i; j--)
        chemin[j] = chemin[j-poursuite];
      /* Vérifie s'il est possible de continuer */
      if (poursuite > 1){
        retour[obstacle][0] = chemin[i];
        retour[obstacle][1] = poursuite;
        retour[obstacle][2] = obstacle;
        obstacle++;
      }
      j = i;
      /* Pour les 4 directions, on fait avancer Thésée dans une directions,
      si le chemein existe. */
      if (ouest != -1) { j++; chemin[j] = ouest; }
      if (est != -1) { j++; chemin[j] = est; }
      if (sud != -1) { j++; chemin[j] = sud; }
      if (nord != -1) { j++; chemin[j] = nord; }
      /* Si la source à atteint la destination, le chemin est terminé et validé. */
      if (cases[x][y] == 3) { etat_final = true; }
      /* Ne rien faire dans le cas ou on arrive sur la sortie, 
      ou que le chemin emprunté amène à sortir des dimensions du tableau,
      représentant la grille du labyrinthe. */
      if ((chemin[i+1] % taille == (x+1) || chemin[i+1] % taille == (x-1) 
           || chemin[i+1] % taille == (x)) && (chemin[i+1] / taille == (y+1) 
           || chemin[i+1] / taille == (y-1) || chemin[i+1] / taille == (y))  
           || chemin[i+1] == -1 || etat_final);
      /* Sinon */
      else {
        /* Boucle d'intégrité de continuation */
        boolean continuation = true;
        for (j = i; continuation ; j--, avancement++){
          etat[i + avancement][0] = chemin[j] % taille;
          etat[i + avancement][1] = chemin[j] / taille;

          if (chemin[j] == retour[obstacle-1][0]) {
            /* Si Thésée atteint un obstacle */
            if ((retour[obstacle-1][1]-1) <= 0)
              obstacle = retour[obstacle-1][2];
            else { continuation = false; }
          }
        }
        /* Recule en arrière */
        avancement--;
        for (j = (taille*taille)-1; (j-1) > i; j--)
          chemin[j] = chemin[j-1];
        j = i; j++;
        chemin[j] = retour[obstacle-1][0];
        i++;
      }
    }
    /* Retour du nombre d'étape pour le mod automatique */
    nb_etapes = i + avancement-1;
    return nb_etapes;
  }
  /** 
  * @see Ariane#deplacement()
  * Permet de relever le nombre de d&eacute;placement,
  * elle est r&eacute;utilis&eacute;e dans la classe : 
  * @see Controller
  * pour la faire correspondre &agrave; l'appui de la touche espace
  */
  public void deplacement(){
    etape++;
    if (etape > nb_etapes) { etape = nb_etapes; }
  }

  /**
  * @see Ariane#paintComponent(Graphics g)
  * Permet de dessinner le labyrinthe selon l'emplacement :
  * des dimesnions, de la source et de la destination par l'&eacute;tat des cases.
  */
  @Override
  public void paintComponent(Graphics g) {
    /* Création d'un composant graphique maléable */
    Graphics pinceau = g.create();
    for (i=0; i<taille; i++) {
      for (j=0; j<taille; j++) {
        int pos_x = (i*50)+5;
        int pos_y = (j*50)+5;
        /* Fond et obstacle infranchissables */
        pinceau.setColor(new Color(0,0,0));
        /* Dessine et remplie aussi la figure */
        pinceau.fillRect(pos_x, pos_y, 45, 45);
        /* Cases accessibles du labyrinthe */
        if((cases[i][j] == 0) || (cases[i][j] == 2)) {
          pinceau.setColor(new Color(100,100,100));
          pinceau.fillRect(pos_x, pos_y, 45, 45);
          /* Destination, sortie */
        } else if (cases[i][j] == 3) {
          pinceau.setColor(new Color(0,100,100));
          pinceau.fillRect(pos_x, pos_y, 45, 45);
        }
      }
    }
    /* Thésée (La source et le point de déplacement) */
    pinceau.setColor(new Color(200,0,0));
    pinceau.fillOval((etat[etape][0]*50)+5, (etat[etape][1]*50)+5, 45, 45);
    /* Compteur du nombre d'étapes nécessaire à chaque état de l'avancement de Thésée */
    pinceau.setColor(new Color(200,50,50));
    pinceau.setFont(new Font("Courier New", 1, 15));
    pinceau.drawString("== Etapes == ", taille*55, 20);
    pinceau.drawString(" " + etape, taille*55, 45);
  }

  /**
  * @see Ariane#automatique(int taille, int[][] cases, boolean choix)
  * Utilise les param&eagrave;tre :
  * @param taille
  * @param cases
  * @param choix
  * @return res 
  * Soit la moyenne des coups en ce qui concerne l'al&eacute;atoire
  */
  public int automatique(int taille, int[][] cases, boolean choix){
    int res = 0;
    if (choix == false) {
      /* On fait touner 100 fois la résolution automatique aléatoire */
      for (int i=0; i<100; i++)
        res += aleatoire(taille, cases);
      /* On fait la moyenne */
      res /= 100;
    } else if (choix == true)
      res += deterministe(taille, cases); 
    return res;
  }
}