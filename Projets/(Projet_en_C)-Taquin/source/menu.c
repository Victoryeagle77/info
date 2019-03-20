    /**** Arthur Chenu ****/

    #include "jeu.h" /* Appelle du fichier header "jeu.h" pour la fonction 
    void jouer(unsigned short int, unsigned short int, unsigned short int, unsigned short int)
    définie dans "jeu.c" */

    /*
    *** Paramètre de la librairie lgraph utilisé ***
      --> couleur char[] : Type définit déterminant une couleur.
      --> _X : Coordonnées en abscisse relevé au passage du curseur de la souris sur l'écran.
      --> _Y : Coordonnées en ordonnée relevé au passage du curseur de la souris sur l'écran.
      On compare donc ces deux paramètres avec des couples de coordonnés, à valeur entière, 
      définit dans des conditions avec l'opérateur ET.
      --> XK : Coordonnées de relevé d'une touche.
      --> XK_n : Avec n qui est un chiffre, sert à commander un paramètre de touche clavier
      --> XK_KP_n : Avec n qui est un chiffre, sert à commander un paramètre de touche clavier
      --> ChargerImageFond(char[]) : Permet de charger une image sur l'ensemble de la fenêtre
      en inscrivant en argument son chemin relatif.
      --> ChargerImage(char[], int, int, int, int, int, int) : Permet de charger une image,
      à partir de son chemin relatif, avec ses dimensions et les coordonnées de sa position sur
      une fenêtre graphique.
      --> RemplirRectangle(int, int, int, int) : Permet de construire un rectangle avec ses dimensions
      et sa position sur la fenêtre.
      --> CouleurParNom(char[]) : 
      --> ChoisirCouleurDessin(couleur) :
      --> EcrireTexte(int, int, int, int) :
      --> ToucheEnAttente() : Détectera une touche cliquée, tant qu'aucune touche est encore cliquée.
      --> Touche() : Défini une touche active.
      --> SourisCliquee() : Détecte si on a cliqué sur la souris.
      --> SourisPosition() : Relève les coordonnées de la position du curseur de la souris sur l'écran.
    */

    /* Définition de types généraux pour le restant du programme */
    couleur coloris; 
    unsigned short int touche;
    unsigned short int text_design;
    unsigned short int ligne = 3;
    unsigned short int colonne = 3;
    char selection[10];

    void choix(unsigned short int longueur, unsigned short int hauteur, 
      unsigned short int image, unsigned short int miniature) {
      /* Recharge l'écran pour préparer la page suivante. */
      ChargerImageFond("../images/fond.png");

      /* Boutton jouer */
      text_design=TailleChaineEcran("Jouer", 1);
      coloris = CouleurParNom("gray");
      ChoisirCouleurDessin(coloris);
      RemplirRectangle(longueur/2-8-text_design/2, 5*hauteur/6, text_design+20, 45);
      
      /* Couleur des textes */
      coloris = CouleurParNom("black");
      ChoisirCouleurDessin(coloris); 
      
      /* Affichage graphique de type printf durant la séléction des lignes et colonnes */
      EcrireTexte(longueur/3, 5*hauteur/25, "* Lignes *", 1);
      sprintf(selection, "%hu", ligne);
      EcrireTexte((longueur/2)+70, 5*hauteur/25, "* Colonne *", 1);
      EcrireTexte((longueur/2)-120, (hauteur/3)+80, selection, 1);
      sprintf(selection, "%hu", colonne);
      EcrireTexte((longueur/2)+120, (hauteur/3)+80, selection, 1);

      EcrireTexte(longueur/2-text_design/2, 5*hauteur/6+30, "Jouer", 1);
      
      /* Affichage d'images de flèche avec la fonction ChargerImage(int, int, int, int, int, int) */
      ChargerImage("../images/haut.png", (longueur/2)-160, (hauteur/4), 0, 0, 80, 80);
      ChargerImage("../images/gauche.png", (longueur/2)-160, (hauteur/2), 0, 0, 80, 80);
      ChargerImage("../images/droite.png", (longueur/2)+80, (hauteur/4), 0, 0, 80, 80);
      ChargerImage("../images/bas.png", (longueur/2)+80, (hauteur/2), 0, 0, 80, 80);
      
      while(1) { /* Boucle définissant : quoi qu'il se passe, faire ... */
        if (ToucheEnAttente()) {
          touche = Touche(); /* Relever une touche
           Permet d'augmenter le nombre de ligne en cliquant à gauche */
          if(touche == XK_Up) {
            ligne++;
            if(ligne>8) { ligne=8; } /* Empêche de dépasser 8 lignes
           Permet d'augmenter le nombre de ligne en cliquant à gauche */
          }else if(touche == XK_Left){
            ligne--;
            if(ligne<3) { ligne=3; } /* Empêche de passer en dessous de 3 lignes
           Permet d'augmenter le nombre de colonne en cliquant à droite */
          }else if(touche == XK_Right){
            colonne++;
            if(colonne>8) { colonne=8; } /* Empêche de dépasser 8 colonnes
            Permet d'augmenter le nombre de colonne en cliquant en bas */
          }else if(touche == XK_Down) {
            colonne--;
            if(colonne<3) { colonne=3; } /* Empêche de passer en dessous de 3 colonnes */
          }else if(touche == XK_Return) { /* Touche de bouton retour */
            jouer(image, miniature, ligne, colonne); /* Fonction jouer(int, int, int, int) */
            exit(0); /* Quitte avec succès */
          }
          /* Rechargement d'écran pour le menu de la séléction */
          ChargerImageFond("../images/fond.png");
          EcrireTexte(longueur/3, 5*hauteur/25, "* Lignes *", 1);
          sprintf(selection, "%hu",ligne);
          EcrireTexte((longueur/2)+70, 5*hauteur/25, "* Colonne *", 1);
          EcrireTexte((longueur/2)-120, (hauteur/3)+80, selection, 1);
          sprintf(selection, "%hu",colonne);
          EcrireTexte((longueur/2)+120, (hauteur/3)+80, selection, 1);
          RemplirRectangle(longueur/2-8-text_design/2, 5*hauteur/6, text_design+20, 45);
          ChargerImage("../images/haut.png",(longueur/2)-160, (hauteur/4), 0, 0, 80, 80);
          ChargerImage("../images/gauche.png",(longueur/2)-160, (hauteur/2), 0, 0, 80, 80);
          ChargerImage("../images/droite.png",(longueur/2)+80, (hauteur/4), 0, 0, 80, 80);
          ChargerImage("../images/bas.png",(longueur/2)+80, (hauteur/2), 0, 0, 80, 80);
          coloris = CouleurParNom("gray");
          ChoisirCouleurDessin(coloris);
          RemplirRectangle(longueur/2-8-text_design/2, 5*hauteur/6, text_design+20, 45);
          coloris = CouleurParNom("black");
          ChoisirCouleurDessin(coloris);
          EcrireTexte(longueur/2-text_design/2, 5*hauteur/6+30, "Jouer", 1);
          /* Fin du rechargement */
      }

      if (SourisCliquee()) { /* Si l'utilisateur clique sur la souris */
        SourisPosition(); /* Prendre les coordonnées de la position de la souris */
        /* On compare les paramètres _X et _Y avec des couples de coordonnés, à valeur entière, 
        définit dans des conditions avec l'opérateur ET, pour définir l'endroit à cliquer sur l'écran.
        */
        if(_X >= (longueur/2)-160 && _X <= (500)-80 && _Y >= (hauteur/4) && _Y <= (hauteur/4)+80) {
          ligne++;
          if(ligne > 8) { ligne=8; }
        }else if(_X >= (longueur/2)-160 && _X <= (500)-80 && _Y >= (hauteur/2) && _Y <= (hauteur/2)+80) {
          ligne--;
          if(ligne < 3) { ligne=3; }
        }else if(_X >= (longueur/2)+80 && _X<=(longueur/2)+160 && _Y>=(hauteur/4) && _Y<=(hauteur/4)+80) {
          colonne++;
          if(colonne > 8) { colonne=8; }
        }else if(_X >= (longueur/2)+80 && _X <= (longueur/2)+160 && _Y >= (hauteur/2) && _Y <= (hauteur/2)+80) {
          colonne--;
          if(colonne < 3) { colonne=3; }
        }else if(_X >= longueur/2-text_design/2 && _X <= longueur/2+text_design/2 
          && _Y >= 5*hauteur/6 && _Y <= 5*hauteur/6+50) {
          jouer(image, miniature, ligne, colonne);
          exit(0);
        }
        /* Rechargement d'écran pour le menu de la séléction */
        ChargerImageFond("../images/fond.png");
        EcrireTexte(longueur/3, 5*hauteur/25, "* Lignes *", 1);
        sprintf(selection, "%hu", ligne);
        EcrireTexte((longueur/2)+70, 5*hauteur/25, "* Colonne *", 1);
        EcrireTexte((longueur/2)-120, (hauteur/3)+80, selection, 1);
        sprintf(selection, "%hu", colonne);
        EcrireTexte((longueur/2)+120, (hauteur/3)+80, selection, 1);
        RemplirRectangle(longueur/2-8-text_design/2, 5*hauteur/6, text_design+20, 45);
        ChargerImage("../images/haut.png",(longueur/2)-160, (hauteur/4), 0, 0, 80, 80);
        ChargerImage("../images/gauche.png",(longueur/2)-160, (hauteur/2), 0, 0, 80, 80);
        ChargerImage("../images/droite.png",(longueur/2)+80, (hauteur/4), 0, 0, 80, 80);
        ChargerImage("../images/bas.png",(longueur/2)+80, (hauteur/2), 0, 0, 80, 80);
        coloris = CouleurParNom("gray");
        ChoisirCouleurDessin(coloris);
        RemplirRectangle(longueur/2-8-text_design/2, 5*hauteur/6, text_design+20, 45);
        coloris = CouleurParNom("black");
        ChoisirCouleurDessin(coloris);
        EcrireTexte(longueur/2-text_design/2, 5*hauteur/6+30, "Jouer", 1);
        /* Fin du rechargement */
        }
      }
    }

    void image_choisie(unsigned short int longueur, unsigned short int hauteur) {
      /* Recharge l'écran pour préparer la page suivante. */
      ChargerImageFond("../images/fond.png");
      
      /* Boutton Quitter */
      text_design=TailleChaineEcran("Quitter", 2);
      coloris = CouleurParNom("gray");
      ChoisirCouleurDessin(coloris);
      RemplirRectangle(longueur/2-text_design/2, 5*hauteur/6, text_design, 50);
      /* Couleur des textes */
      coloris = CouleurParNom("black");
      ChoisirCouleurDessin(coloris);
      EcrireTexte(420, 100, "==== TAQUIN ====", 1);
      EcrireTexte(((longueur/3)-68), (hauteur/4.5), "Img-1 [Taper 1]", 1);
      EcrireTexte((longueur/2)-68, (hauteur/4.5), "Img-2 [Taper 2]", 1);
      EcrireTexte((2*(longueur/3))-68, (hauteur/4.5), "Img-3 [Taper 3]", 1);
      EcrireTexte(517-text_design/2, 5*hauteur/6+32, "Quitter", 1);
      /* Règles */
      EcrireTexte(100-text_design/2, 5*hauteur/6-240, 
      "Le taquin est un jeu dont le but est de reconstruire des puzzle d'images avec une case mobile noire", 1);
      EcrireTexte(100-text_design/2, 5*hauteur/6-220, "(au clavier ou avec la souris).", 1);
      EcrireTexte(100-text_design/2, 5*hauteur/6-150, "[Choisissez parmis les trois images ici]", 1);
      /* Fin des règles */
      ChargerImage("../images/miniature1.png",(longueur/3) -75, (hauteur/4), 0, 0, 150, 150);
      ChargerImage("../images/miniature2.png",(longueur/2) -75, (hauteur/4), 0, 0, 150, 150);
      ChargerImage("../images/miniature3.png",(2*(longueur/3)) -75, (hauteur/4), 0, 0, 150, 150);
      /* Ce fragment permet d'ouvrir la fenêtre même si le curseur de la souris est en dehors,
      ou qu'une touche du clavier est touchée en dehors */
      while(1) {
        /* Si une touche est attendu pour être cliquée OU que la souris est cliquée */
        if(SourisCliquee() || ToucheEnAttente()) { 
          if (ToucheEnAttente()) { touche = Touche(); } /* Relever une touche */
          SourisPosition(); /* Relever les coordonnée de la position du curseur de la souris
          Définira au clavier le choix des images à séléctionner */
          if((_X >= (longueur/3)-75 && _X <= (longueur/3)+75 
            && _Y >= (hauteur/4) && _Y <= (hauteur/4)+150) 
            || (touche == XK_1 || touche == XK_KP_1)) 
            choix(longueur, hauteur, 1, 650); /* Fonction choix(int, int, int, int) */
          else if((_X >= (longueur/2)-75 && _X <= (longueur/2)+75 
            && _Y >= (hauteur/4) && _Y <= (hauteur/4)+150) 
            || (touche == XK_2 || touche == XK_KP_2)) 
            choix(longueur, hauteur, 2, 600); 
          else if((_X >= 2*(longueur/3)-75 && _X <= 2*(longueur/3)+75 
            && _Y >= (hauteur/4) && _Y <= (hauteur/4)+150) || 
            (touche == XK_3 || touche == XK_KP_3)) 
            choix(longueur, hauteur, 3, 700); 
          else if (_X >= longueur/2-text_design/2 && _X <= longueur/2+text_design/2 
            && _Y >= 5*hauteur/6 && _Y <= 5*hauteur/6+50) 
            exit(0);
        }
      }
    }