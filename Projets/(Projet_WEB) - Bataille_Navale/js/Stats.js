/*** Fonction qui évalue les statistiques des tirs joueurs effecutés ***/
class Stats{
    constructor(){
		this.tir_subis = 0;
		this.tir_touche = 0;

		/* Conversion en entier des item stocké dans les coockies de la page,
		que l'on récupére. */
		this.total_tirs = parseInt(localStorage.getItem('total_tirs'), 10) || 0;
		this.total_dommages = parseInt(localStorage.getItem('total_dommages'), 10) || 0;
		this.lance_jeu = parseInt(localStorage.getItem('lance_jeu'), 10) || 0;
		this.victoire = parseInt(localStorage.getItem('victoire'), 10) || 0;

		/* Vérification de la compatibilté des variables */
		if(DEBUG_MODE){ this.tmp = true; }
	}

	/* Prototype de la fonction Stats qui gère la synchronisation des statistiques */
	sync(){
		let grille_valeur = '';

		if(!(this.tmp)){
			let total_tirs = parseInt(localStorage.getItem('total_tirs'), 10) || 0;
			total_tirs += this.tir_subis;

			let total_dommages = parseInt(localStorage.getItem('total_dommages'), 10) || 0;
			total_dommages += this.tir_touche;

			/* Charger les valeurs suivante dans les items stockés dans les coockies de la page */
			localStorage.setItem('total_tirs', total_tirs);
			localStorage.setItem('total_dommages', total_dommages);
			localStorage.setItem('victoire', this.victoire);
		}else{ this.tmp = false; }

		/* Mise en place des cases */
		for(let x = 0; x < 10; x++){
			/* Dessin de la grille */
			for(let y = 0; y < 10; y++)
				grille_valeur += '(' + x + ',' + y + '):' +
			jeu.grille_joueur.coordonnees[x][y] + ';\n';
		}
		if (!DEBUG_MODE) { ga('send', 'event', 'grille_joueur', grille_valeur); }
	}
	
	/* Prototype de la fonction Stats qui gère les points de vie de la flotte. */
	pv(){ this.tir_subis++; }

	/* Prototype de la fonction Stats qui gère les points de vie de la flotte ennemie. */
	scoring(){ this.tir_touche++; }

	/* Prototype de la fonction Stats qui gère la victoire du jeu */
	gagne(){
		this.lance_jeu++; this.victoire++;
		/* Vérification du debug mode avec Google Analytics */
		if (!DEBUG_MODE){ ga('send', 'event', 'jeu_perdu', 'win'); }
	}

	/* Prototype de la fonction Stats qui gère la défaite du jeu */
	perd(){
		this.lance_jeu++;
		/* Vérification du debug mode avec Google Analytics */
		if (!(DEBUG_MODE)){ ga('send', 'event', 'jeu_perdu', 'lose'); }
	}
}