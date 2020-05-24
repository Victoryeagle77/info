#include "../header/interface.h"
#include "../header/analyse.h"

extern volatile uint8_t donnee[5];

static volatile unsigned short int x, y;

static const unsigned long config_couleur(Display *d, const char *couleur){
   static XColor fond, surface;
   XAllocNamedColor(d, DefaultColormap(d, DefaultScreen(d)), 
                     couleur, &fond, &surface);
   return surface.pixel;
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

static const XContext config(Display * d){
   static volatile Window f;
   /* Attribus la valeur des composant */
   static XGCValues v;
   /* Structure de la police de texte */
   static XFontStruct * font;
   /* contexte graphique */
   const XContext cx = XUniqueContext();
   volatile Button *racine = calloc(sizeof(*racine), 1);

   /* Chargement de la police */
   font = config_police(d, "-*-times-medium-r-normal-*-16-*-*-*-*-*-*-*");
   racine->background = config_couleur(d, "#101010");
   racine->border = config_couleur(d, "#903030");
   racine->foreground = v.foreground = config_couleur(d, "#ffffff");
   
   static const Screen *ecran;
   /* Detecte la resolution de l'ecran */
   for(volatile unsigned short int i=0; i<ScreenCount(d); i++)
      ecran = ScreenOfDisplay(d, i);
   /* Stocke les dimensions dans les variables */
   x = ecran->width;
   y = ecran->height;
   /* Creation de la fenetre */
   f = XCreateSimpleWindow(d, DefaultRootWindow(d), 0, 0, 
                           x, y, 0, racine->border, racine->background);
   /* Style graphique */
   v.line_style = LineSolid;
   v.font = font->fid;
   
   /* Titre de la fenetre et de son onglet */
   Xutf8SetWMProperties(d, f, "T.H.A", "T.H.A", NULL, 0, NULL, NULL, NULL);

   XChangeGC(d, GC(d), GCForeground | GCLineWidth | 
               GCLineStyle | GCFont, &v);

   Sortie *data = malloc(sizeof(*data));
   data->d = d;
   data->font = font;

   creer_bouton(d, f, "Exit", font, (x/2)-40, (y*85/100), 80, 
                  (font->ascent + font->descent) * 2, racine->foreground, 
                  0x400000, racine->border, cx, quitter, data);

   /* tell the display server what kind of events we would like to see */
   XSelectInput(d, f, StructureNotifyMask | ExposureMask);
   /* okay, put the window on the screen, please */
   XMapWindow(d, f);

   /* save the useful information about the window */
   XSaveContext(d, f, cx, (XPointer)racine);

   return cx;
}

static void interface(const Button *b, const XEvent *e){
   static char str[255];
   if(b->text){
      /* Texte du bouton */
      XDrawString16(e->xany.display, e->xany.window, GC(e->xany.display), 
                     (b->largeur - b->text_width)/2, (b->hauteur + b->font_ascent)/2,
                     b->text, encodage(b->text));
   }else{
      XDrawString(e->xany.display, e->xany.window, GC(e->xany.display), 
                  (x/2)-120, 50, "Temperature & Humidity Analyser", 
                  strlen("Temperature & Humidity Analyser"));

      /* Date */
      date(str);
      XDrawString(e->xany.display, e->xany.window, GC(e->xany.display), 
                  (x/2)-60, 150, str, strlen(str));
      /* Humidite */
      sprintf(str, "%s%d%%", "Humidity : ", donnee[0]);
      XDrawString(e->xany.display, e->xany.window, GC(e->xany.display), 
               20, (y*40/100), str, strlen(str));
      /* Temperature */
      sprintf(str, "%s%d *C or %.1f *F", "Temperature : ",
               donnee[2], (donnee[2] * 9.0 / 5.0 + 32));
      XDrawString(e->xany.display, e->xany.window, GC(e->xany.display), 
                  20, (y*60/100), str, strlen(str));
   }
}

static void affichage(Display *d, const XContext cx){
   static XEvent e;
   /* A chaque envoie d'evenement, on envoie la reponse correspondante. */
   while(1){
      static Button *b = NULL;
      XNextEvent(d, &e);
      XFindContext(e.xany.display, e.xany.window, cx, (XPointer*)&b);
      
      usleep(5000);
      XClearArea(e.xany.display, e.xany.window, 0, 100, 250, y/2, True);
      switch(e.type){
         /* Afficher les composants graphiques dans la fenetre. */
         case Expose:
            if(b){ interface(b, &e); }
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
            if(b && b->relachement)
               b->relachement(b->data);
         break;
    }
  }
}

extern void menu(void){
   static Display *d;
   /* Connexion au serveur*/
   if((d = XOpenDisplay(getenv("DISPLAY"))) == NULL)
      exit(1);
   /* Affichage de la fenetre et ses elements */
   affichage(d, config(d));
}
