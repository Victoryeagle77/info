#include "../header/interface.h"

static void creer_canvas(Display *d, const Window racine, const Window f, volatile Zone *canvas,
                           const unsigned short int x, const unsigned short int y, const unsigned short int largeur,
                           const unsigned short int hauteur, const unsigned int background, const unsigned int border,
                           const unsigned int mask, const XContext cx, const uint_fast8_t id){
   /* Dire au serveur d'affichage quel type d'evenements que nous voulons avoir */
   XSelectInput(d, f, mask);
   /* Afficher la sous fenetre sur la fenetre racine. */
   XMapWindow(d, f);
   /* Conserver les informations du contexte graphique. */
   XSaveContext(d, f, cx, (XPointer)canvas);

   /* Attribu d'un id pour le contenu de la fenetre */
   canvas->id = id;
   /* Attribution de la longueur et largeur de la fenetre */
   canvas->largeur = largeur;
   canvas->hauteur = hauteur;
   /* Attribu de style de la fenetre */
   canvas->background = background;
   canvas->border = border;
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
                  StructureNotifyMask | ExposureMask | EnterWindowMask | 
                  LeaveWindowMask | ButtonReleaseMask, cx, 0);
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
                  background, StructureNotifyMask | ExposureMask | ButtonPressMask, cx, 1); 
}

extern void menu_saisie(Display *d, const XEvent *e,  Window *zone, volatile unsigned short int y){
   /* Bar a gauche de l'ecran */
   volatile Window container = XCreateSimpleWindow(d, e->xany.window, 0, 0, 200, y, 0, 0xffffff, 0x151515);  
   XMapWindow(d, container);

   /* Zones de saisie interactives */
   for(volatile unsigned short int i=0; i<2; i++){
      zone[i] = XCreateSimpleWindow(d, container, 25, 150 + i*80, 145, 30, 2, 0x707070, 0x404040); 
      XSelectInput(d, zone[i], KeyPressMask);  
      XMapWindow(d, zone[i]);
   }

   /* Legendes et titres des zones de saisies */
   XDrawString(d, container, GC(d), 55, 30, "Keyboard", 8);
   XDrawString(d, container, style(d, 0xffffff), 25, 140, "Temperature (0 to 50)", 21);
   XDrawString(d, container, style(d, 0xffffff), 25, 220, "Humidity (20 to 80)", 19);

   /* Consignes graphe */
   XDrawString(d, container, style(d, 0xaaaaaa), 25, 300, "Click on graph to change", 24);
   XDrawString(d, container, style(d, 0xaaaaaa), 25, 320, "the analysing mode.", 19);
   /* Consignes saisie */
   XDrawString(d, container, style(d, 0xcc0000), 25, y-140, "You can enter maximum of", 24);
   XDrawString(d, container, style(d, 0xcc0000), 25, y-120, "temperature and humidity", 24);
   XDrawString(d, container, style(d, 0xcc0000), 25, y-100, "to don't exceed.", 16);
   XDrawString(d, container, style(d, 0xcc0000), 25, y-80, "Press Enter to confirm.", 23);
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

extern void survol_bouton(const Zone *canvas, const XEvent *e, const unsigned int nuance){
   /* Attribu du canvas dans la fenetre */
   static XSetWindowAttributes a;
   /* Couleur de fond */
   a.background_pixel = canvas->background + nuance;
   /* Bordures */
   a.border_pixel = canvas->border;
   /* Changement d'attribus par remplacement du jeu de couleur */
   XChangeWindowAttributes(e->xany.display, e->xany.window,
                           CWBackPixel | CWBorderPixel, &a);
   XClearArea(e->xany.display, e->xany.window, 0, 0,
               canvas->largeur, canvas->hauteur, 1);
}
