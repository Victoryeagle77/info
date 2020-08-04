class Ship {
    constructor(type, grille_joueur, joueur) {
        this.degats = 0;
        this.type = type;
        this.grille_joueur = grille_joueur;
        this.joueur = joueur;
        /* Taille des différents type de navire */
        switch(this.type){
            /* Porte-avions */
            case CONST.FLOTTE[0]: this.longueur = 5; break;
            /* Croiseur */
            case CONST.FLOTTE[1]: this.longueur = 4; break;
            /* Destroyer */
            case CONST.FLOTTE[2]: this.longueur = 3; break;
            /* Sous marin */
            case CONST.FLOTTE[3]: this.longueur = 3; break;
            /* Patrouilleur */
            case CONST.FLOTTE[4]: this.longueur = 2; break;
        }
        this.max = this.longueur;
        this.sunk = false;
    }

    /* Limite les actions possibles dans la grille de jeu */
    limite(x, y, direction) {
        if(direction == Ship.DIRECTION_VERTICAL)
            return x + this.longueur <= 10;
        else{ return y + this.longueur <= 10; }
    }

    /* Borne de la grille et des actions a effectuer à l'intérieur */
    borne(x, y, direction) {
        if(this.limite(x, y, direction)) {
            for(let i = 0; i < this.longueur; i++) {
                if(direction == Ship.DIRECTION_VERTICAL){
                    if((this.grille_joueur.coordonnees[x + i][y] == CONST.NAVIRE) ||
                        (this.grille_joueur.coordonnees[x + i][y] == CONST.RATE) ||
                        (this.grille_joueur.coordonnees[x + i][y] == CONST.COULE))
                        return false;
                }else{
                    if((this.grille_joueur.coordonnees[x][y + i] == CONST.NAVIRE) ||
                        (this.grille_joueur.coordonnees[x][y + i] == CONST.RATE) ||
                        (this.grille_joueur.coordonnees[x][y + i] == CONST.COULE))
                        return false;
                }
            }
            return true;
        }else{ return false; }
    }

    /* Score des navires détruits */
    score_degats(){
        this.degats++;
        if(this.degats >= this.max){
            this.degats = this.max;
            this.sunk = true;
            if(!(false)){
                let cases = this.taille_navire();
                for(let i = 0; i < this.longueur; i++)
                    this.grille_joueur.curseur(cases[i].x, cases[i].y, 'sunk', this.joueur);
            }
        }
    }

    /* Espace occupé, au niveau des cases de la grille, par un navire */
    taille_navire() {
        let res = [];
        for(let i = 0; i < this.longueur; i++){
            if(this.direction == Ship.DIRECTION_VERTICAL)
                res[i] = { 'x': this.abscisse + i, 'y': this.ordonnee };
            else
                res[i] = { 'x': this.abscisse, 'y': this.ordonnee + i };
        }
        return res;
    }
    
    /* Placement d'un navire sur la grille de jeu concernée */
    positionner(x, y, direction, unite) {
        this.abscisse = x;
        this.ordonnee = y;
        this.direction = direction;
        if(!(unite)){
            for(let i = 0; i < this.longueur; i++){
                if(this.direction == Ship.DIRECTION_VERTICAL)
                    this.grille_joueur.coordonnees[x + i][y] = CONST.NAVIRE;
                else{ this.grille_joueur.coordonnees[x][y + i] = CONST.NAVIRE; }

            }
        }
    }
}

Ship.DIRECTION_VERTICAL = 0;
Ship.DIRECTION_HORIZONTAL = 1;