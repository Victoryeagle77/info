#include "../header/interface.h"
#include "../header/analyse.h"

extern volatile uint8_t donnee[5];

static volatile unsigned short int x, y;

static void quitter(void *data){
   Sortie *e = (Sortie*)data;
   /* Fermeture du flux generant la police */
   XFreeFont(e->d, e->font);
   /* Fermeture des fenetres */
   XCloseDisplay(e->d);
   free(e);
   exit(0);
}

static const uint_fast8_t legende(const XChar2b *texte){
   static volatile uint_fast8_t i=0;
   for(i=0; (texte[i].byte1) || (texte[i].byte2); i++);
   return i;
}

static const uint_fast8_t encodage(volatile XChar2b *affiche, 
                                    const uint_fast8_t debordement, 
                                    const char *saisie, const uint_fast8_t chaine){
   static volatile uint_fast8_t i, j;
   for(i=0, j=0; (i<chaine) && (j<debordement); i++){
      if(saisie[i] < 128){
         affiche[j].byte1 = 0;
         affiche[j].byte2 = saisie[i]; 
         j++;
      }
   }
   return j;
}

static const unsigned long coloration(Display *d, const char *couleur){
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

static void creer_bouton(Display *d, const Window parent, const char *text, 
                           XFontStruct *font, const short int x, 
                           const short int y, const short int largeur, 
                           const short int hauteur, const unsigned int foreground, 
                           const unsigned int background, const unsigned int border, 
                           const XContext cx, const Reception reception, void *data){
   static volatile Button *b;
   /* Creer une fenetre */
   const Window f = XCreateSimpleWindow(d, parent, x, y,
                                       largeur, hauteur, 2, border, background);
   if(!(f)){ exit(1); }
  
   b = calloc(sizeof(*b), 1);
   if(!(b)){ exit(2); }
  
   b->font_ascent = font->ascent;
  
   b->text = malloc(sizeof(*b->text) * (strlen(text)+1));
   if(!b->text){ exit(2); }
	
   b->text_width = XTextWidth16(font, b->text, encodage(b->text, 
                                 strlen(text), text, strlen(text)));
   /* Attribution du retour de clique sur bouton */
   b->relachement = reception;
   b->data = data;
   /* Attribution de la longueur et largeur du bouton et son texte */
   b->largeur = largeur;
   b->hauteur = hauteur;
   /* Attribut de decoration du bouton */
   b->background = background;
   b->foreground = foreground;
   b->border = border;
  
   XSelectInput(d, f, ButtonPressMask | ButtonReleaseMask | 
                 StructureNotifyMask | ExposureMask |
                 LeaveWindowMask | EnterWindowMask);
   XSaveContext(d, f, cx, (XPointer)b);
   XMapWindow(d, f);
}

static const XContext configuration(Display * d){
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
   racine->background = coloration(d, "#101010");
   racine->border = coloration(d, "#903030");
   racine->foreground = v.foreground = coloration(d, "#ffffff");
   
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

   creer_bouton(d, f, "Exit", font, (x/2)-40, (short int)(y*85/100), 80, 
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

static void survol_bouton(const Button *b, 
                           const XEvent *e){
   /* Attribu du bouton dans la fenetre */
   static XSetWindowAttributes a;
   /* Couleur de Fond remplacer par les bordures */
   a.background_pixel = b->background;
   a.border_pixel = b->border;
   /* Changement d'attribus par remplacement du jeu de couleur */
   XChangeWindowAttributes(e->xany.display, e->xany.window,
                           CWBackPixel|CWBorderPixel, &a);
   XClearArea(e->xany.display, e->xany.window, 0, 0, 
              b->largeur, b->hauteur, True);
}

static void pression_bouton(const Button *b, 
                             const XEvent *e){
   /* Attribu du bouton dans la fenetre */
   static XSetWindowAttributes a;
   /* Couleur de Fond */
   a.background_pixel = b->border;
   a.border_pixel = b->background;
   /* Changement d'attribus par remplacement du jeu de couleur */
   XChangeWindowAttributes(e->xany.display, e->xany.window,
                           CWBackPixel|CWBorderPixel, &a);
   XClearArea(e->xany.display, e->xany.window, 0, 0, 
              b->largeur, b->hauteur, True);
}

static void interface(const Button *b, const XEvent *e){
   static char str[255];
   if(b->text){
      /* Texte du bouton */
      XDrawString16(e->xany.display, e->xany.window, GC(e->xany.display), 
                     (b->largeur - b->text_width)/2, (b->hauteur + b->font_ascent)/2,
                     b->text, legende(b->text));
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
      usleep(10000);
      XClearArea(e.xany.display, e.xany.window, 0, 0, 300, b->largeur, True);
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
   affichage(d, configuration(d));
}
