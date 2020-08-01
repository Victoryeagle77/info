class Grid {
	constructor(dimension) {
		this.dimension = dimension;
		this.cells = [];
		this.initialisation();
	}
	initialisation() {
		for (let x = 0; x < this.dimension; x++) {
			let colonne = [];
			this.cells[x] = colonne;
			for (let y = 0; y < this.dimension; y++) { colonne.push(CONST.VIDE); }
		}
	}
	curseur(x, y, type, cible) {
		let player;
		if (cible === CONST.JOUEUR) { player = 'human-player'; }
		else if (cible === CONST.IA) { player = 'computer-player'; }
		switch (type) {
			case CONST.STYLE_VIDE:
				this.cells[x][y] = CONST.VIDE;
				break;
			case CONST.STYLE_NAVIRE:
				this.cells[x][y] = CONST.NAVIRE;
				break;
			case CONST.STYLE_RATE:
				this.cells[x][y] = CONST.RATE;
				break;
			case CONST.STYLE_TOUCHE:
				this.cells[x][y] = CONST.TOUCHE;
				break;
			case CONST.STYLE_COULE:
				this.cells[x][y] = CONST.COULE;
				break;
			default:
				this.cells[x][y] = CONST.VIDE;
				break;
		}
		let classes = ['grid-cell', 'grid-cell-' + x + '-' + y, 'grid-' + type];
		document.querySelector('.' + player + ' .grid-cell-' + x + '-' + y).setAttribute('class', classes.join(' '));
	}
	navire_sauf(x, y) {
		return this.cells[x][y] == CONST.NAVIRE;
	}
	navire_evite(x, y) {
		return this.cells[x][y] == CONST.RATE;
	}
	navire_endommage(x, y) {
		return this.cells[x][y] == CONST.TOUCHE || this.cells[x][y] === CONST.COULE;
	}
}





