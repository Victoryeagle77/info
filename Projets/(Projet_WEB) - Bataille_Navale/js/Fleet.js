class Fleet {
	constructor(grille_joueur, player) {
		this.grille_joueur = grille_joueur;
		this.player = player;
		this.fleetRoster = [];
		this.densite();
	}

	densite() {
		for (let i = 0; i < CONST.FLOTTE.length; i++) {
			this.fleetRoster.push(new Ship(CONST.FLOTTE[i % CONST.FLOTTE.length],
				this.grille_joueur, this.player));
		}
	}

	pos_navire(x, y, direction, type_navire) {
		let position;
		for (let i = 0; i < this.fleetRoster.length; i++) {
			let type_navires = this.fleetRoster[i].type;
			/* Si un bateau est touché dans la grille */
			if ((type_navire === type_navires) && (this.fleetRoster[i].isLegal(x, y, direction))) {
				this.fleetRoster[i].create(x, y, direction, false);
				position = this.fleetRoster[i].getAllShipCells();

				for (let j = 0; j < position.length; j++)
					this.grille_joueur.curseur(position[j].x, position[j].y, 'ship', this.player);
				return true;
			}
		}
		return false;
	}

	pos_naviresRandomly() {
		let coordonnees;
		for (let i = 0; i < this.fleetRoster.length; i++) {
			let position = true;
			if ((this.player === CONST.JOUEUR) && (Game.flotte_valide[i] === CONST.VALIDE))
				continue;

			while (position) {
				let x = Math.floor(10 * Math.random());
				let y = Math.floor(10 * Math.random());
				let direction = Math.floor(2 * Math.random());
				if (this.fleetRoster[i].isLegal(x, y, direction)) {
					this.fleetRoster[i].create(x, y, direction, false);
					coordonnees = this.fleetRoster[i].getAllShipCells();
					position = false;
				}
				else { continue; }
			}
			if (this.player === CONST.JOUEUR && Game.flotte_valide[i] !== CONST.VALIDE) {
				for (let j = 0; j < coordonnees.length; j++) {
					this.grille_joueur.curseur(coordonnees[j].x, coordonnees[j].y, 'ship', this.player);
					Game.flotte_valide[i] = CONST.VALIDE;
				}
			}
		}
	}

	localisation(x, y) {
		for (let i = 0; i < this.fleetRoster.length; i++) {
			let navire = this.fleetRoster[i];
			if (navire.direction === Ship.DIRECTION_VERTICAL) {
				if ((y === navire.yPosition) && (x >= navire.xPosition) &&
					(x < navire.xPosition + navire.shipLength))
					return navire;
				else { continue; }
			}
			else {
				if ((x === navire.xPosition) && (y >= navire.yPosition) &&
					(y < navire.yPosition + navire.shipLength))
					return navire;
				else { continue; }
			}
		}
		return null;
	}

	findShipByType(type_navire) {
		for (let i = 0; i < this.fleetRoster.length; i++) {
			if (this.fleetRoster[i].type === type_navire) { return this.fleetRoster[i]; }
		}
		return null;
	}

	flotte_detruite() {
		for (let i = 0; i < this.fleetRoster.length; i++) {
			if (this.fleetRoster[i].sunk === false) { return false; }
		}
		return true;
	}
}






