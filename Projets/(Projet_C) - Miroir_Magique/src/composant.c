#include "../header/interface.h"

extern void creer_bouton(Display *d, const Window parent, const char *text, 
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
	
   b->text_width = XTextWidth16(font, b->text, decodage(b->text, 
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

extern void survol_bouton(const Button *b, 
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

extern void pression_bouton(const Button *b, 
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
