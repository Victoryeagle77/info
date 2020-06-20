#include "../header/interface.h"

/**
* @function *config_fond
* Permet d'effectuer un degrade de couleur, 
* par rapport aux parametres suivant :
* @param *map : Surface a recouvrir
* @param *d : Disposition par rapport a l'ecran
* @param *vue
* @param *image : Image de degrade a dessiner
* @param x : Taille de l'ecran en largeur
* @param y : Taille de l'ecran en hauteur
*/
static inline XImage *config_fond(unsigned char *map, Display *d, Visual *vue, 
                                    const unsigned char *image, volatile unsigned short int x, 
                                    volatile unsigned short int y){
   /* Allocation dynamique de la surface a recouvrir */
   map = (unsigned char *)malloc(x*y*100);
   volatile unsigned char *tmp = map;
   /* Degrade de couleur a 3 niveau de nuance */
   for(volatile unsigned short int i=0; i<x; i++){
      for(volatile unsigned short int j=0; j<y; j++){
         for(volatile unsigned short int k=0; k<50; k++){
            *tmp ++= i%256;
            *tmp ++= k%1;
         }
      }
   }
   /* Creer l'image sur la profondeur de la fenetre sur l'ecran */
   return XCreateImage(d, vue, DefaultDepth(d, DefaultScreen(d)), 
                        ZPixmap, 0, map, x, y, 32, 0);
}

/**
* @function style
* Permet de génerer une couleur sur les Drawables et les polices.
* @param *d : Disposition par rapport a l'ecran
* @param couleur : code hexadecimal de la couleur
*/
extern const GC style(Display *d, const unsigned int couleur){
   static XGCValues gcv;
   gcv.foreground = couleur;
   /* retourne la composante de style graphique */
   return XCreateGC(d, DefaultRootWindow(d), GCForeground | GCBackground, &gcv);
}

/**
* @function config_generale
* Permet de disposer les differentes zones sur la fenetre principale,
* et de choisir leurs parametres d'affichage.
* @param *d : Disposition par rapport a l'ecran
* @param x : Taille de l'ecran en largeur
* @param y : Taille de l'ecran en hauteur
*/
static const XContext config_generale(Display * d, volatile unsigned short int x, 
                                       volatile unsigned short int y){
   /* Fenetre principale sur laquelle on affiche tous les composants */
   static Window f;
   /* Attribus la valeur des composant */
   static XGCValues gcv;
   /* Structure de la police de texte */
   static XFontStruct *police;
   /* contexte graphique */
   const XContext cx = XUniqueContext();

   /* Allocation de memoire pour les composants d'un canvas */
   volatile Zone *canvas = calloc(sizeof(*canvas), 1);

   /* Allocation des elements sur lesquels interagir */
   Element *data = malloc(sizeof(*data));

   /* Chargement de la police */
   police = XLoadQueryFont(d, "-*-courier-medium-r-normal-*-16-*-*-*-*-*-iso8859-1");
   gcv.foreground = 0xffffff;
   gcv.font = police->fid;

   /* Creation de la fenetre */
   f = XCreateSimpleWindow(d, DefaultRootWindow(d), 0, 0, x, y, 0, 
                              canvas->border, canvas->background);
   
   /* Donne a recuperer */
   data->font = police;
   data->d = d;
   data->f = f;

   /* Titre de la fenetre et de son onglet */
   Xutf8SetWMProperties(d, f, "T.H.A", "T.H.A", NULL, 0, NULL, NULL, NULL);

   /* Generer le style graphique */
   XChangeGC(d, GC(d), GCForeground | GCLineWidth | 
               GCLineStyle | GCFont, &gcv);

   /* Fenetre contenant le graphqiue */
   creer_graph(d, f, (x*30/100)-50, (y*20/100)+50, x/2, y/2, 0, 0x505050, cx);

   /* Fenetre contenant le bouton de sortie */
   creer_bouton(d, f, "Exit", police, (x/2)-40, (y-120), 80, (police->ascent + police->descent) * 2 + 5, 
                  0x400000, 0x303030, cx, quitter, data);

   /* Dire au serveur d'affichage quel type d'evenements que nous voulons avoir */
   XSelectInput(d, f, StructureNotifyMask | ExposureMask);
   /* Afficher la fenetre sur l'ecran. */
   XMapWindow(d, f);
   /* Conserver les informations du contexte graphique. */
   XSaveContext(d, f, cx, (XPointer)canvas);

   return cx;
}

/**
* @funcion affichage
* Permet de choisir quel type d'elements afficher,
* et sur quelle zone definie par un canvas.
* @param *canvas : Zone d'affichage
* @param *e : Evenement d'affichage
* @param x : Taille de l'ecran en largeur
* @param y : Taille de l'ecran en hauteur
*/
static void affichage(const Zone *canvas, const XEvent *e, XImage *ximage, Window *zone,
                        volatile unsigned short int x, volatile unsigned short int y){
   static unsigned char str[2];
   /* Bouton de sortie */
   if((canvas->texte) && (canvas->id == 0)){
      /* Texte du bouton */
      XDrawString16(e->xany.display, e->xany.window, GC(e->xany.display), 
                     (canvas->largeur - canvas->longueur)/2, (canvas->hauteur + canvas->police)/2,
                     canvas->texte, encodage(canvas->texte));
   /* Graphique */
   }else if(canvas->id == 1)
      tracer_graph(e->xany.display, e->xany.window);
   /* Fond */
   else{
      /* Fenetre racine (principale) */
      static Window racine;
      /* Parametres dimensionnels et de coordonnees */
      static int hauteur, largeur;
      static unsigned int abscisse, ordonnee, bordure, profondeur;
      /* Recentrage des elements dans la fenetre racine */
      XGetGeometry(e->xany.display, e->xany.window, &racine, &hauteur, &largeur, &abscisse, 
                     &ordonnee, &bordure, &profondeur);

      /* Image de fond */
      XPutImage(e->xany.display, e->xany.window, GC(e->xany.display), ximage, 0, 0, 0, 0, abscisse, ordonnee);

      /* Affichage du titre */
      XDrawString(e->xany.display, e->xany.window, GC(e->xany.display), 
                  (abscisse/2)-150, 50, "Temperature & Humidity Analyser", 31);
      /* Affichage de la date */
      XDrawString(e->xany.display, e->xany.window, GC(e->xany.display), 
                     (x/2)-90, 130, date(), 18);

      /* Menu de saisie des valeurs */
      menu_saisie(e, zone, y);
   }
}

static void interaction(Display *d, const XContext cx, XImage *ximage, 
                        volatile unsigned short int x, volatile unsigned short int y){
   /* A chaque envoie d'evenement, on envoie la reponse adequte du serveur. */
   while(1){
      static XEvent e;
      static Window zone[2];
      static Zone *canvas = NULL;
      /* Definir un evenement de maniere bloquante */
      XNextEvent(d, &e);
      XFindContext(e.xany.display, e.xany.window, cx, (XPointer*)&canvas);
      switch(e.type){
         case ConfigureNotify:
               config_canvas(canvas, &e);
         break;
         /* Afficher les composants graphiques dans la fenetre. */
         case Expose:
               affichage(canvas, &e, ximage, zone, x, y);
         break;
         /* Lors de la pression d'une touche. */
         case KeyPress :
            if(e.xkey.window == zone[0]){ saisie(&e, 0); }
            else if(e.xkey.window == zone[1]){ saisie(&e, 1); }
         break;
         /* Active la surbrillance, en additionnant par 0x101010 la couleur de fond actuelle. */
         case EnterNotify:
            survol_bouton(canvas, &e, 0x101010);
         break;
         /* Retablit la couleur de fond de bas en l'additionnant par 0. */
         case LeaveNotify:
            survol_bouton(canvas, &e, 0);
         break;
         /* Lors du relachement du bouton, on effectue les actions voulues. */
         case ButtonRelease:
            if(canvas->relachement)
               canvas->relachement(canvas->data);
         break;
      }
   }
}

/**
* @function rendu
* Fonction principale de l'interface graphique,
* permettant d'ouvrir la connexion au serveur,
* de disposer certaine mavcros principales,
* et de calculer la taille en plein ecran de l'ecran actuel.
*/
extern void interface(void){
   static Display *d;
   static const Screen *ecran;
   static unsigned char *map;

   /* Connexion au serveur*/
   if((d = XOpenDisplay(getenv("DISPLAY"))) == NULL)
      exit(1);

   /* Type de disposition de l'image de fond */
   Visual *vue = DefaultVisual(d, 0);
   if(vue->class != TrueColor){ exit(1); }

   /* Detecte la resolution de l'ecran */
   for(volatile unsigned short int i=0; i<ScreenCount(d); i++)
      ecran = ScreenOfDisplay(d, i);
   /* Stocke les dimensions dans les variables */
   volatile unsigned short int x = ecran->width - 5;
   volatile unsigned short int y = ecran->height;
   
   /* Taille minmale de deploiement sur ecran */
   if((x < 1080) && (y < 720)){
      x = 1080;
      y = 720;
   /* Taille maximale de deploiement sur ecran */
   }else if((x > 1920) && (y > 1080)){
      x = 1920;
      y = 1080;
   }

   /* Affichage de la fenetre et ses elements */
   interaction(d, config_generale(d, x, y), 
                  config_fond(map, d, vue, 0, x, y), x, y);

   free(map);
   /* Destruction de tous les elements */
   DestroyAll;
   /* Terminer la connexion au serveur */
   XCloseDisplay(d);
}
