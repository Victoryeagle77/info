#include "../header/interface.h"

static void creer_canvas(Display *d, const Window racine, const Window f, volatile Zone *canvas,
                           const unsigned short int x, const unsigned short int y, const unsigned short int largeur,
                           const unsigned short int hauteur, const unsigned int background, const unsigned int border,
                           const unsigned int mask, const XContext cx, const uint_fast8_t id){

   /* Dire au serveur d'affichage quel type d'evenements que nous voulons avoir */
   XSelectInput(d, f, mask);
   /* Afficher la sous fenetre sur la fenetre racine. */
   XMapWindow(d, f);

   /* Attribu d'un id pour le contenu de la fenetre */
   canvas->id = id;

   /* Attribution de la longueur et largeur de la fenetre */
   canvas->largeur = largeur;
   canvas->hauteur = hauteur;
   
   /* Attribu de style de la fenetre */
   canvas->background = background;
   canvas->border = border;

   /* Conserver les informations du contexte graphique. */
   XSaveContext(d, f, cx, (XPointer)canvas);
}

extern void creer_bouton(Display *d, const Window racine, const char *texte,
                           XFontStruct *font, const short int x, const short int y,
                           const short int largeur, const short int hauteur, const unsigned int background,
                           const unsigned int border, const XContext cx, const Reception reception, void *data){
   /* Creer une fenetre */
   const Window f = XCreateSimpleWindow(d, racine, x, y, largeur, 
                                          hauteur, 2, border, background);

   /* Allocation du canvas en fonction des composants a y afficher */
   volatile Zone *canvas = calloc(sizeof(*canvas), 1);

   /* Parametre texte d'un bouton */
   canvas->police = font->ascent;
   canvas->texte = malloc(sizeof(*canvas->texte) * (strlen(texte)+1));
   canvas->longueur = XTextWidth16(font, canvas->texte, decodage(canvas->texte, 
                                    strlen(texte), texte, strlen(texte)));

   /* Attribution du retour de clic de la fenetre */
   canvas->relachement = reception;
   /* Donnees a liberer lors de la sortie de programme */
   canvas->data = data;

   /* Principaux elements du canvas */
   creer_canvas(d, racine, f, canvas, x, y, largeur, hauteur, background, border,
                  ButtonPressMask | ButtonReleaseMask | StructureNotifyMask | ExposureMask | 
                  LeaveWindowMask | EnterWindowMask, cx, 0);
}

extern void creer_graph(Display *d, const Window racine, const unsigned short int x,
                           const unsigned short int y, const unsigned short int largeur,
                           const unsigned short int hauteur, const unsigned int background,
                           const unsigned int border, const XContext cx){

   /* Allocation du canvas en fonction des composants a y afficher */
   volatile Zone *canvas = calloc(sizeof(*canvas), 1);

   /* Creer une fenetre */
   const Window f = XCreateSimpleWindow(d, racine, x, y, largeur,
                                          hauteur, 2, border, background);

   /* Principaux elements du canvas */
   creer_canvas(d, racine, f, canvas, x, y, largeur, hauteur, border, 
                  background, StructureNotifyMask | ExposureMask, cx, 1);
}

extern void config_canvas(Zone *canvas, const XEvent *e){
	if((canvas->largeur != e->xconfigure.width)
			|| (canvas->hauteur != e->xconfigure.height)){
		canvas->largeur = e->xconfigure.width;
		canvas->hauteur = e->xconfigure.height;
      /* Effacer et reafficher le contenu a chaque modification de taille */
		XClearWindow(e->xany.display, e->xany.window);
	}
}

extern void active_bouton(const Zone *canvas, const XEvent *e){
   /* Attribu du canvas dans la fenetre */
   static XSetWindowAttributes a;
   /* Couleur de fond */
   a.background_pixel = canvas->border;
   a.border_pixel = canvas->background;
   /* Changement d'attribus par remplacement du jeu de couleur */
   XChangeWindowAttributes(e->xany.display, e->xany.window,
                           CWBackPixel | CWBorderPixel, &a);
   XClearArea(e->xany.display, e->xany.window, 0, 0,
              canvas->largeur, canvas->hauteur, 1);
}

extern void desactive_bouton(const Zone *canvas, const XEvent *e){
   /* Attribu du canvas dans la fenetre */
   static XSetWindowAttributes a;
   /* Couleur des bordures */
   a.background_pixel = canvas->background;
	a.border_pixel = canvas->border;
   /* Changement d'attribus par remplacement du jeu de couleur */
   XChangeWindowAttributes(e->xany.display, e->xany.window,
                           CWBackPixel | CWBorderPixel, &a);
   XClearArea(e->xany.display, e->xany.window, 0, 0,
              canvas->largeur, canvas->hauteur, 1);
}
