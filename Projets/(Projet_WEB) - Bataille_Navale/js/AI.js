class AI{
    constructor(object){
        this.object = object;
        this.grille = new Grid(10);
        this.flotte = new Fleet(this.grille, 2);
        this.proba = [];
        this.init();
        this.update();
    }
    
    /* Tir de l'intelligence artificielle sur la grille du joueur */
    tir(){
        let max_coords;
        let max_proba = 0;
        let max = [];

        /* Tir provenant de l'intelligence artificielle sur les cases du joueur */
        for(let i = 0; i < AI.CALCULE.length; i++){
            let cases = AI.CALCULE[i];
            if(this.proba[cases.x][cases.y] != 0)
                this.proba[cases.x][cases.y] += cases.weight;
        }

        /* Calculer le coup dans les bornes de la grille */
        for(let x = 0; x < 10; x++){
            for(let y = 0; y < 10; y++){
                if(this.proba[x][y] > max_proba){
                    max_proba = this.proba[x][y];
                    max = [{ 'x': x, 'y': y }];
                }else if(this.proba[x][y] == max_proba)
                    max.push({ 'x': x, 'y': y });
            }
        }

        max_coords = Math.random() < 0.1 ? max[Math.floor(Math.random() * max.length)] : max[0];
        let res = this.object.tir(max_coords.x, max_coords.y, CONST.JOUEUR);

        /* Si le jeu est perdu */
        if(Game.jeu_perdu){
            Game.jeu_perdu = false;
            return;
        }

        this.grille.coordonnees[max_coords.x][max_coords.y] = res;

        /* Si un navire est touché */
        if(res == CONST.TOUCHE){
            let flotte_joueur = this.object.flotte_joueur.localisation(
                max_coords.x, max_coords.y);
            if(flotte_joueur.degats >= flotte_joueur.max){
                let type_navires = [];
                for(let i = 0; i < this.flotte.artillerie.length; i++)
                    type_navires.push(this.flotte.artillerie[i].type);
    
                this.flotte.artillerie.splice(type_navires.indexOf(flotte_joueur.type), 1);
 
                let cases = flotte_joueur.taille_navire();
                for(let i = 0; i < cases.length; i++)
                    this.grille.coordonnees[cases[i].x][cases[i].y] = CONST.COULE;
            }
        }
        this.update();
    }

    /* Met l'état de la grille à jour après une action effectuée dessus */
    update() {
        let unite = this.flotte.artillerie;
        let coords;

        /* Réinitialiser la grille de jeu */
        for(let x = 0; x < 10; x++){
            for(let y = 0; y < 10; y++)
                this.proba[x][y] = 0;
        }

        /* Unité navale */
        for(let k = 0; k < unite.length; k++){
            /* Cases de la grille */
            for(let x = 0; x < 10; x++){
                for(let y = 0; y < 10; y++){

                    /* Pour détruire un navire du joueur en position verticale */
                    if(unite[k].borne(x, y, Ship.DIRECTION_VERTICAL)){
                        unite[k].positionner(x, y, Ship.DIRECTION_VERTICAL, true);
                        coords = unite[k].taille_navire();
                        if(this.toucher_case(coords)){
                            for(let i = 0; i < coords.length; i++)
                                this.proba[coords[i].x][coords[i].y] += 5000 * this.case_visee(coords);
                        }else{
                            for(let i = 0; i < coords.length; i++)
                                this.proba[coords[i].x][coords[i].y]++;
                        }
                    /* Pour détruire un navire du joueur en position horizontale */
                    }else if(unite[k].borne(x, y, Ship.DIRECTION_HORIZONTAL)){
                        unite[k].positionner(x, y, Ship.DIRECTION_HORIZONTAL, true);
                        coords = unite[k].taille_navire();
                        if(this.toucher_case(coords)){
                            for(let i = 0; i < coords.length; i++)
                                this.proba[coords[i].x][coords[i].y] += 5000 * this.case_visee(coords);
                        }else{
                            for(let i = 0; i < coords.length; i++)
                                this.proba[coords[i].x][coords[i].y]++;
                        }
                    }

                    if(this.grille.coordonnees[x][y] == CONST.TOUCHE)
                        this.proba[x][y] = 0;
                }
            }
        }
    }
    
    /* Initialise les probabilités par rapport à la grille */
    init(){
        for(let x = 0; x < 10; x++){
            let colonne = [];
            this.proba[x] = colonne;
            for(let y = 0; y < 10; y++){ colonne.push(0); }
        }
    }
    
    /* Espace touché */
    toucher_case(espace){
        for(let i = 0; i < espace.length; i++) {
            if(this.grille.coordonnees[espace[i].x][espace[i].y] == CONST.TOUCHE)
                return true;
        }
        return false;
    }

    /* Si une case est ciblée, tirer dessus */
    case_visee(espace){
        let cases = 0;
        for(let i = 0; i < espace.length; i++){
            if(this.grille.coordonnees[espace[i].x][espace[i].y] == CONST.TOUCHE) 
                cases++;
        }
        return cases;
    }
}

/* Génération aleatoire entre un minimum et maximum entré */
function gen(min, max){
	return Math.random() * (max - min) + min;
}

/* Calcule du coup aléatoire en fonction des cases de la grille */
AI.CALCULE = [
    {'x': 7, 'y': 3, 'weight': gen(10, 20)}, {'x': 6, 'y': 2, 'weight': gen(10, 20)},
    {'x': 3, 'y': 7, 'weight': gen(10, 20)}, {'x': 2, 'y': 6, 'weight': gen(10, 20)},
    {'x': 6, 'y': 6, 'weight': gen(10, 20)}, {'x': 3, 'y': 3, 'weight': gen(10, 20)},
    {'x': 5, 'y': 5, 'weight': gen(10, 20)}, {'x': 4, 'y': 4, 'weight': gen(10, 20)},
    {'x': 0, 'y': 8, 'weight': gen(15, 25)}, {'x': 1, 'y': 9, 'weight': gen(20, 30)},
    {'x': 8, 'y': 0, 'weight': gen(15, 25)}, {'x': 9, 'y': 1, 'weight': gen(20, 30)},
    {'x': 9, 'y': 9, 'weight': gen(20, 30)}, {'x': 0, 'y': 0, 'weight': gen(20, 30)}
];