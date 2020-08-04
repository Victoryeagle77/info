class Fleet{
	constructor(grille_joueur, player){
		this.grille_joueur = grille_joueur;
		this.player = player;
		this.artillerie = [];
		this.densite();
	}
	
	/* Total des bateaux positionnés */
	densite(){
		for(let i = 0; i < CONST.FLOTTE.length; i++){
			this.artillerie.push(new Ship(CONST.FLOTTE[i % CONST.FLOTTE.length],
				this.grille_joueur, this.player));
		}
	}
	
	/* Emplacement d'un navire selon sa direction */
	pos_navire(x, y, direction, type_navire){
		let position;
		for(let i = 0; i < this.artillerie.length; i++){
			let type_navires = this.artillerie[i].type;
			/* Si un bateau est touché dans la grille */
			if((type_navire == type_navires) && (this.artillerie[i].borne(x, y, direction))){
				this.artillerie[i].positionner(x, y, direction, false);
				position = this.artillerie[i].taille_navire();

				for(let j = 0; j < position.length; j++)
					this.grille_joueur.curseur(position[j].x, position[j].y, 'ship', this.player);
				return true;
			}
		}
		return false;
	}

	/* Generation aleatoire des navires de la flotte adverse */
	gen_pos(){
		let cords;
		for(let i = 0; i < this.artillerie.length; i++) {
			let position = true;
			if((this.player == CONST.JOUEUR) && (Game.flotte_valide[i] == CONST.VALIDE))
				continue;

			while(position) {
				let x = Math.floor(10 * Math.random());
				let y = Math.floor(10 * Math.random());
				/* Générer un sens de placement aléatoire entre horizontal et vertical */
				let direction = Math.floor(2 * Math.random());
				if(this.artillerie[i].borne(x, y, direction)){
					this.artillerie[i].positionner(x, y, direction, false);
					cords = this.artillerie[i].taille_navire();
					position = false;
				}else{ continue; }
			}
			if((this.player == CONST.JOUEUR) && (Game.flotte_valide[i] != CONST.VALIDE)){
				for(let j = 0; j < cords.length; j++){
					this.grille_joueur.curseur(cords[j].x, cords[j].y, 'ship', this.player);
					Game.flotte_valide[i] = CONST.VALIDE;
				}
			}
		}
	}

	localisation(x, y){
		for(let i = 0; i < this.artillerie.length; i++){
			let navire = this.artillerie[i];
			if(navire.direction == Ship.DIRECTION_VERTICAL){
				if((y == navire.ordonnee) && (x >= navire.abscisse) &&
					(x < navire.abscisse + navire.longueur))
					return navire;
				else{ continue; }
			}else{
				if((x == navire.abscisse) && (y >= navire.ordonnee) &&
					(y < navire.ordonnee + navire.longueur))
					return navire;
				else{ continue; }
			}
		}
		return null;
	}

    /* Destruction de tous les navires adverses */
	flotte_detruite(){
		for(let i = 0; i < this.artillerie.length; i++){
			if(this.artillerie[i].sunk == false){ return false; }
		}
		return true;
	}
}