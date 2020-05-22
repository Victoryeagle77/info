#include "../header/interface.h"
#include "../header/analyse.h"

#define DefGC(dpy) DefaultGC(dpy, DefaultScreen(dpy))

extern volatile uint8_t donnee[5];

static volatile unsigned short int x, y;

static void quitter(void *data){
  Sortie *e = (Sortie*)data;
  /* Fermeture du flux generant la police */
  XFreeFont(e->d, e->font);
  /* Fermeture des fenetres */
  XCloseDisplay(e->d);
  exit(0);
}

static const uint_fast8_t legende(XChar2b *texte){
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

static inline XFontStruct *getFont(Display *d, char *def){
  static const XrmValue v;
  static char *type;
  static XFontStruct *police = NULL;

  if(v.addr)
    police = XLoadQueryFont(d, v.addr);

  /* Si la police de texte ne charge pas */
  if(!(police))
    police = XLoadQueryFont(d, def);

  return police;
}

static void creer_bouton(Display *d, const Window parent, const char *text, 
			  XFontStruct *font, const short int x, 
			  const short int y, const short int width, 
			  const short int height, const unsigned int foreground, 
			  const unsigned int background, const unsigned int border, 
			  const XContext cx, const Reception reception, void *data){
  static volatile Button *bouton;
  /* Creer une fenetre */
  const Window f = XCreateSimpleWindow(d, parent, x, y,
                                        width, height, 2, border, background);
  if(!(f)){ exit(1); }
  
  bouton = calloc(sizeof(*bouton), 1);
  if(!(bouton)){ exit(2); }
  
  bouton->font_ascent = font->ascent;
  
  bouton->text = malloc(sizeof(*bouton->text) * (strlen(text)+1));
  if(!bouton->text){ exit(2); }
	
  bouton->text_width = XTextWidth16(font, bouton->text, 
				    encodage(bouton->text, strlen(text), 
				    text, strlen(text)));
  /* Attribution du retour de clique sur bouton */
  bouton->buttonRelease = reception;
  bouton->data = data;
  /* Attribution de la longueur et largeur du bouton et son texte */
  bouton->width = width;
  bouton->height = height;
  /* Attribut de decoration du bouton */
  bouton->background = background;
  bouton->foreground = foreground;
  bouton->border = border;
  
  XSelectInput(d, f, ButtonPressMask | ButtonReleaseMask | 
	        StructureNotifyMask | ExposureMask |
		LeaveWindowMask | EnterWindowMask);
  XSaveContext(d, f, cx, (XPointer)bouton);
  XMapWindow(d, f);
}

static const XContext setup(Display * d){
  /* */
  static volatile Window f;
  /* Attribus la valeur des composant */
  static XGCValues v;
  
  static XFontStruct * font;
  volatile XrmDatabase db = XrmGetDatabase(d);
  
  const XContext cx = XUniqueContext();
  volatile Button *racine = calloc(sizeof(*racine), 1);
  
  /* Chargement de la police */
  font = getFont(d, "-*-times-medium-r-normal-*-16-*-*-*-*-*-*-*");
  racine->background = coloration(d, "#101010");
  racine->border = coloration(d, "#903030");
  racine->foreground = v.foreground = coloration(d, "#ffffff");
  
  static const Screen *ecran;
  /* Detecte la resolution de l'ecran */
  for(volatile unsigned short int i = 0; i < ScreenCount(d); i++)
    ecran = ScreenOfDisplay(d, i);
  /* Stocke les dimensions dans les variables */
  x = ecran->width;
  y = ecran->height;
  /* Creation de la fenetre */
  f = XCreateSimpleWindow(d, DefaultRootWindow(d),
                              0, 0, x, y, 0, racine->border, 
			      racine->background);
  /* make the default pen what we want */
  v.line_style = LineSolid;
  v.font = font->fid;
    
  XChangeGC(d, DefGC(d), GCForeground | GCLineWidth | 
	    GCLineStyle | GCFont, &v);
	
  Sortie *data = malloc(sizeof(*data));
  data->d = d;
  data->font = font;

  creer_bouton(d, f, "Exit", font, (x/2)-40, y-130, 80, 
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
  static unsigned char str[255];
  if(b->text){
    /* Texte du bouton */
    XDrawString16(e->xany.display, e->xany.window, DefGC(e->xany.display), 
                  (b->width - b->text_width)/2, (b->height + b->font_ascent)/2,
		   b->text, legende(b->text));
  }else{
    XDrawString(e->xany.display, e->xany.window, DefGC(e->xany.display), 
                x/2 - 110, 50, "Temperature & Humidity Analyser", 
		strlen("Temperature & Humidity Analyser"));
    /* Humidite */
    sprintf(str, "%s%d%%", "Humidity : ", donnee[0]);
    XDrawString(e->xany.display, e->xany.window, DefGC(e->xany.display), 
                  20, (30*y/100), str, strlen(str));
    /* Temperature */
    sprintf(str, "%s%d C or %.1f F", "Temperature : ", 
            donnee[2], (donnee[2] * 9.0 / 5.0 + 32));
    XDrawString(e->xany.display, e->xany.window, DefGC(e->xany.display), 
	        20, (60*y/100), str, strlen(str));
   /* XClearArea(e->xany.display, e->xany.window, 0, 0, 
              b->width, b->height, True); */
  }
}

static void configuration_bouton(volatile Button *b, volatile XEvent *e){
  if((b->width != e->xconfigure.width)
      || (b->height != e->xconfigure.height)){
    b->width = e->xconfigure.width;
    b->height = e->xconfigure.height;
    XClearWindow(e->xany.display, e->xany.window);
  }
}

static void pression_bouton(const Button *b, const XEvent *e){
  static XSetWindowAttributes a;
  a.background_pixel = b->border;
  a.border_pixel = b->background;
  XChangeWindowAttributes(e->xany.display, e->xany.window,
			  CWBackPixel|CWBorderPixel, &a);
  XClearArea(e->xany.display, e->xany.window, 0, 0, 
              b->width, b->height, True);
}

static void survol_bouton(const Button *b, const XEvent *e){
  static XSetWindowAttributes a;
  a.background_pixel = b->background;
  a.border_pixel = b->border;
  XChangeWindowAttributes(e->xany.display, e->xany.window,
			  CWBackPixel|CWBorderPixel, &a);
  XClearArea(e->xany.display, e->xany.window, 0, 0, 
              b->width, b->height, True);
}

static void affichage(Display *d, const XContext cx){
  static XEvent e;
  /* as each event that we asked about occurs, we respond. */
  while(1){
    Button *button = NULL;
    XNextEvent(d, &e);
    XFindContext(e.xany.display, e.xany.window, 
                  cx, (XPointer*)&button);
    switch(e.type){
      /* configure notify will only be sent to the main window */
      case ConfigureNotify:
        if(button){ configuration_bouton(button, &e); }
      break;
      /* expose will be sent to both the button and the main window */
      case Expose:
        if(button){ interface(button, &e); }
      break;
      /* these three events will only be sent to the button */
      case EnterNotify:
	if(button){ pression_bouton(button, &e); }
      break;
      case LeaveNotify:
        if(button){ survol_bouton(button, &e); }
      break;
      case ButtonRelease:
        if(button && button->buttonRelease)
	    button->buttonRelease(button->data);
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
  affichage(d, setup(d));
}
