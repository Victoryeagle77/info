#include "../header/interface.h"

extern void creer_bouton(Display *d, const Window racine, const char *texte, 
                           XFontStruct *font, const short int x, 
                           const short int y, const short int largeur, 
                           const short int hauteur, const unsigned int foreground, 
                           const unsigned int background, const unsigned int border, 
                           const XContext cx, const Reception reception, void *data){
   /* Creer une fenetre */
   const Window f = XCreateSimpleWindow(d, racine, x, y, largeur, 
                                          hauteur, 2, border, background);
   if(!(f)){ exit(1); }
  
   volatile Button *b = calloc(sizeof(*b), 1);
   if(!(b)){ exit(2); }
  
   b->font_ascent = font->ascent;
  
   b->texte = malloc(sizeof(*b->texte) * (strlen(texte)+1));
   if(!b->texte){ exit(2); }
	
   b->longueur = XTextWidth16(font, b->texte, decodage(b->texte, 
                                 strlen(texte), texte, strlen(texte)));

   /* Attribution du retour de clique sur bouton */
   b->relachement = reception;
   b->data = data;
   /* Attribution de la longueur et largeur du bouton et son texte */
   b->largeur = largeur;
   b->hauteur = hauteur;
   /* Attribut de decoration du bouton */
   b->background = background;
   b->border = border;

   /* Dire au serveur d'affichage quel type d'evenements que nous voulons avoir */
   XSelectInput(d, f, ButtonPressMask | ButtonReleaseMask | StructureNotifyMask 
                  | ExposureMask | LeaveWindowMask | EnterWindowMask);
   /* Afficher la sous fenetre sur la fenetre racine. */
   XMapWindow(d, f);
   /* Conserver les informations du contexte graphique. */
   XSaveContext(d, f, cx, (XPointer)b);
}

extern void survol_bouton(const Button *b, const XEvent *e){
   /* Attribu du bouton dans la fenetre */
   static XSetWindowAttributes a;
   /* Couleur de Fond remplacer par les bordures */
   a.border_pixel = 0x404040;
   /* Changement d'attribus par remplacement du jeu de couleur */
   XChangeWindowAttributes(e->xany.display, e->xany.window,
                           CWBackPixel|CWBorderPixel, &a);
   XClearArea(e->xany.display, e->xany.window, 0, 0,
              b->largeur, b->hauteur, True);
}

extern void pression_bouton(const Button *b, const XEvent *e){
   /* Attribu du bouton dans la fenetre */
   static XSetWindowAttributes a;
   /* Couleur de Fond */
   a.border_pixel = b->background;
   /* Changement d'attribus par remplacement du jeu de couleur */
   XChangeWindowAttributes(e->xany.display, e->xany.window,
                           CWBackPixel|CWBorderPixel, &a);
   XClearArea(e->xany.display, e->xany.window, 0, 0, 
              b->largeur, b->hauteur, True);
}
