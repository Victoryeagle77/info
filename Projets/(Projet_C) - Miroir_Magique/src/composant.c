#include "../header/interface.h"

extern void creer_bouton(Display *d, const Window racine, const char *texte, 
                           XFontStruct *font, const short int x, 
                           const short int y, const short int largeur, 
                           const short int hauteur, const unsigned int background, 
                           const unsigned int border, const XContext cx, 
                           const Reception reception, void *data){
   /* Creer une fenetre */
   const Window f = XCreateSimpleWindow(d, racine, x, y, largeur, 
                                          hauteur, 2, border, background);

   /* Allocation du canvas en fonction des composants a y afficher */
   volatile Zone *canvas = calloc(sizeof(*canvas), 1);

   canvas->police = font->ascent;

   /* Attribu d'un id pour le contenu de la fenetre */
   canvas->id = 0;

   canvas->texte = malloc(sizeof(*canvas->texte) * (strlen(texte)+1));
   canvas->longueur = XTextWidth16(font, canvas->texte, decodage(canvas->texte, 
                                    strlen(texte), texte, strlen(texte)));

   /* Attribution du retour de clic de la fenetre */
   canvas->relachement = reception;
   /* Donnees a liberer lors de la sortie de programme */
   canvas->data = data;
   /* Attribution de la longueur et largeur de la fenetre */
   canvas->largeur = largeur;
   canvas->hauteur = hauteur;
   /* Attribu de decoration de la fenetre */
   canvas->background = background;
   canvas->border = border;

   /* Dire au serveur d'affichage quel type d'evenements que nous voulons avoir */
   XSelectInput(d, f, ButtonPressMask | ButtonReleaseMask | StructureNotifyMask 
                  | ExposureMask | LeaveWindowMask | EnterWindowMask);
   /* Afficher la sous fenetre sur la fenetre racine. */
   XMapWindow(d, f);
   /* Conserver les informations du contexte graphique. */
   XSaveContext(d, f, cx, (XPointer)canvas);
}

extern void creer_graph(Display *d, const Window racine, const short int x, 
                           const short int y, const short int largeur, 
                           const short int hauteur, const XContext cx){
   /* Creer une fenetre */
   const Window f = XCreateSimpleWindow(d, racine, x, y, largeur, 
                                          hauteur, 2, 0xaaaaaa, 0);

   /* Allocation du canvas en fonction des composants a y afficher */
   volatile Zone *canvas = calloc(sizeof(*canvas), 1);

   /* Attribu d'un id pour le contenu de la fenetre */
   canvas->id = 1;

   /* Attribution de la longueur et largeur de la fenetre */
   canvas->largeur = largeur;
   canvas->hauteur = hauteur;

   /* Dire au serveur d'affichage quel type d'evenements que nous voulons avoir */
   XSelectInput(d, f, StructureNotifyMask | ExposureMask);
   /* Afficher la sous fenetre sur la fenetre racine. */
   XMapWindow(d, f);
   /* Conserver les informations du contexte graphique. */
   XSaveContext(d, f, cx, (XPointer)canvas);
}

extern void config_canvas(Zone *canvas, XEvent *e){
	if((canvas->largeur != e->xconfigure.width)
			|| (canvas->hauteur != e->xconfigure.height)){
		canvas->largeur = e->xconfigure.width;
		canvas->hauteur = e->xconfigure.height;
      /* Effacer et reafficher le contenu a chaque modification de taille */
		XClearWindow(e->xany.display, e->xany.window);
	}
}

extern void survol_bouton(const Zone *canvas, const XEvent *e){
   /* Attribu du canvas dans la fenetre */
   static XSetWindowAttributes a;
   /* Couleur des bordures */
   a.border_pixel = 0x404040;
   /* Changement d'attribus par remplacement du jeu de couleur */
   XChangeWindowAttributes(e->xany.display, e->xany.window,
                           CWBackPixel | CWBorderPixel, &a);
   XClearArea(e->xany.display, e->xany.window, 0, 0,
              canvas->largeur, canvas->hauteur, 1);
}

extern void pression_bouton(const Zone *canvas, const XEvent *e){
   /* Attribu du canvas dans la fenetre */
   static XSetWindowAttributes a;
   /* Couleur de fond */
   a.border_pixel = canvas->background;
   /* Changement d'attribus par remplacement du jeu de couleur */
   XChangeWindowAttributes(e->xany.display, e->xany.window,
                           CWBackPixel | CWBorderPixel, &a);
   XClearArea(e->xany.display, e->xany.window, 0, 0,
              canvas->largeur, canvas->hauteur, 1);
}
