/* Fonctions pour ouvrir et fermer le menu (en le faisant disparaître vers la gauche) */
function ouvnav() {
	document.getElementById('nav').style.marginLeft="0";
}
function fermnav() {
	document.getElementById('nav').style.marginLeft="-100%";
}

/* Ensembles de fonctions permettants l'animation du diaporama,
en fonction du nombre d'images entrés en dans les fichiers HTML */
var index = 1; /* index = 1 correspond à la visibilité d'un objet en html */
diaporama(index);
/* Permet à partir de l'index actuel de faire défiler les sildes */
function defile(x) { diaporama(index += x); }
/* Permet de dessiner des "points" servant d'indice du nombre de slide 
dans un diaporama. */
function curseur(x) { diaporama(index = x); }
/* Fonction principale */
function diaporama(x) {
  var i;
  var slides = document.getElementsByClassName("slides");
  var indicage = document.getElementsByClassName("position");
  if (x > slides.length) { index = 1 }  /* index d'origine d'une image */  
  if (x < 1) { index = slides.length } /* nombre de slides */
  /* Permet de faire disparaitre une slide avec l'index pour éviter qu'elles "s'emplient" */
  for (i = 0; i < slides.length; i++)
      slides[i].style.display = "none";  

  for (i = 0; i < indicage.length; i++)
      indicage[i].className = indicage[i].className.replace("active", "");
      /* Boutons interactifs d'action avancer et reculer */
  slides[index-1].style.display = "block";  
  indicage[index-1].className += " active";
}