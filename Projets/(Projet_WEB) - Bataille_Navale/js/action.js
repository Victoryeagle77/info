(function() {
	/* Définition de constantes à l'individualisation des cases de jeu */	
	var CONST = {};
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
	CONST.RATE = 2; CONST.TOUCHE = 3; CONST.COULE = 4; 
	/* Initialisation de la flotte des navires utilisés au départ (c'est à dire aucun) */
	Game.flotte_valide = [CONST.INVALIDE, CONST.INVALIDE, CONST.INVALIDE, CONST.INVALIDE, CONST.INVALIDE];
	CONST.VALIDE = 1; CONST.INVALIDE = 0;

	/*** Fonction qui évalue les statistiques des tirs joueurs effecutés ***/
	function Stats(){
		this.tir_subis = 0; this.tir_touche = 0;
		/* Conversion en entier des item stocké dans les coockies de la page,
		que l'on récupére. */
		this.total_tirs = parseInt(localStorage.getItem('total_tirs'), 10) || 0;
		this.total_dommages = parseInt(localStorage.getItem('total_dommages'), 10) || 0;
		this.lance_jeu = parseInt(localStorage.getItem('lance_jeu'), 10) || 0;
		this.victoire = parseInt(localStorage.getItem('victoire'), 10) || 0;
		if (DEBUG_MODE) { this.tmp = true; }
	}
	/* Prototype de la fonction Stats qui gère la synchronisation des statistiques */
	Stats.prototype.sync = function() {
		if(!this.tmp) {
			var total_tirs = parseInt(localStorage.getItem('total_tirs'), 10) || 0;
			total_tirs += this.tir_subis;
			var total_dommages = parseInt(localStorage.getItem('total_dommages'), 10) || 0;
			total_dommages += this.tir_touche;
			/* Charger les valeurs suivante dans les items stockés dans les coockies de la page */
			localStorage.setItem('total_tirs', total_tirs);
			localStorage.setItem('total_dommages', total_dommages);
			localStorage.setItem('victoire', this.victoire);
		} else { this.tmp = false; }
		var grille_valeur = '';
		/* Mise en place des cases */
		for (var x = 0; x < Game.dimension; x++) {
			for (var y = 0; y < Game.dimension; y++)
				grille_valeur += '(' + x + ',' + y + '):' + jeu.grille_joueur.cells[x][y] + ';\n';
		}
		if (!DEBUG_MODE)
			ga('send', 'event', 'grille_joueur', grille_valeur);
	};
	/* Prototype de la fonction Stats qui gère les points de vie de la flotte. */
	Stats.prototype.pv = function() {
		this.tir_subis++;
	};
	/* Prototype de la fonction Stats qui gère les points de vie de la flotte ennemie. */
	Stats.prototype.scoring = function() {
		this.tir_touche++;
	};
	/* Prototype de la fonction Stats qui gère la victoire du jeu */
	Stats.prototype.gagne = function() {
		this.lance_jeu++; this.victoire++;
		/* Vérification du debug mode avec Google Analytics */
		if (!DEBUG_MODE)
			ga('send', 'event', 'jeu_perdu', 'win');
	};
	/* Prototype de la fonction Stats qui gère la défaite du jeu */
	Stats.prototype.perd = function() {
		this.lance_jeu++;
		/* Vérification du debug mode avec Google Analytics */
		if (!DEBUG_MODE)
			ga('send', 'event', 'jeu_perdu', 'lose');
	};

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
		if (this.flotte_ia.flotte_detruite()) {
			/* Message d'alerte javascript */
			alert('Bravo, flotte ennemie détruite');
			Game.jeu_perdu = true;
			/* Synchronisation du statut de victoire */
			Game.stats.gagne(); Game.stats.sync();
			this.menu_rejouer();
		} else if (this.flotte_joueur.flotte_detruite()) {
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
		var grille_cible, flotte_cible;
		if (joueur_cible === CONST.JOUEUR) {
			grille_cible = this.grille_joueur;
			flotte_cible = this.flotte_joueur;
		} else if (joueur_cible === CONST.IA) {
			grille_cible = this.grille_ia;
			flotte_cible = this.flotte_ia;
		}
		/* Etat des bateaux selon leur coordonnées */
		if (grille_cible.navire_endommage(x, y)) { return null; }
		else if (grille_cible.navire_evite(x, y)) { return null; }
		else if (grille_cible.navire_sauf(x, y)) {
			grille_cible.change_case(x, y, 'hit', joueur_cible);
			/* Détecter et localiser la présence d'un bateau par ses coordonnées */
			flotte_cible.localisation(x, y).dommages_scoring(); 
			this.etat();
			return CONST.TOUCHE;
		} else {
			grille_cible.change_case(x, y, 'miss', joueur_cible);
			this.etat();
			return CONST.RATE;
		}
	};
	/* Prototype de la fonction Game, 
	qui permet de lié le statut des tirs au score et point de vie */ 
	Game.prototype.tir_param = function(e) {
		var self = e.target.self;
		/* Axe de rotation d'un élément attribué en abscisse et ordonnée,
		converti en coordonnées entiére, (rotation d'un navire) */
		var x = parseInt(e.target.getAttribute('data-x'), 10);
		var y = parseInt(e.target.getAttribute('data-y'), 10);
		var res = null;
		if (self.operationnel)
			res = self.tir(x, y, CONST.IA);
		if (res !== null && !Game.jeu_perdu) {
			/* Inventaire des points de vie des navires */
			Game.stats.pv();
			if (res === CONST.TOUCHE) { Game.stats.scoring(); }
			self.auto.tir();
		} else { Game.jeu_perdu = false; }
	};
	/* Prototype de la fonction Game, 
	qui assure la lisaison entre les éléments graphiques de CSS et de JS.
	Le design des sprits de bateaux sont liés par leur classes CSS aux JS. */
	Game.prototype.flotte_param = function(e) {
		var self = e.target.self;
		/* Selectionner la classe CSS correspondante */
		var flotte = document.querySelectorAll('.fleet-roster li');
		for (var i = 0; i < flotte.length; i++) {
			/* Obtenir les classes CSS */
			var classes = flotte[i].getAttribute('class') || '';
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
	Game.prototype.place_param = function(e) {
		var self = e.target.self;
		if (self.place_grille) {
			var x = parseInt(e.target.getAttribute('data-x'), 10);
			var y = parseInt(e.target.getAttribute('data-y'), 10);
			var atteinte = self.flotte_joueur.pos_navire(x, y, 
				Game.place_direction, Game.place_navire);
			if (atteinte) {
				self.place_final(Game.place_navire);
				self.place_grille = false;
				/* Pour tous les bateaux placés sur la grille */
				if (self.grille_remplie()) {
					var e = document.getElementById('rotate-button');
					e.addEventListener(transitionEndEventName(),
						(function(){
							e.setAttribute('class', 'hidden');
							/* Caché l'élément de bouton commencer,
							tant que tous les navvires ne sont pas placés. */
							if (menu_jeu.defile)
								document.getElementById('start-game').setAttribute('class');
							else
								document.getElementById('start-game').removeAttribute('class');	
						}),false);
					e.setAttribute('class', 'invisible');
				}
			}
		}
	};
    /* Prototype de la fonction Game qui gère */
	Game.prototype.mouse_ouver = function(e) {
		var self = e.target.self;
		if (self.place_grille) {
			var x = parseInt(e.target.getAttribute('data-x'), 10);
			var y = parseInt(e.target.getAttribute('data-y'), 10);
			var classes;
			var fleetRoster = self.flotte_joueur.fleetRoster;

			for (var i = 0; i < fleetRoster.length; i++) {
				var type_navire = fleetRoster[i].type;

				if (Game.place_navire === type_navire &&
					fleetRoster[i].isLegal(x, y, Game.place_direction)) {
					fleetRoster[i].create(x, y, Game.place_direction, true);
					Game.navire_coords = fleetRoster[i].getAllShipCells();
                    
					for (var j = 0; j < Game.navire_coords.length; j++) {
						var e = document.querySelector('.grid-cell-' + Game.navire_coords[j].x 
							+ '-' + Game.navire_coords[j].y);
						classes = e.getAttribute('class');
						if (classes.indexOf(' grid-ship') < 0) {
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
		var self = e.target.self;
		if (self.place_grille) {
			for (var j = 0; j < Game.navire_coords.length; j++) {
				var e = document.querySelector('.grid-cell-' + Game.navire_coords[j].x 
					+ '-' + Game.navire_coords[j].y);
				classes = e.getAttribute('class');
				if (classes.indexOf(' grid-ship') > -1) {
					classes = classes.replace(' grid-ship', '');
					e.setAttribute('class', classes);
				}
			}
		}
	};
	/* Prototype de la fonction Game qui gère la rotation d'un navire */
	Game.prototype.toggleRotation = function(e) {
		var direction = parseInt(e.target.getAttribute('data-direction'), 10);
		/* Direcion horizontale initialisé à 1 */
		if (direction === Ship.DIRECTION_VERTICAL) {
			e.target.setAttribute('data-direction', '1');
			Game.place_direction = Ship.DIRECTION_HORIZONTAL;
		/* Direcion verticale initialisé à 0 */
		} else if (direction === Ship.DIRECTION_HORIZONTAL) {
			e.target.setAttribute('data-direction', '0');
			Game.place_direction = Ship.DIRECTION_VERTICAL;
		}
	};

	Game.prototype.commence_jeu = function(e) {
		var self = e.target.self;
		var e = document.getElementById('roster-sidebar');
		var fn = function() {e.setAttribute('class', 'hidden');};
		e.addEventListener(transitionEndEventName(),fn,false);
		e.setAttribute('class', 'invisible');
		self.operationnel = true;
		e.removeEventListener(transitionEndEventName(),fn,false);
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
		for (var i = 0; i < playerRoster.length; i++) {
			if (playerRoster[i].getAttribute('class') === 'placed')
				continue;
			else { return false; }
		}
		Game.place_direction = 0;
		Game.place_navire = '';
		Game.navire_coords = [];
		return true;
	};

	Game.prototype.resetFogOfWar = function() {
		for (var i = 0; i < Game.dimension; i++) {
			for (var j = 0; j < Game.dimension; j++) {
				this.grille_joueur.change_case(i, j, 'empty', CONST.JOUEUR);
				this.grille_ia.change_case(i, j, 'empty', CONST.IA);
			}
		}
		Game.flotte_valide = Game.flotte_valide.map(function(){return CONST.INVALIDE;});
	};

	Game.prototype.resetRosterSidebar = function() {
		var els = document.querySelector('.fleet-roster').querySelectorAll('li');
		for (var i = 0; i < els.length; i++) 
			els[i].removeAttribute('class');
		if (menu_jeu.defile) { menu_jeu.nextStep(); } 
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
		for (var j = 0; j < cases.length; j++)
			cases[j].removeEventListener('click', this.tir_param, false);
		/* Créé une liste correspondant aux 5 types de bateaux pouvant être placés. */
		var flotte_joueur = document.querySelector('.fleet-roster').querySelectorAll('li');
		for (var i = 0; i < flotte_joueur.length; i++)
			flotte_joueur[i].removeEventListener('click', this.flotte_param, false);
		/* Bouton recommencer */
		var recommencer = document.getElementById('restart-game');
		recommencer.addEventListener('click', this.recommence_jeu, false);
		recommencer.self = this;
	};

	/* Prototype de la fonction Game qui permet de gérer la grille de jeu */
	Game.prototype.grille_jeu = function() {
		var cases = document.querySelectorAll('.grid');
		for (var grille = 0; grille < cases.length; grille++) {
			cases[grille].removeChild(cases[grille].querySelector('.error')); 
			for (var i = 0; i < Game.dimension; i++) { /* Lignes */
				for (var j = 0; j < Game.dimension; j++) { /* Colonnes */
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

	function Grid(dimension) {
		this.dimension = dimension;
		this.cells = [];
		this.init();
	}

	Grid.prototype.init = function() {
		for (var x = 0; x < this.dimension; x++) {
			var colonne = [];
			this.cells[x] = colonne;
			for (var y = 0; y < this.dimension; y++) {
				colonne.push(CONST.VIDE);
			}
		}
	};

	Grid.prototype.change_case = function(x, y, type, joueur_cible) {
		var player;
		if (joueur_cible === CONST.JOUEUR) {
			player = 'human-player';
		} else if (joueur_cible === CONST.IA) {
			player = 'computer-player';
		}
		switch (type) {
			case CONST.STYLE_VIDE: this.cells[x][y] = CONST.VIDE; break;
			case CONST.STYLE_NAVIRE: this.cells[x][y] = CONST.NAVIRE; break;
			case CONST.STYLE_RATE: this.cells[x][y] = CONST.RATE; break;
			case CONST.STYLE_TOUCHE: this.cells[x][y] = CONST.TOUCHE; break;
			case CONST.STYLE_COULE: this.cells[x][y] = CONST.COULE; break;
			default: this.cells[x][y] = CONST.VIDE; break;
		}
		var classes = ['grid-cell', 'grid-cell-' + x + '-' + y, 'grid-' + type];
		document.querySelector('.' + player + ' .grid-cell-' + x + '-' + y).setAttribute('class', classes.join(' '));
	};

	Grid.prototype.navire_sauf = function(x, y) {
		return this.cells[x][y] === CONST.NAVIRE;
	};

	Grid.prototype.navire_evite = function(x, y) {
		return this.cells[x][y] === CONST.RATE;
	};

	Grid.prototype.navire_endommage = function(x, y) {
		return this.cells[x][y] === CONST.TOUCHE || this.cells[x][y] === CONST.COULE;
	};

	function Fleet(playerGrid, player) {
		this.numShips = CONST.FLOTTE.length;
		this.playerGrid = playerGrid;
		this.player = player;
		this.fleetRoster = [];
		this.populate();
	}

	Fleet.prototype.populate = function() {
		for (var i = 0; i < this.numShips; i++) {
			var j = i % CONST.FLOTTE.length;
			this.fleetRoster.push(new Ship(CONST.FLOTTE[j], this.playerGrid, this.player));
		}
	};

	Fleet.prototype.pos_navire = function(x, y, direction, type_navire) {
		var shipCoords;
		for (var i = 0; i < this.fleetRoster.length; i++) {
			var type_navires = this.fleetRoster[i].type;

			if (type_navire === type_navires &&
				this.fleetRoster[i].isLegal(x, y, direction)) {
				this.fleetRoster[i].create(x, y, direction, false);
				shipCoords = this.fleetRoster[i].getAllShipCells();

				for (var j = 0; j < shipCoords.length; j++)
					this.playerGrid.change_case(shipCoords[j].x, shipCoords[j].y, 'ship', this.player);
				return true;
			}
		}
		return false;
	};

	Fleet.prototype.pos_naviresRandomly = function() {
		var shipCoords;
		for (var i = 0; i < this.fleetRoster.length; i++) {
			var illegalPlacement = true;
			if(this.player === CONST.JOUEUR && Game.flotte_valide[i] === CONST.VALIDE)
				continue;
			while (illegalPlacement) {
				var randomX = Math.floor(10*Math.random());
				var randomY = Math.floor(10*Math.random());
				var randomDirection = Math.floor(2*Math.random());			
				if (this.fleetRoster[i].isLegal(randomX, randomY, randomDirection)) {
					this.fleetRoster[i].create(randomX, randomY, randomDirection, false);
					shipCoords = this.fleetRoster[i].getAllShipCells();
					illegalPlacement = false;
				} else { continue; }
			}
			if (this.player === CONST.JOUEUR && Game.flotte_valide[i] !== CONST.VALIDE) {
				for (var j = 0; j < shipCoords.length; j++) {
					this.playerGrid.change_case(shipCoords[j].x, shipCoords[j].y, 'ship', this.player);
					Game.flotte_valide[i] = CONST.VALIDE;
				}
			}
		}
	};

	Fleet.prototype.localisation = function(x, y) {
		for (var i = 0; i < this.fleetRoster.length; i++) {
			var currentShip = this.fleetRoster[i];
			if (currentShip.direction === Ship.DIRECTION_VERTICAL) {
				if (y === currentShip.yPosition &&
					x >= currentShip.xPosition &&
					x < currentShip.xPosition + currentShip.shipLength) {
					return currentShip;
				} else { continue; }
			} else {
				if (x === currentShip.xPosition &&
					y >= currentShip.yPosition &&
					y < currentShip.yPosition + currentShip.shipLength) {
					return currentShip;
				} else { continue; }
			}
		}
		return null;
	};

	Fleet.prototype.findShipByType = function(type_navire) {
		for (var i = 0; i < this.fleetRoster.length; i++) {
			if (this.fleetRoster[i].type === type_navire) {
				return this.fleetRoster[i];
			}
		}
		return null;
	};

	Fleet.prototype.flotte_detruite = function() {
		for (var i = 0; i < this.fleetRoster.length; i++) {
			if (this.fleetRoster[i].sunk === false) {
				return false;
			}
		}
		return true;
	};

	function Ship(type, playerGrid, player) {
		this.damage = 0;
		this.type = type;
		this.playerGrid = playerGrid;
		this.player = player;

		switch (this.type) {
			case CONST.FLOTTE[0]: this.shipLength = 5; break;
			case CONST.FLOTTE[1]: this.shipLength = 4; break;
			case CONST.FLOTTE[2]: this.shipLength = 3; break;
			case CONST.FLOTTE[3]: this.shipLength = 3; break;
			case CONST.FLOTTE[4]: this.shipLength = 2; break;
			default: this.shipLength = 3; break;
		}
		this.maxDamage = this.shipLength;
		this.sunk = false;
	}

	Ship.prototype.isLegal = function(x, y, direction) {
		if (this.withinBounds(x, y, direction)) {
			for (var i = 0; i < this.shipLength; i++) {
				if (direction === Ship.DIRECTION_VERTICAL) {
					if (this.playerGrid.cells[x + i][y] === CONST.NAVIRE ||
						this.playerGrid.cells[x + i][y] === CONST.RATE ||
						this.playerGrid.cells[x + i][y] === CONST.COULE) {
						return false;
					}
				} else {
					if (this.playerGrid.cells[x][y + i] === CONST.NAVIRE ||
						this.playerGrid.cells[x][y + i] === CONST.RATE ||
						this.playerGrid.cells[x][y + i] === CONST.COULE) {
						return false;
					}
				}
			}
			return true;
		} else { return false; }
	};

	Ship.prototype.withinBounds = function(x, y, direction) {
		if (direction === Ship.DIRECTION_VERTICAL) 
			return x + this.shipLength <= Game.dimension;
		else 
			return y + this.shipLength <= Game.dimension;
	};

	Ship.prototype.dommages_scoring = function() {
		this.damage++;
		if (this.isSunk()) { this.sinkShip(false); }
	};

	Ship.prototype.isSunk = function() {
		return this.damage >= this.maxDamage;
	};

	Ship.prototype.sinkShip = function(virtual) {
		this.damage = this.maxDamage; 
		this.sunk = true;
		if (!virtual) {
			var allCells = this.getAllShipCells();
			for (var i = 0; i < this.shipLength; i++) {
				this.playerGrid.change_case(allCells[i].x, allCells[i].y, 'sunk', this.player);
			}
		}
	};

	Ship.prototype.getAllShipCells = function() {
		var resObject = [];
		for (var i = 0; i < this.shipLength; i++) {
			if (this.direction === Ship.DIRECTION_VERTICAL) {
				resObject[i] = {'x': this.xPosition + i, 'y': this.yPosition};
			} else {
				resObject[i] = {'x': this.xPosition, 'y': this.yPosition + i};
			}
		}
		return resObject;
	};

	Ship.prototype.create = function(x, y, direction, virtual) {
		this.xPosition = x;
		this.yPosition = y;
		this.direction = direction;
		if (!virtual) {
			for (var i = 0; i < this.shipLength; i++) {
				if (this.direction === Ship.DIRECTION_VERTICAL) {
					this.playerGrid.cells[x + i][y] = CONST.NAVIRE;
				} else {
					this.playerGrid.cells[x][y + i] = CONST.NAVIRE;
				}
			}
		}
		
	};
	Ship.DIRECTION_VERTICAL = 0;
	Ship.DIRECTION_HORIZONTAL = 1;

	function Tutorial() {
		this.currentStep = 0;
	}

	function AI(gameObject) {
		this.gameObject = gameObject;
		this.virtualGrid = new Grid(Game.dimension);
		this.virtualFleet = new Fleet(this.virtualGrid, CONST.ADVERSAIRE);
		this.probGrid = []; 
		this.initProbs();
		this.updateProbs();
	}
	AI.PROB_WEIGHT = 5000; 
	AI.OPEN_HIGH_MIN = 20;
	AI.OPEN_HIGH_MAX = 30;
	AI.OPEN_MED_MIN = 15;
	AI.OPEN_MED_MAX = 25;
	AI.OPEN_LOW_MIN = 10;
	AI.OPEN_LOW_MAX = 20;
	AI.RANDOMNESS = 0.1;
	AI.OPENINGS = [
		{'x': 7, 'y': 3, 'weight': getRandom(AI.OPEN_LOW_MIN, AI.OPEN_LOW_MAX)},
		{'x': 6, 'y': 2, 'weight': getRandom(AI.OPEN_LOW_MIN, AI.OPEN_LOW_MAX)},
		{'x': 3, 'y': 7, 'weight': getRandom(AI.OPEN_LOW_MIN, AI.OPEN_LOW_MAX)},
		{'x': 2, 'y': 6, 'weight': getRandom(AI.OPEN_LOW_MIN, AI.OPEN_LOW_MAX)},
		{'x': 6, 'y': 6, 'weight': getRandom(AI.OPEN_LOW_MIN, AI.OPEN_LOW_MAX)},
		{'x': 3, 'y': 3, 'weight': getRandom(AI.OPEN_LOW_MIN, AI.OPEN_LOW_MAX)},
		{'x': 5, 'y': 5, 'weight': getRandom(AI.OPEN_LOW_MIN, AI.OPEN_LOW_MAX)},
		{'x': 4, 'y': 4, 'weight': getRandom(AI.OPEN_LOW_MIN, AI.OPEN_LOW_MAX)},
		{'x': 0, 'y': 8, 'weight': getRandom(AI.OPEN_MED_MIN, AI.OPEN_MED_MAX)},
		{'x': 1, 'y': 9, 'weight': getRandom(AI.OPEN_HIGH_MIN, AI.OPEN_HIGH_MAX)},
		{'x': 8, 'y': 0, 'weight': getRandom(AI.OPEN_MED_MIN, AI.OPEN_MED_MAX)},
		{'x': 9, 'y': 1, 'weight': getRandom(AI.OPEN_HIGH_MIN, AI.OPEN_HIGH_MAX)},
		{'x': 9, 'y': 9, 'weight': getRandom(AI.OPEN_HIGH_MIN, AI.OPEN_HIGH_MAX)},
		{'x': 0, 'y': 0, 'weight': getRandom(AI.OPEN_HIGH_MIN, AI.OPEN_HIGH_MAX)}
	];

	AI.prototype.tir = function() {
		var maxProbability = 0;
		var maxProbCoords;
		var maxProbs = [];
		for (var i = 0; i < AI.OPENINGS.length; i++) {
			var cell = AI.OPENINGS[i];
			if (this.probGrid[cell.x][cell.y] !== 0) {
				this.probGrid[cell.x][cell.y] += cell.weight;
			}
		}
		for (var x = 0; x < Game.dimension; x++) {
			for (var y = 0; y < Game.dimension; y++) {
				if (this.probGrid[x][y] > maxProbability) {
					maxProbability = this.probGrid[x][y];
					maxProbs = [{'x': x, 'y': y}]; 
				} else if (this.probGrid[x][y] === maxProbability) {
					maxProbs.push({'x': x, 'y': y});
				}
			}
		}
		maxProbCoords = Math.random() < AI.RANDOMNESS ?
		maxProbs[Math.floor(Math.random() * maxProbs.length)] :
		maxProbs[0];
		var res = this.gameObject.tir(maxProbCoords.x, maxProbCoords.y, CONST.JOUEUR);	
		if (Game.jeu_perdu) {
			Game.jeu_perdu = false;
			return;
		}
		this.virtualGrid.cells[maxProbCoords.x][maxProbCoords.y] = res;
		if (res === CONST.TOUCHE) {
			var humanShip = this.findHumanShip(maxProbCoords.x, maxProbCoords.y);
			if (humanShip.isSunk()) {
				var type_navires = [];
				for (var k = 0; k < this.virtualFleet.fleetRoster.length; k++) {
					type_navires.push(this.virtualFleet.fleetRoster[k].type);
				}
				var index = type_navires.indexOf(humanShip.type);
				this.virtualFleet.fleetRoster.splice(index, 1);
				var shipCells = humanShip.getAllShipCells();
				for (var _i = 0; _i < shipCells.length; _i++) {
					this.virtualGrid.cells[shipCells[_i].x][shipCells[_i].y] = CONST.COULE;
				}
			}
		}
		this.updateProbs();
	};

	AI.prototype.updateProbs = function() {
		var roster = this.virtualFleet.fleetRoster;
		var coords;
		this.resetProbs();
		for (var k = 0; k < roster.length; k++) {
			for (var x = 0; x < Game.dimension; x++) {
				for (var y = 0; y < Game.dimension; y++) {
					if (roster[k].isLegal(x, y, Ship.DIRECTION_VERTICAL)) {
						roster[k].create(x, y, Ship.DIRECTION_VERTICAL, true);
						coords = roster[k].getAllShipCells();
						if (this.passesThroughHitCell(coords)) {
							for (var i = 0; i < coords.length; i++) {
								this.probGrid[coords[i].x][coords[i].y] += AI.PROB_WEIGHT * this.numHitCellsCovered(coords);
							}
						} else {
							for (var _i = 0; _i < coords.length; _i++) {
								this.probGrid[coords[_i].x][coords[_i].y]++;
							}
						}
					}
					if (roster[k].isLegal(x, y, Ship.DIRECTION_HORIZONTAL)) {
						roster[k].create(x, y, Ship.DIRECTION_HORIZONTAL, true);
						coords = roster[k].getAllShipCells();
						if (this.passesThroughHitCell(coords)) {
							for (var j = 0; j < coords.length; j++) {
								this.probGrid[coords[j].x][coords[j].y] += AI.PROB_WEIGHT * this.numHitCellsCovered(coords);
							}
						} else {
							for (var _j = 0; _j < coords.length; _j++) {
								this.probGrid[coords[_j].x][coords[_j].y]++;
							}
						}
					}
					if (this.virtualGrid.cells[x][y] === CONST.TOUCHE) {
						this.probGrid[x][y] = 0;
					}
				}
			}
		}
	};

	AI.prototype.initProbs = function() {
		for (var x = 0; x < Game.dimension; x++) {
			var colonne = [];
			this.probGrid[x] = colonne;
			for (var y = 0; y < Game.dimension; y++)
				colonne.push(0);
		}
	};

	AI.prototype.resetProbs = function() {
		for (var x = 0; x < Game.dimension; x++) {
			for (var y = 0; y < Game.dimension; y++) {
				this.probGrid[x][y] = 0;
			}
		}
	};

	AI.prototype.findHumanShip = function(x, y) {
		return this.gameObject.flotte_joueur.localisation(x, y);
	};

	AI.prototype.passesThroughHitCell = function(shipCells) {
		for (var i = 0; i < shipCells.length; i++) {
			if (this.virtualGrid.cells[shipCells[i].x][shipCells[i].y] === CONST.TOUCHE)
				return true;
		}
		return false;
	};

	AI.prototype.numHitCellsCovered = function(shipCells) {
		var cells = 0;
		for (var i = 0; i < shipCells.length; i++) {
			if (this.virtualGrid.cells[shipCells[i].x][shipCells[i].y] === CONST.TOUCHE)
				cells++;
		}
		return cells;
	};

	var menu_jeu = new Tutorial();
	var jeu = new Game(10);
})();

function transitionEndEventName() {
	var i,
		undefined,
		el = document.createElement('div'),
		transitions = {
			'transition':'transitionend',
			'OTransition':'otransitionend', 
			'MozTransition':'transitionend',
			'WebkitTransition':'webkitTransitionEnd'
		};

	for (i in transitions) {
		if (transitions.hasOwnProperty(i) && el.style[i] !== undefined)
			return transitions[i];
	}
}

function getRandom(min, max) {
	return Math.random() * (max - min) + min;
}

function setDebug(val) {
	DEBUG_MODE = val;
	localStorage.setItem('DEBUG_MODE', val);
	window.location.reload();
}