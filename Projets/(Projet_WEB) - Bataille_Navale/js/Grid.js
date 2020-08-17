class Grid{
    constructor(dimension){
        this.dimension = dimension;
        this.coordonnees = [];
        this.init();
    }

    /* Initialisation de la grille de jeu avec toutes ses cases vides */
    init(){
        for(let x = 0; x < this.dimension; x++){
            let colonne = [];
            this.coordonnees[x] = colonne;
            for(let y = 0; y < this.dimension; y++){ colonne.push(CONST.VIDE); }
        }
    }

    /* Cible lockée */
    curseur(x, y, type, cible) {
        let player;
        let classes = ['cell', 'cell-' + x + '-' + y, 'grid-' + type];
        /* S'il s'agit du joueur */
        if(cible == CONST.JOUEUR){ player = 'player'; }
        /* S'il s'agit d" l'intelligence artificielle */
        else if(cible == CONST.IA){ player = 'AI'; }

        switch(type){
            case CONST.STYLE_VIDE:
                this.coordonnees[x][y] = CONST.VIDE;
            break;
            case CONST.STYLE_NAVIRE:
                this.coordonnees[x][y] = CONST.NAVIRE;
            break;
            case CONST.STYLE_RATE:
                this.coordonnees[x][y] = CONST.RATE;
            break;
            case CONST.STYLE_TOUCHE:
                this.coordonnees[x][y] = CONST.TOUCHE;
            break;
            case CONST.STYLE_COULE:
                this.coordonnees[x][y] = CONST.COULE;
            break;
            default:
                this.coordonnees[x][y] = CONST.VIDE;
            break;
        }
        document.querySelector('.' + player + ' .cell-' + x + '-' + y).setAttribute('class', classes.join(' '));
    }

    /* Navire non-endommagé */
    navire_sauf(x, y){ return this.coordonnees[x][y] == CONST.NAVIRE; }

    /* Navire endommagé */
    navire_evite(x, y){ return this.coordonnees[x][y] == CONST.RATE; }

    /* Navire détruit */
    navire_endommage(x, y){
        return this.coordonnees[x][y] == CONST.TOUCHE || this.coordonnees[x][y] == CONST.COULE;
    }
}
