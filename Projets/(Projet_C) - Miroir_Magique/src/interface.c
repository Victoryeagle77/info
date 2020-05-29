#include "../header/interface.h"
#include "../header/analyse.h"

extern volatile uint8_t donnee[5];

static inline XImage *config_fond(unsigned char *map, Display *d, Visual *vue, 
                                    const unsigned char *image, volatile unsigned short int x, 
                                    volatile unsigned short int y){
   map = (unsigned char *)malloc(x*y*100);
   volatile unsigned char *tmp = map;
   for(volatile uint16_t i=0; i<x; i++){
      for(volatile uint16_t j=0; j<y; j++){
         for(volatile uint16_t k=0; k<50; k++){
            *tmp ++= i%256;
            *tmp ++= k%1;
         }
      }
   }
   return XCreateImage(d, vue, DefaultDepth(d, DefaultScreen(d)), 
                        ZPixmap, 0, map, x, y, 32, 0);
}

static inline XFontStruct *config_police(Display *d, char *nom){
   static const XrmValue v;
   static char *type;
   static XFontStruct *police = NULL;

   if(v.addr)
      police = XLoadQueryFont(d, v.addr);

   /* Si la police de texte ne charge pas */
   if(!(police))
      police = XLoadQueryFont(d, nom);

   return police;
}

static const XContext config_generale(Display * d, volatile unsigned short int x, 
                                       volatile unsigned short int y){
   static volatile Window f;
   /* Attribus la valeur des composant */
   static XGCValues gcv;
   /* Structure de la police de texte */
   static XFontStruct * font;
   /* contexte graphique */
   const XContext cx = XUniqueContext();

   volatile Button *src = calloc(sizeof(*src), 1);
   Sortie *data = malloc(sizeof(*data));

   /* Chargement de la police */
   font = config_police(d, "-*-courier-medium-r-normal-*-16-*-*-*-*-*-iso8859-1");
   gcv.foreground = 0xffffff;
   gcv.font = font->fid;
   /* Parametre bouton */
   data->d = d;
   data->font = font;

   /* Creation de la fenetre */
   f = XCreateSimpleWindow(d, DefaultRootWindow(d), 0, 0, x, y, 0, 
                              src->border, src->background);

   /* Titre de la fenetre et de son onglet */
   Xutf8SetWMProperties(d, f, "T.H.A", "T.H.A", NULL, 0, NULL, NULL, NULL);

   XChangeGC(d, GC(d), GCForeground | GCLineWidth | 
               GCLineStyle | GCFont, &gcv);

   creer_bouton(d, f, "Exit", font, (x/2)-40, (y-150), 80, 
                  (font->ascent + font->descent) * 2 + 5, 0,
                  0x803030, 0x404040, cx, quitter, data);

   /* Dire au serveur d'affichage quel type d'evenements que nous voulons avoir */
   XSelectInput(d, f, ExposureMask | KeyPressMask);
   /* Afficher la fenetre sur l'ecran. */
   XMapWindow(d, f);
   /* Conserver les informations du contexte graphique. */
   XSaveContext(d, f, cx, (XPointer)src);
   
   return cx;
}

static void afficher(const Button *b, const XEvent *e, 
                        volatile unsigned short int x, volatile unsigned short int y){
   static char str[2];
   if(b->texte){
      /* Texte du bouton */
      XDrawString16(e->xany.display, e->xany.window, GC(e->xany.display), 
                     (b->largeur - b->longueur)/2, (b->hauteur + b->font_ascent)/2,
                     b->texte, encodage(b->texte));
   }else{
      tracer_fonction(e->xany.display, e->xany.window, x/2, y/2);
      XDrawString(e->xany.display, e->xany.window, GC(e->xany.display), 
                  (x/2)-150, 70, "Temperature & Humidity Analyser", 
                  strlen("Temperature & Humidity Analyser"));

      /* Date */
      date(str);
      XDrawString(e->xany.display, e->xany.window, GC(e->xany.display), 
                  (x/2)-80, 150, str, strlen(str));

      tracer_fonction(e->xany.display, e->xany.window, x/2, y/2);
   }
}

static void interaction(Display *d, const XContext cx, XImage *ximage, 
                        volatile unsigned short int x, volatile unsigned short int y){
   static XEvent e;
   /* A chaque envoie d'evenement, on envoie la reponse correspondante. */
   while(1){
      static Button *b = NULL;
      XNextEvent(d, &e);
      XFindContext(e.xany.display, e.xany.window, cx, (XPointer*)&b);
      switch(e.type){
         /* Afficher les composants graphiques dans la fenetre. */
         case Expose:
            XPutImage(e.xany.display, e.xany.window, GC(e.xany.display),
                        ximage, 0, 0, 0, 0, x, y);
            if(b){ afficher(b, &e, x, y); }
         break;
         /* Active la surbrillance, inversion des couleurs du fond et des bordures,
         lorsque l'on entre dans la zone definissant le bouton. */
         case EnterNotify:
            if(b){ pression_bouton(b, &e); }
         break;
         /* La surbrillance, inversion des couleurs du fond et des bordures,
         s'enleve lorsque l'on quitte la zone definissant le bouton. */
         case LeaveNotify:
            if(b){ survol_bouton(b, &e); }
         break;
         /* Lors du relachement du bouton, on effectue les actions voulues. */
         case ButtonRelease:
            if((b) && (b->relachement))
               b->relachement(b->data);
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

   /* Affichage de la fenetre et ses elements */
   interaction(d, config_generale(d, x, y), 
               config_fond(map, d, vue, 0, x, y), x, y);
   free(map);
}
