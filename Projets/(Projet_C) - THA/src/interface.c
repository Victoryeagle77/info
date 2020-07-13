#include <pthread.h>
#include "../header/interface.h"
#include "../header/composant.h"
#include "../header/utilitaire.h"

static inline XImage *config_fond(unsigned char *map, Display *d, Visual *vue, const unsigned char *image, 
                                    volatile unsigned short int x, volatile unsigned short int y){
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

extern const GC style(Display *d, const unsigned int couleur){
   static XGCValues gcv;
   gcv.foreground = couleur;
   /* retourne la composante de style graphique */
   return XCreateGC(d, DefaultRootWindow(d), GCForeground | GCBackground, &gcv);
}

static const XContext config_generale(Display * d, volatile unsigned short int x, volatile unsigned short int y){
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
   f = XCreateSimpleWindow(d, DefaultRootWindow(d), 0, 0, x, y, 0, canvas->border, canvas->background);

   /* Donne a recuperer */
   data->font = police;
   data->d = d;
   data->f = f;

   /* Titre de la fenetre et de son onglet */
   Xutf8SetWMProperties(d, f, "T.H.A", "T.H.A", NULL, 0, NULL, NULL, NULL);

   /* Generer le style graphique */
   XChangeGC(d, GC(d), GCForeground | GCLineWidth | GCLineStyle | GCFont, &gcv);

   /* Fenetre contenant le graphqiue */
   creer_graph(d, f, (x*30/100)-50, (y*20/100)+50, x/2, y/2, 0, 0x101010, cx);

   /* Fenetre contenant le bouton de sortie */
   creer_bouton(d, f, "Exit", police, (x/2)-40, (y-120), 80, (police->ascent + police->descent) * 2 + 5, 
                  0x101010, 0x303030, cx, quitter, data);

   /* Dire au serveur d'affichage quel type d'evenements que nous voulons avoir */
   XSelectInput(d, f, StructureNotifyMask | ExposureMask);
   /* Afficher la fenetre sur l'ecran. */
   XMapWindow(d, f);
   /* Conserver les informations du contexte graphique. */
   XSaveContext(d, f, cx, (XPointer)canvas);

   return cx;
}

static void affichage(Display *d, const Zone *canvas, const XEvent *e, XImage *ximage, Window *zone,
                        volatile unsigned short int x, volatile unsigned short int y){
   static unsigned char str[2];

   /* Bouton de sortie */
   if((canvas->texte) && (canvas->id == 0))
      /* Texte du bouton */
      XDrawString16(d, e->xany.window, GC(d), (canvas->largeur - canvas->longueur)/2, 
                    (canvas->hauteur + canvas->police)/2, canvas->texte, encodage(canvas->texte));
   /* Graphique en temps reel */
   else if(canvas->id == 1){ tracer_graph(d, e->xany.window, 0); }
   /* Graphique de la base de donnees */
   else if(canvas->id == 2){ tracer_graph(d, e->xany.window, 1); }
   /* Fond */
   else{
      /* Image de fond */
      XPutImage(d, e->xany.window, GC(d), ximage, 0, 0, 0, 0, x, y);
      /* Affichage du titre */
      XDrawString(d, e->xany.window, GC(d), (x/2)-150, 50, "Temperature & Humidity Analyser", 31);
      /* Affichage de la date */
      XDrawString(d, e->xany.window, GC(d), (x/2)-90, 130, date(), 18);
      /* Menu de saisie des valeurs */
      menu_saisie(d, e, zone, y);
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
      XFindContext(d, e.xany.window, cx, (XPointer*)&canvas);
      XFlush(e.xany.display);
      switch(e.type){
         /* Conserver un aspect et une position correctes selon l'ecran */
         case ConfigureNotify :
            XMoveWindow(e.xany.display, e.xany.window, 0, 0);
            XResizeWindow(e.xany.display, e.xany.window, x, y);
            XFlush(e.xany.display);
         break;
         /* Afficher les composants graphiques dans la fenetre. */
         case Expose:
            affichage(d, canvas, &e, ximage, zone, x, y);
         break;
         /* Lors de la pression d'une touche. */
         case KeyPress :
            if(e.xkey.window == zone[0]){ saisie(d, &e, 0); }
            else if(e.xkey.window == zone[1]){ saisie(d, &e, 1); }
         break;
         /* Si l'on appuie sur le graphique */
         case ButtonPress:
            XClearArea(d, e.xany.window, 0, 0, x/2, y/2, 1);
            if(canvas->id == 1){ canvas->id = 2; }
            else if(canvas->id = 2){ canvas->id = 1; }
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

extern void interface(void){
   static Display *d;
   static const Screen *ecran;
   static char *map;
   static pthread_mutex_t mutex;

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
   
   /* Taille minmale de deploiement sur ecran : 960x540 */
   if(((x < 955) || (y < 540)) || (x < y)){ 
      free(map);
      /* Terminer la connexion au serveur */
      XCloseDisplay(d);
      exit(1);
   /* Taille maximale de deploiement sur ecran : 1920x1080 */
   }else if(x > 1920){ x = 1920; }
   else if(y > 1080){ y = 1080; }

   /* Securisation de l'execution multitache */
   pthread_mutex_lock(&mutex);
   /* Affichage de la fenetre et ses elements */
   interaction(d, config_generale(d, x, y), 
                  config_fond(map, d, vue, 0, x, y), x, y);
   /* Securisation de l'execution multitache */
   pthread_mutex_unlock(&mutex);

   free(map);
   /* Destruction de tous les elements */
   DestroyAll;
   /* Terminer la connexion au serveur */
   XCloseDisplay(d);
}
