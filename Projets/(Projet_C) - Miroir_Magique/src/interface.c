#include "../header/interface.h"
#include "../header/analyse.h"

#define DefGC(dpy) DefaultGC(dpy, DefaultScreen(dpy))

extern volatile uint8_t donnee[5];
static volatile unsigned short int x, y;

typedef void (*Reception)(void *data);

/* Structure definissant un bouton */
volatile typedef struct Button Button;
struct Button{
  XChar2b *text;
  volatile unsigned short int text_width,
    font_ascent, width, height;
  unsigned long border, background, foreground;
  void *data;
  volatile Reception buttonRelease;
};

/* Structure definissant l'action de sortie */
typedef struct sortie Sortie;
struct sortie {
  Display *dpy;
  XFontStruct *font;
};

static void exitButton(void *data){
  Sortie *e = (Sortie*)data;
  /* Fermeture du flux generant la police */
  XFreeFont(e->dpy, e->font);
  /* Fermeture des fenetres */
  XCloseDisplay(e->dpy);
  exit(0);
}

static const uint8_t legende(XChar2b *texte){
  static volatile uint8_t i=0;
  for(i=0; (texte[i].byte1) || (texte[i].byte2); i++);
  return i;
}

static const uint8_t encodage(volatile XChar2b *affiche, 
			      const uint8_t debordement, const char *saisie, 
			      const uint8_t chaine){
  static volatile uint8_t i, j;
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

static void creer_bouton(Display *d, Window parent, char *text, XFontStruct *font,
		int x, int y, int width, int height, unsigned long foreground, 
		unsigned long background, unsigned long border, XContext cx,
		Reception reception, void *data){
  static volatile Button *button;
  /* Creer une fenetre */
  const Window f = XCreateSimpleWindow(d, parent, x, y, width, height,
                                        2, border, background);
  if(!(f)){ exit(1); }
  
  button = calloc(sizeof(*button), 1);
  if(!(button)){ exit(2); }
  
  button->font_ascent = font->ascent;
  
  button->text = malloc(sizeof(*button->text) * (strlen(text)+1));
  if(!button->text){ exit(2); }
	
  button->text_width = XTextWidth16(font, button->text, 
				    encodage(button->text, strlen(text), 
				    text, strlen(text)));
  /* Attribution du retour de clique sur bouton */
  button->buttonRelease = reception;
  button->data = data;
  /* Attribution de la longueur et largeur du bouton et son texte */
  button->width = width;
  button->height = height;
  
  button->background = background;
  button->foreground = foreground;
  button->border = border;
  
  XSelectInput(d, f, ButtonPressMask | ButtonReleaseMask | 
	        StructureNotifyMask | ExposureMask |
		LeaveWindowMask | EnterWindowMask);
  XSaveContext(d, f, cx, (XPointer)button);
  XMapWindow(d, f);
}

static const XContext setup(Display * dpy){
  /* */
  static volatile Window win;
  /* Attribus la valeur des composant */
  static XGCValues v;
  
  static XFontStruct * font;
  static volatile XrmDatabase db;
  
  const XContext cx = XUniqueContext();
  volatile Button *racine = calloc(sizeof(*racine), 1);
  
  db = XrmGetDatabase(dpy);
  /* Chargement de la police */
  font = getFont(dpy, "-*-times-medium-r-normal-*-16-*-*-*-*-*-*-*");
  racine->background = coloration(dpy, "#200000");
  racine->border = coloration(dpy, "#303030");
  racine->foreground = v.foreground = coloration(dpy, "#ffffff");
  
  static const Screen *ecran;
  /* Detecte la resolution de l'ecran */
  for(volatile unsigned short int i = 0; i < ScreenCount(dpy); i++)
    ecran = ScreenOfDisplay(dpy, i);
  /* Stocke les dimensions dans les variables */
  x = ecran->width;
  y = ecran->height;
  /* Creation de la fenetre */
  win = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy),
                              0, 0, x, y, 0, racine->border, 
			      racine->background);
    /* make the default pen what we want */
    v.line_style = LineSolid;
    v.font = font->fid;
    
    XChangeGC(dpy, DefGC(dpy), GCForeground | GCLineWidth | 
              GCLineStyle | GCFont,&v);
	
	static Sortie *sortie;
	sortie = malloc(sizeof(*sortie));
	sortie->dpy = dpy;
	sortie->font = font;
  
	creer_bouton(dpy, win, "Quitter", font,
		(ecran->width/2)-40, (ecran->height)-130, 80, 
		(font->ascent+font->descent)*2, racine->foreground, 
		racine->background, racine->border, cx, exitButton, sortie);
	

	/* tell the display server what kind of events we would like to see */
	XSelectInput(dpy, win, StructureNotifyMask|ExposureMask);
	/* okay, put the window on the screen, please */
	XMapWindow(dpy, win);

	/* save the useful information about the window */
	XSaveContext(dpy, win, cx, (XPointer)racine);

	return cx;
}

static void interface(const Button *b, const XEvent *e){
  static unsigned char str[255];
  if(b->text){
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
                  20, (y/2) - 70, str, strlen(str));
    /* Temperature */
    sprintf(str, "%s%d C or %.1f F", "Temperature : ", 
            donnee[2], (donnee[2] * 9.0 / 5.0 + 32));
    XDrawString(e->xany.display, e->xany.window, DefGC(e->xany.display), 
	        20, (y/2) + 70, str, strlen(str));
    
    //XClearArea(e->xany.display, x/2, 40, 5, 50, 50, 1);
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
  XSetWindowAttributes a;
  a.background_pixel = b->border;
  a.border_pixel = b->background;
  XChangeWindowAttributes(e->xany.display, e->xany.window,
			  CWBackPixel|CWBorderPixel, &a);
  XClearArea(e->xany.display, e->xany.window, 0, 0, 
              b->width, b->height, True);
}

static void survol_bouton(const Button *b, const XEvent *e){
  XSetWindowAttributes a;
  a.background_pixel = b->background;
  a.border_pixel = b->border;
  XChangeWindowAttributes(e->xany.display, e->xany.window,
			  CWBackPixel|CWBorderPixel, &a);
  XClearArea(e->xany.display, e->xany.window, 0, 0, 
              b->width, b->height, True);
}

static void affichage(Display *dpy, XContext context){
  static XEvent ev;
  /* as each event that we asked about occurs, we respond. */
  while(1){
    Button *button = NULL;
    XNextEvent(dpy, &ev);
    XFindContext(ev.xany.display, ev.xany.window, context, (XPointer*)&button);
    switch(ev.type){
      /* configure notify will only be sent to the main window */
      case ConfigureNotify:
        if(button){ configuration_bouton(button, &ev); }
      break;
	    /* expose will be sent to both the button and the main window */
	    case Expose:
		  if(button){ interface(button, &ev); }
	    break;
	    /* these three events will only be sent to the button */
	    case EnterNotify:
	      if(button){ pression_bouton(button, &ev); }
	    break;
	    case LeaveNotify:
		if(button){ survol_bouton(button, &ev); }
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
