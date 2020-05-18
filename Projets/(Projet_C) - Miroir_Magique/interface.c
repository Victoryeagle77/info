#include "../header/interface.h"
#include "../header/analyse.h"

static volatile unsigned short int x = 300, y = 300;
static Display *disposition;
static Window fenetre;
static GC canvas;
static XFontStruct *fd;

extern volatile uint8_t donnee[5];

static void configuration(void){
   /* Connexion au serveur*/
   if((disposition = XOpenDisplay(getenv("DISPLAY"))) == NULL){
      puts("Erreur : Connexion serveur");
      exit(1);
   }
   /* Creer une fenetre */
   fenetre = XCreateSimpleWindow(
      disposition, RootWindow(disposition, DefaultScreen(disposition)),
      0, 0, x, y, 0, 
      BlackPixel(disposition, DefaultScreen(disposition)), 20);

   /* Chargement d'une police de caracteres*/
   if((fd = XLoadQueryFont(disposition, "-*-helvetica-medium-r-normal-*-13-*-*-*-*-*-*-*")) == NULL){
      puts("Erreur : Chargement police");
      exit(1);
   }
}

static void initialiser(void){
   static XGCValues gcv;
   
   configuration();
   
   /* Mise en place de la structure de la police */
   gcv.font = fd->fid;
   /* Couleur de fond de la police */
   gcv.foreground = WhitePixel(disposition, DefaultScreen(disposition));
   /* Container des éléments graphiques */
   canvas = XCreateGC(disposition, fenetre, GCFont | GCForeground, &gcv);
   /* Afficher la fenetre */
   XMapWindow(disposition, fenetre);
   /* Titre de la fenetre */
   XStoreName(disposition, fenetre, "Sonde");
   /* Afficher les composants graphiques au lancement */
   XSelectInput(disposition, fenetre, ExposureMask);
}

static void modeliser(void){
   static unsigned char str[6];
   static volatile unsigned short int i=0;
   static uint8_t temperature;
   
   while(1){
      sprintf(str, "%d", donnee[0]);
      XDrawString(disposition, fenetre, canvas, x/2, 40,
         str, strlen(str));

      XDrawString(disposition, fenetre, canvas, 10, 20,
         "Analayse de Temperature", strlen("Analayse de Temperature"));
      XDrawString(disposition, fenetre, canvas, 10, (y/2) - 30,
         "Humidity : ", strlen("Humidity :"));
      XDrawString(disposition, fenetre, canvas, 10, (y/2) + 30,
         "Temperature : ", strlen("Temperature :"));
   }
}

extern void affichage(void){
   initialiser();
   modeliser();
}
