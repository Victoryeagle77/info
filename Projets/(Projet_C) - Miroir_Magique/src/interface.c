#include "../header/interface.h"

extern volatile uint8_t donnee[5];

/**
* @function *config_fond
* Permet d'effectuer un degrade de couleur, 
* par rapport aux parametres suivant :
* @param *map : surface a recouvrir
* @param *d : disposition par rapport a l'ecran
* @param *vue
* @param *image : image de degrade a dessiner
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
   for(volatile uint16_t i=0; i<x; i++){
      for(volatile uint16_t j=0; j<y; j++){
         for(volatile uint16_t k=0; k<50; k++){
            *tmp ++= i%256;
            *tmp ++= k%1;
         }
      }
   }
   /* Creer l'image sur la profondeur de la fenetre sur l'ecran */
   return XCreateImage(d, vue, DefaultDepth(d, DefaultScreen(d)), 
                        ZPixmap, 0, map, x, y, 32, 0);
}

static inline XFontStruct *config_police(Display *d, const char *nom){
   static const XrmValue v;
   static XFontStruct *police = NULL;

   /* Si on utilise l'adresse pour genere une police */
   if(v.addr)
      police = XLoadQueryFont(d, v.addr);

   /* Si la police de texte ne charge pas par son adresse */
   if(!(police))
      police = XLoadQueryFont(d, nom);

   return police;
}

extern const GC style(Display *d, const unsigned int couleur){
   static XGCValues gcv;
   gcv.foreground = couleur;
   /* retourne la composante de style graphique */
   return XCreateGC(d, DefaultRootWindow(d), GCForeground | GCBackground 
                        | GCLineWidth | GCLineStyle, &gcv);
}

/**
* @function config_generale
* Permet de disposer les differentes zones sur la fenetre principale,
* et de choisir leurs parametres d'affichage.
* @param *d : disposition par rapport a l'ecran
* @param x : Taille de l'ecran en largeur
* @param y : Taille de l'ecran en hauteur
*/
static const XContext config_generale(Display * d, volatile unsigned short int x, 
                                       volatile unsigned short int y){
   /* Fenetre principale sur laquelle on affiche tous les composants */
   static Window racine;
   /* Attribus la valeur des composant */
   static XGCValues gcv;
   /* Structure de la police de texte */
   static XFontStruct *police;
   /* contexte graphique */
   const XContext cx = XUniqueContext();

   /* Allocation de memoire pour les composants d'un canvas */
   volatile Zone *canvas = calloc(sizeof(*canvas), 1);
   /* Allocation de memoire pour les elements a detruire */
   Sortie *data = malloc(sizeof(*data));

   /* Chargement de la police */
   police = config_police(d, "-*-courier-medium-r-normal-*-16-*-*-*-*-*-iso8859-1");
   gcv.foreground = 0xffffff;
   gcv.font = police->fid;
   /* Parametre du bouton de sortie */
   data->font = police;
   data->d = d;

   /* Creation de la fenetre */
   racine = XCreateSimpleWindow(d, DefaultRootWindow(d), 0, 0, x, y, 0, 
                              canvas->border, canvas->background);

   /* Titre de la fenetre et de son onglet */
   Xutf8SetWMProperties(d, racine, "T.H.A", "T.H.A", NULL, 0, NULL, NULL, NULL);

   /* Generer le style graphique */
   XChangeGC(d, GC(d), GCForeground | GCLineWidth | 
               GCLineStyle | GCFont, &gcv);

   /* Fenetre contenant le graphqiue */
   creer_graph(d, racine, (x*30/100)-50, (y*20/100)+50, x/2, y/2, cx);

   /* Fenetre contenant le bouton de sortie */
   creer_bouton(d, racine, "Exit", police, (x/2)-40, (y-120), 80, 
                  (police->ascent + police->descent) * 2 + 5,
                  0x803030, 0x404040, cx, quitter, data);

   /* Dire au serveur d'affichage quel type d'evenements que nous voulons avoir */
   XSelectInput(d, racine, StructureNotifyMask | ExposureMask | KeyPressMask);
   /* Afficher la fenetre sur l'ecran. */
   XMapWindow(d, racine);
   /* Conserver les informations du contexte graphique. */
   XSaveContext(d, racine, cx, (XPointer)canvas);

   return cx;
}

/**
* @funcion affichage
* Permet de choisir quel type d'elements afficher,
* et sur quelle zone definie par un canvas.
* @param *canvas : Zone d'affichage
* @param *e : evenement
* @param x : Taille de l'ecran en largeur
* @param y : Taille de l'ecran en hauteur
*/
static void affichage(const Zone *canvas, const XEvent *e, 
                        volatile unsigned short int x, volatile unsigned short int y){
   static char str[2];
   /* Bouton de sortie */
   if((canvas->texte) && (canvas->id == 0)){
      /* Texte du bouton */
      XDrawString16(e->xany.display, e->xany.window, GC(e->xany.display), 
                     (canvas->largeur - canvas->longueur)/2, (canvas->hauteur + canvas->police)/2,
                     canvas->texte, encodage(canvas->texte));
   /* Graphique */
   }else if(canvas->id == 1){
      Pixmap pix = XCreatePixmap(e->xany.display, e->xany.window, x/2, y/2,
                                 XDefaultDepth(e->xany.display, DefaultScreen(e->xany.display)));
      XCopyArea(e->xany.display, e->xany.window, pix, GC(e->xany.display), 
                  0, 0, x/2, y/2, 0, 0);
      tracer_graph(e->xany.display, pix);
   /* Fond */
   }else{
      /* Affichage du titre */
      XDrawString(e->xany.display, e->xany.window, GC(e->xany.display), 
                  (x/2)-150, 50, "Temperature & Humidity Analyser", 31);
      /* Affichage de la date */
      date(str);
      XDrawString(e->xany.display, e->xany.window, GC(e->xany.display), 
                  (x/2)-90, 130, str, 18);
   }
}

static void interaction(Display *d, const XContext cx, XImage *ximage, 
                        volatile unsigned short int x, volatile unsigned short int y){
   /* A chaque envoie d'evenement, on envoie la reponse adequte du serveur. */
   while(1){
      static XEvent e;
      static Zone *canvas = NULL;
      XNextEvent(d, &e);
      XFindContext(e.xany.display, e.xany.window, cx, (XPointer*)&canvas);
      switch(e.type){
         case ConfigureNotify:
               config_canvas(canvas, &e);
         break;
         /* Afficher les composants graphiques dans la fenetre. */
         case Expose:
            /* Image de fond */
            XPutImage(e.xany.display, e.xany.window, GC(e.xany.display),
                        ximage, 0, 0, 0, 0, x, y);
            affichage(canvas, &e, x, y);
         break;
         /* Active la surbrillance, inversion des couleurs du fond et des bordures,
         lorsque l'on entre dans la zone definissant le bouton. */
         case EnterNotify:
            pression_bouton(canvas, &e);
         break;
         /* La surbrillance, inversion des couleurs du fond et des bordures,
         s'enleve lorsque l'on quitte la zone definissant le bouton. */
         case LeaveNotify:
            survol_bouton(canvas, &e);
         break;
         /* Lors du relachement du bouton, on effectue les actions voulues. */
         case ButtonRelease:
            if(canvas->relachement)
               canvas->relachement(canvas->data);
         break;
      }
   }
}

extern void menu(void){
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
   volatile unsigned short int x = ecran->width;
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
