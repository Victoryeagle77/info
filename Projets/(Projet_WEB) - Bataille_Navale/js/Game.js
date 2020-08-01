/* Définition de constantes à l'individualisation des cases de jeu */	
let CONST = {};
CONST.FLOTTE = ['porte_avions', 'croiseur', 'destroyer', 'sous_marin', 'patrouilleur'];
/* Paramètre des différents joueurs */
CONST.JOUEUR = 0; CONST.IA = 1; CONST.ADVERSAIRE = 2;
/* Définition de CSS lié à l'état d'une case de la grille */
CONST.STYLE_VIDE = 'empty';
CONST.STYLE_NAVIRE = 'ship';
CONST.STYLE_RATE = 'miss';
CONST.STYLE_TOUCHE = 'hit';
CONST.STYLE_COULE = 'sunk';
/* Constante d'état d'une case de la grille de jeu */
CONST.VIDE = 0; CONST.NAVIRE = 1; 
CONST.RATE = 2; CONST.TOUCHE = 3; 
CONST.COULE = 4; 
	
/* Initialisation de la flotte des navires utilisés au départ (c'est à dire aucun) */
Game.flotte_valide = [0, 0, 0, 0, 0];

/*** Fonction déterminant le jeu, actions joueurs et initialisations grille ***/
function Game(dimension) {
	Game.dimension = dimension;
	this.tir_subis = 0;
	this.grille_jeu(); this.init();
}
	/* Dimension de la grille de jeu */
	Game.dimension = 10; 
	/* Booléen d'état de jeu perdu */
    Game.jeu_perdu = false;
    
	/* Prototype de la fonction Game,
	qui gère l'intégration de la perte ou de la victoire d'une partie. */
	Game.prototype.etat = function() {
		if(this.flotte_ia.flotte_detruite()) {
			/* Message d'alerte javascript */
			alert('Bravo, flotte ennemie détruite');
			Game.jeu_perdu = true;
			/* Synchronisation du statut de victoire */
			Game.stats.gagne(); Game.stats.sync();
			this.menu_rejouer();
		} else if(this.flotte_joueur.flotte_detruite()) {
			alert('Perdu, votre flotte a été détruite');
			Game.jeu_perdu = true;
			/* Synchronisation du statut de défaite */
			Game.stats.perd(); Game.stats.sync();
			this.menu_rejouer();
		}
    };
    
	/* Prototype de la fonction Game, 
	qui détermine la grille et la flotte cible,
	dans le cas ou le joueur est l'IA ou le joueur.
	On distingue ainsi la flotte allié à ne pas toucher. */
	Game.prototype.tir = function(x, y, joueur_cible) {
		let grille_cible, flotte_cible;
		if(joueur_cible === CONST.JOUEUR) {
			grille_cible = this.grille_joueur;
			flotte_cible = this.flotte_joueur;
		} else if(joueur_cible === CONST.IA) {
			grille_cible = this.grille_ia;
			flotte_cible = this.flotte_ia;
		}
		/* Etat des bateaux selon leur coordonnées */
		if(grille_cible.navire_endommage(x, y)){ return null; }
		else if(grille_cible.navire_evite(x, y)){ return null; }
		else if(grille_cible.navire_sauf(x, y)){
			grille_cible.curseur(x, y, 'hit', joueur_cible);
			/* Détecter et localiser la présence d'un bateau par ses coordonnées */
			flotte_cible.localisation(x, y).dommages_scoring(); 
			this.etat();
			return CONST.TOUCHE;
		}else{
			grille_cible.curseur(x, y, 'miss', joueur_cible);
			this.etat();
			return CONST.RATE;
		}
    };
    
	/* Prototype de la fonction Game, 
	qui permet de lié le statut des tirs au score et point de vie */ 
	Game.prototype.tir_param = function(e) {
		let self = e.target.self;
		/* Axe de rotation d'un élément attribué en abscisse et ordonnée,
		converti en coordonnées entiére, (rotation d'un navire) */
		let x = parseInt(e.target.getAttribute('data-x'), 10);
		let y = parseInt(e.target.getAttribute('data-y'), 10);
		let res = null;
		if(self.operationnel)
			res = self.tir(x, y, CONST.IA);
		if(res !== null && !Game.jeu_perdu){
			/* Inventaire des points de vie des navires */
			Game.stats.pv();
			if (res === CONST.TOUCHE){ Game.stats.scoring(); }
			self.auto.tir();
		} else { Game.jeu_perdu = false; }
    };
    
	/* Prototype de la fonction Game, 
	qui assure la lisaison entre les éléments graphiques de CSS et de JS.
	Le design des sprits de bateaux sont liés par leur classes CSS aux JS. */
	Game.prototype.flotte_param = function(e){
		let self = e.target.self;
		/* Selectionner la classe CSS correspondante */
		let flotte = document.querySelectorAll('.fleet-roster li');
		for(let i = 0; i < flotte.length; i++) {
			/* Obtenir les classes CSS */
			let classes = flotte[i].getAttribute('class') || '';
			classes = classes.replace('placing', '');
			flotte[i].setAttribute('class', classes);
		}
		/* Obtenir les id CSS */
		Game.place_navire = e.target.getAttribute('id');
		document.getElementById(Game.place_navire).setAttribute('class', 'placing');
		/* Obtenir par l'id CSS le bouton de rotation du positionnement des navires */
		Game.place_direction = parseInt(document.getElementById('rotate-button')
			.getAttribute('data-direction'), 10);
		self.place_grille = true;
    };
    
	/* Prototype de la fonction Game, 
	qui gère l'affichage du menu commencer en fonction des navires placés sur la grille. */
	Game.prototype.place_param = function(e){
		let self = e.target.self;
		if(self.place_grille) {
			let x = parseInt(e.target.getAttribute('data-x'), 10);
			let y = parseInt(e.target.getAttribute('data-y'), 10);
			let atteinte = self.flotte_joueur.pos_navire(x, y, Game.place_direction, Game.place_navire);
			if(atteinte) {
				self.place_final(Game.place_navire);
				self.place_grille = false;
				/* Pour tous les bateaux placés sur la grille */
				if(self.grille_remplie()) {
					let e = document.getElementById('rotate-button');
                    e.addEventListener(animation(),
                        (function(){
							e.setAttribute('class', 'hidden');
							/* Caché l'élément de bouton commencer,
							tant que tous les navvires ne sont pas placés. */
							if(menu_jeu.defile)
								document.getElementById('start-game').setAttribute('class');
							else
								document.getElementById('start-game').removeAttribute('class');	
						}), false);
					e.setAttribute('class', 'invisible');
				}
			}
		}
    };
    
    /* Prototype de la fonction Game qui gère */
	Game.prototype.mouse_ouver = function(e) {
		let self = e.target.self;
		if(self.place_grille) {
			let x = parseInt(e.target.getAttribute('data-x'), 10);
			let y = parseInt(e.target.getAttribute('data-y'), 10);
			let classes;
			let flotte = self.flotte_joueur.fleetRoster;

			for(let i = 0; i < flotte.length; i++) {
				let type_navire = flotte[i].type;

				if(Game.place_navire === type_navire &&
					flotte[i].isLegal(x, y, Game.place_direction)) {
                        flotte[i].create(x, y, Game.place_direction, true);
					Game.navire_coords = flotte[i].getAllShipCells();
                    
					for(let j = 0; j < Game.navire_coords.length; j++) {
                        let e = document.querySelector('.grid-cell-' + Game.navire_coords[j].x + '-' + Game.navire_coords[j].y);
						classes = e.getAttribute('class');
						if(classes.indexOf(' grid-ship') < 0) {
							classes += ' grid-ship';
							e.setAttribute('class', classes);
						}
					}
				}
			}
		}
    };
    
    /* Prototype de la fonction Game qui gère le canvas de la souris,
    La souris ne peut interagir uniquement dans la grille. */
	Game.prototype.mouse_out = function(e) {
		let cible = e.target.self;
		if(cible.place_grille) {
			for(let j = 0; j < Game.navire_coords.length; j++) {
				let e = document.querySelector('.grid-cell-' + Game.navire_coords[j].x 
					+ '-' + Game.navire_coords[j].y);
				classes = e.getAttribute('class');
				if(classes.indexOf(' grid-ship') > -1) {
					classes = classes.replace(' grid-ship', '');
					e.setAttribute('class', classes);
				}
			}
		}
    };
    
	/* Prototype de la fonction Game qui gère la rotation d'un navire */
	Game.prototype.toggleRotation = function(e) {
		let direction = parseInt(e.target.getAttribute('data-direction'), 10);
		/* Direcion horizontale initialisé à 1 */
		if(direction === Ship.DIRECTION_VERTICAL){
			e.target.setAttribute('data-direction', '1');
			Game.place_direction = Ship.DIRECTION_HORIZONTAL;
		/* Direcion verticale initialisé à 0 */
		}else if(direction === Ship.DIRECTION_HORIZONTAL){
			e.target.setAttribute('data-direction', '0');
			Game.place_direction = Ship.DIRECTION_VERTICAL;
		}
	};

	Game.prototype.commence_jeu = function(e) {
		var self = e.target.self;
		var e = document.getElementById('roster-sidebar');
		var fn = function() {e.setAttribute('class', 'hidden');};
		e.addEventListener(animation(), fn, false);
		e.setAttribute('class', 'invisible');
		self.operationnel = true;
		e.removeEventListener(animation(), fn, false);
	};

	Game.prototype.recommence_jeu = function(e) {
		e.target.removeEventListener(e.type, arguments.callee);
		var self = e.target.self;
		document.getElementById('restart-sidebar').setAttribute('class', 'hidden');
		self.resetFogOfWar();
		self.init();
	};

	Game.prototype.placeRandomly = function(e){
		e.target.removeEventListener(e.type, arguments.callee);
		e.target.self.flotte_joueur.pos_naviresRandomly();
		e.target.self.operationnel = true;
		document.getElementById('roster-sidebar').setAttribute('class', 'hidden');
		this.setAttribute('class', 'hidden');
	};

	Game.prototype.place_final = function(type_navire) {
		document.getElementById(type_navire).setAttribute('class', 'placed');
		Game.flotte_valide[CONST.FLOTTE.indexOf(type_navire)] = CONST.VALIDE;
		Game.place_direction = null;
		Game.place_navire = '';
		Game.navire_coords = [];
	};

	Game.prototype.grille_remplie = function() {
		var playerRoster = document.querySelectorAll('.fleet-roster li');
		for(var i = 0; i < playerRoster.length; i++) {
			if(playerRoster[i].getAttribute('class') === 'placed')
				continue;
			else { return false; }
		}
		Game.place_direction = 0;
		Game.place_navire = '';
		Game.navire_coords = [];
		return true;
	};

	Game.prototype.resetFogOfWar = function() {
		for(var i = 0; i < Game.dimension; i++) {
			for(var j = 0; j < Game.dimension; j++) {
				this.grille_joueur.curseur(i, j, 'empty', CONST.JOUEUR);
				this.grille_ia.curseur(i, j, 'empty', CONST.IA);
			}
		}
		Game.flotte_valide = Game.flotte_valide.map(function(){ return CONST.INVALIDE; });
	};

	Game.prototype.resetRosterSidebar = function() {
		var els = document.querySelector('.fleet-roster').querySelectorAll('li');
		for(var i = 0; i < els.length; i++) 
			els[i].removeAttribute('class');
		if(menu_jeu.defile) { menu_jeu.nextStep(); } 
		else
			document.getElementById('roster-sidebar').removeAttribute('class');
		document.getElementById('rotate-button').removeAttribute('class');
		document.getElementById('start-game').setAttribute('class', 'hidden');
	};

	/* Prototype de la fonction Game qui permet de gérer le menu pour rejouer, 
	lorsque tous les navires ennemis ou de alliés sont détruits. */
	Game.prototype.menu_rejouer = function() {
		var menu = document.getElementById('restart-sidebar');
		menu.setAttribute('class', '');
		var cases = document.querySelector('.computer-player').childNodes;
		for(var j = 0; j < cases.length; j++)
			cases[j].removeEventListener('click', this.tir_param, false);
		/* Créé une liste correspondant aux 5 types de bateaux pouvant être placés. */
		var flotte_joueur = document.querySelector('.fleet-roster').querySelectorAll('li');
		for(var i = 0; i < flotte_joueur.length; i++)
			flotte_joueur[i].removeEventListener('click', this.flotte_param, false);
		/* Bouton recommencer */
		var recommencer = document.getElementById('restart-game');
		recommencer.addEventListener('click', this.recommence_jeu, false);
		recommencer.self = this;
	};

	/* Prototype de la fonction Game qui permet de gérer la grille de jeu */
	Game.prototype.grille_jeu = function() {
		var cases = document.querySelectorAll('.grid');
		for(var grille = 0; grille < cases.length; grille++) {
			cases[grille].removeChild(cases[grille].querySelector('.error')); 
			for(var i = 0; i < Game.dimension; i++) { /* Lignes */
				for(var j = 0; j < Game.dimension; j++) { /* Colonnes */
					var e = document.createElement('div');
					/* Attribuer les valeurs de rotations initiales en abscisse et ordonnée */
					e.setAttribute('data-x', i); e.setAttribute('data-y', j);
					e.setAttribute('class', 'grid-cell grid-cell-' + i + '-' + j);
					cases[grille].appendChild(e);
				}
			}
		}
	};

	Game.prototype.init = function() {
		this.grille_joueur = new Grid(Game.dimension);
		this.grille_ia = new Grid(Game.dimension);
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
		this.resetRosterSidebar();
		var computerCells = document.querySelector('.computer-player').childNodes;
		for (var j = 0; j < computerCells.length; j++) {
			computerCells[j].self = this;
			computerCells[j].addEventListener('click', this.tir_param, false);
		}
		var playerRoster = document.querySelector('.fleet-roster').querySelectorAll('li');
		for (var i = 0; i < playerRoster.length; i++) {
			playerRoster[i].self = this;
			playerRoster[i].addEventListener('click', this.flotte_param, false);
		}
		var humanCells = document.querySelector('.human-player').childNodes;
		for (var k = 0; k < humanCells.length; k++) {
			humanCells[k].self = this;
			humanCells[k].addEventListener('click', this.place_param, false);
			humanCells[k].addEventListener('mouseover', this.mouse_ouver, false);
			humanCells[k].addEventListener('mouseout', this.mouse_out, false);
		}
		var rotateButton = document.getElementById('rotate-button');
		rotateButton.addEventListener('click', this.toggleRotation, false);
		var startButton = document.getElementById('start-game');
		startButton.self = this;
		startButton.addEventListener('click', this.commence_jeu, false);
		this.flotte_ia.pos_naviresRandomly();
	};

	var menu_jeu = this.currentStep = 0;
	var jeu = new Game(10);