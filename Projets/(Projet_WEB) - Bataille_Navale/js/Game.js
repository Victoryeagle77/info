/* Définition d'éléments constants */	
let CONST = {};
CONST.FLOTTE = ['porte_avions', 'croiseur', 'destroyer', 'sous_marin', 'patrouilleur'];
/* Paramètre des différents joueurs */
CONST.JOUEUR = 0; 
CONST.IA = 1;
/* Définition de CSS lié à l'état d'une case de la grille */
CONST.STYLE_VIDE = 'empty';
CONST.STYLE_NAVIRE = 'ship';
CONST.STYLE_RATE = 'miss';
CONST.STYLE_TOUCHE = 'hit';
CONST.STYLE_COULE = 'sunk';
/* Constante d'état d'une case de la grille de jeu */
CONST.VIDE = 0;
CONST.NAVIRE = 1;
CONST.RATE = 2;
CONST.TOUCHE = 3;
CONST.COULE = 4;

class Game{
	constructor(){
		this.tir_subis = 0;
		this.grille_jeu();
		this.init();
		this.jeu_perdu = false;
	}

	/* Gère l'intégration de la perte ou de la victoire d'une partie. */
	etat(){
		if(this.flotte_ia.flotte_detruite()){
			/* Message d'alerte javascript */
			alert('Bravo, destruction de la flotte ennemie !');
			Game.jeu_perdu = true;
			/* Synchronisation du statut de victoire */
			Game.stats.gagne();
			Game.stats.sync();
			this.menu_rejouer();
		}else if(this.flotte_joueur.flotte_detruite()){
			alert('Perdu, destruction de votre flotte');
			Game.jeu_perdu = true;
			/* Synchronisation du statut de défaite */
			Game.stats.perd();
			Game.stats.sync();
			this.menu_rejouer();
		}
	}

    /* Détermine la grille et la flotte cible dans le cas ou le joueur est l'IA ou le joueur.
    On distingue ainsi la flotte allié à ne pas toucher. */
	tir(x, y, joueur_cible){
		let grille_cible, flotte_cible;
		if(joueur_cible == CONST.JOUEUR){
			grille_cible = this.grille_joueur;
			flotte_cible = this.flotte_joueur;
		}else if(joueur_cible == CONST.IA){
			grille_cible = this.grille_ia;
			flotte_cible = this.flotte_ia;
		}

		/* Etat des bateaux selon leur coordonnées */
		if(grille_cible.navire_endommage(x, y)){ return null; }
		else if(grille_cible.navire_evite(x, y)){ return null; }
		else if(grille_cible.navire_sauf(x, y)){
			grille_cible.curseur(x, y, 'hit', joueur_cible);
			/* Détecter et localiser la présence d'un bateau par ses coordonnées */
			flotte_cible.localisation(x, y).score_degats();
			this.etat();
			return CONST.TOUCHE;
		}else{
			grille_cible.curseur(x, y, 'miss', joueur_cible);
			this.etat();
			return CONST.RATE;
		}
	}

	/* Permet de lier le statut des tirs au score et point de vie */
	tir_param(e){
		let self = e.target.self;
        /* Axe de rotation d'un élément attribué en abscisse et ordonnée,
        converti en coordonnées entiére, (rotation d'un navire) */
		let x = parseInt(e.target.getAttribute('data-x'), 10);
		let y = parseInt(e.target.getAttribute('data-y'), 10);
		let res = null;
		if(self.operationnel){ res = self.tir(x, y, CONST.IA); }
		if((res != null) && (!(Game.jeu_perdu))){
			/* Inventaire des points de vie des navires */
			Game.stats.pv();
			if(res == CONST.TOUCHE){ Game.stats.scoring(); }
			self.auto.tir();
		}else{ Game.jeu_perdu = false; }
	}

    /* Assure la lisaison entre les éléments graphiques de CSS et de JS.
    Le design des sprits de bateaux sont liés par leur classes CSS aux JS. */
	flotte_param(e){
		let self = e.target.self;
		/* Selectionner la classe CSS correspondante */
		let flotte = document.querySelectorAll('.fleet-roster li');
		for(let i = 0; i < flotte.length; i++){
			/* Obtenir les classes CSS */
			let classes = flotte[i].getAttribute('class') || '';
			classes = classes.replace('placing', '');
			flotte[i].setAttribute('class', classes);
		}
		/* Obtenir les id CSS */
		Game.place_navire = e.target.getAttribute('id');
		document.getElementById(Game.place_navire).setAttribute('class', 'placing');
		/* Obtenir par l'id CSS le bouton de rotation du positionnement des navires */
		Game.place_direction = parseInt(document.getElementById('rotate-button').getAttribute('data-direction'), 10);
		self.place_grille = true;
	}

	/* Gère l'affichage du menu commencer en fonction des navires placés sur la grille. */
	place_param(e){
		let self = e.target.self;
		if (self.place_grille) {
			let x = parseInt(e.target.getAttribute('data-x'), 10);
			let y = parseInt(e.target.getAttribute('data-y'), 10);
			let atteinte = self.flotte_joueur.pos_navire(x, y, Game.place_direction, Game.place_navire);
			if(atteinte){
				self.place_final(Game.place_navire);
				self.place_grille = false;
				/* Pour tous les bateaux placés sur la grille */
				if(self.grille_remplie()){
					let e = document.getElementById('rotate-button');
					e.addEventListener(animation(),
						(function () {
							e.setAttribute('class', 'hidden');
                            /* Caché l'élément de bouton commencer,
                            tant que tous les navvires ne sont pas placés. */
							document.getElementById('start-game').removeAttribute('class');
						}), false);
					e.setAttribute('class', 'invisible');
				}
			}
		}
	}
	
	/* Survol des cases par la souris */
	survol_curseur(e){
		let self = e.target.self;
		if(self.place_grille){
			let x = parseInt(e.target.getAttribute('data-x'), 10);
			let y = parseInt(e.target.getAttribute('data-y'), 10);
			let classes;
			let flotte = self.flotte_joueur.artillerie;

			for(let i = 0; i < flotte.length; i++){
				let type_navire = flotte[i].type;

				if((Game.place_navire == type_navire) &&
					(flotte[i].borne(x, y, Game.place_direction))){
					flotte[i].positionner(x, y, Game.place_direction, true);
					Game.navire_coords = flotte[i].taille_navire();

					for(let j = 0; j < Game.navire_coords.length; j++){
						let e = document.querySelector('.grid-cell-' + Game.navire_coords[j].x + '-' + Game.navire_coords[j].y);
						classes = e.getAttribute('class');
						if(classes.indexOf(' grid-ship') < 0){
							classes += ' grid-ship';
							e.setAttribute('class', classes);
						}
					}
				}
			}
		}
	}

	/* Gère le canvas de la souris qui ne peut interagir uniquement dans la grille. */
	sortie_curseur(e){
		let classes;
		let cible = e.target.self;
		if(cible.place_grille){
			for(let j = 0; j < Game.navire_coords.length; j++){
				let e = document.querySelector('.grid-cell-' + Game.navire_coords[j].x
					+ '-' + Game.navire_coords[j].y);
				classes = e.getAttribute('class');
				if(classes.indexOf(' grid-ship') > -1){
					classes = classes.replace(' grid-ship', '');
					e.setAttribute('class', classes);
				}
			}
		}
	}

	/* Gère la rotation d'un navire */
	rotation(e){
		let direction = parseInt(e.target.getAttribute('data-direction'), 10);
		/* Direcion horizontale initialisé à 1 */
		if(direction == Ship.DIRECTION_VERTICAL){
			e.target.setAttribute('data-direction', '1');
			Game.place_direction = Ship.DIRECTION_HORIZONTAL;
			/* Direcion verticale initialisé à 0 */
		}else if(direction == Ship.DIRECTION_HORIZONTAL){
			e.target.setAttribute('data-direction', '0');
			Game.place_direction = Ship.DIRECTION_VERTICAL;
		}
	}

	commence_jeu(e){
		let self = e.target.self;
		var e = document.getElementById('roster-sidebar');

		e.addEventListener(animation(), e.setAttribute('class', 'hidden'), false);
		e.setAttribute('class', 'invisible');
		self.operationnel = true;
		e.removeEventListener(animation(), e.setAttribute('class', 'hidden'), false);
	}
	
	recommence_jeu(e){
		let self = e.target.self;
		document.getElementById('restart-sidebar').setAttribute('class', 'hidden');
		self.chargement();
		self.init();
	}
	
	/* Détermine lorsqu'un bateau est placé sur la grille après clique */
	place_final(type_navire){
		document.getElementById(type_navire).setAttribute('class', 'placed');
		Game.flotte_valide[CONST.FLOTTE.indexOf(type_navire)] = CONST.VALIDE;
		Game.place_direction = null;
		Game.place_navire = '';
		Game.navire_coords = [];
	}
	
	/* Détermine quand la grille est pleine (5 navires placés) */
	grille_remplie(){
		let navires = document.querySelectorAll('.fleet-roster li');
		for(let i = 0; i < navires.length; i++){
			if(navires[i].getAttribute('class') == 'placed'){ continue; }
			else{ return false; }
		}
		Game.place_direction = 0;
		Game.place_navire = '';
		Game.navire_coords = [];
		return true;
	}
	
	/* Chargement de la grille du joueur et de l'ia */
	chargement(){
		for(let i = 0; i < 10; i++){
			for(let j = 0; j < 10; j++){
				this.grille_joueur.curseur(i, j, 'empty', CONST.JOUEUR);
				this.grille_ia.curseur(i, j, 'empty', CONST.IA);
			}
		}
		Game.flotte_valide = Game.flotte_valide.map(function () { return CONST.INVALIDE; });
	}

    /* Permet de gérer le menu pour rejouer.
    lorsque tous les navires ennemis ou de alliés sont détruits. */
	menu_rejouer(){
		document.getElementById('restart-sidebar').setAttribute('class', '');

		let cases = document.querySelector('.computer-player').childNodes;
		for(let j = 0; j < cases.length; j++)
			cases[j].removeEventListener('click', this.tir_param, false);

		/* Créé une liste correspondant aux 5 types de bateaux pouvant être placés. */
		let flotte_joueur = document.querySelector('.fleet-roster').querySelectorAll('li');
		for(let i = 0; i < flotte_joueur.length; i++)
			flotte_joueur[i].removeEventListener('click', this.flotte_param, false);

		/* Bouton recommencer */
		document.getElementById('restart-game').addEventListener('click', this.recommence_jeu, false);
		document.getElementById('restart-game').self = this;
	}

	/* Prototype de la fonction Game qui permet de gérer la grille de jeu */
	grille_jeu(){
		let cases = document.querySelectorAll('.grid');
		for(let grille = 0; grille < cases.length; grille++){
			cases[grille].removeChild(cases[grille].querySelector('.error'));
			for(let i = 0; i < 10; i++){ /* Lignes */
				for(let j = 0; j < 10; j++){ /* Colonnes */
					let e = document.createElement('div');
					/* Attribuer les valeurs de rotations initiales en abscisse et ordonnée */
					e.setAttribute('data-x', i); e.setAttribute('data-y', j);
					e.setAttribute('class', 'grid-cell grid-cell-' + i + '-' + j);
					cases[grille].appendChild(e);
				}
			}
		}
	}

	/* Initialiser le jeu et tous les paramètres qui lui sont associés */
	init(){
		this.grille_joueur = new Grid(10);
		this.grille_ia = new Grid(10);
		this.flotte_joueur = new Fleet(this.grille_joueur, CONST.JOUEUR);
		this.flotte_ia = new Fleet(this.grille_ia, CONST.IA);
		this.auto = new AI(this);

		Game.stats = new Stats();

		this.tir_subis = 0;
		this.operationnel = false;
		this.place_grille = false;

		Game.place_direction = 0;
		Game.place_navire = '';
		Game.navire_coords = [];

		/* Réinitialiser la bar de placement de la flotte */
		let e = document.querySelector('.fleet-roster').querySelectorAll('li');
		for(let i = 0; i < e.length; i++){ e[i].removeAttribute('class'); }
		/* Transition par suppression des éléments */
		document.getElementById('roster-sidebar').removeAttribute('class');
		document.getElementById('rotate-button').removeAttribute('class');
		document.getElementById('start-game').setAttribute('class', 'hidden');

		let cases_ia = document.querySelector('.computer-player').childNodes;
		for(let i = 0; i < cases_ia.length; i++){
			cases_ia[i].self = this;
			cases_ia[i].addEventListener('click', this.tir_param, false);
		}

		let cases_joueur = document.querySelector('.human-player').childNodes;
		for(let i = 0; i < cases_joueur.length; i++){
			cases_joueur[i].self = this;
			cases_joueur[i].addEventListener('click', this.place_param, false);
			cases_joueur[i].addEventListener('mouseover', this.survol_curseur, false);
			cases_joueur[i].addEventListener('mouseout', this.sortie_curseur, false);
		}

		let flotte_navale = document.querySelector('.fleet-roster').querySelectorAll('li');
		for(let i = 0; i < flotte_navale.length; i++){
			flotte_navale[i].self = this;
			flotte_navale[i].addEventListener('click', this.flotte_param, false);
		}

		document.getElementById('rotate-button').addEventListener('click', this.rotation, false);

		document.getElementById('start-game').self = this;
		document.getElementById('start-game').addEventListener('click', this.commence_jeu, false);
		this.flotte_ia.gen_pos();
	}
}

/* Déclarer le jeu */
let jeu = new Game();