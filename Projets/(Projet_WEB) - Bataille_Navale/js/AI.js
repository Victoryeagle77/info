class AI {
    constructor(gameObject) {
        this.gameObject = gameObject;
        this.virtualGrid = new Grid(Game.dimension);
        this.virtualFleet = new Fleet(this.virtualGrid, CONST.ADVERSAIRE);
        this.probGrid = [];
        this.initProbs();
        this.updateProbs();
    }

    tir(){
        var maxProbability = 0;
        var maxProbCoords;
        var maxProbs = [];
        for (var i = 0; i < AI.CALCULE.length; i++) {
            var cell = AI.CALCULE[i];
            if (this.probGrid[cell.x][cell.y] !== 0) {
                this.probGrid[cell.x][cell.y] += cell.weight;
            }
        }
        for (var x = 0; x < Game.dimension; x++) {
            for (var y = 0; y < Game.dimension; y++) {
                if (this.probGrid[x][y] > maxProbability) {
                    maxProbability = this.probGrid[x][y];
                    maxProbs = [{ 'x': x, 'y': y }];
                }
                else if (this.probGrid[x][y] === maxProbability) {
                    maxProbs.push({ 'x': x, 'y': y });
                }
            }
        }
        maxProbCoords = Math.random() < 0.1 ?
            maxProbs[Math.floor(Math.random() * maxProbs.length)] : maxProbs[0];
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
    }
    updateProbs() {
        let unite = this.virtualFleet.fleetRoster;
        let coords;
        this.resetProbs();
        for (let k = 0; k < unite.length; k++) {
            for (let x = 0; x < Game.dimension; x++) {
                for (let y = 0; y < Game.dimension; y++) {
                    if (unite[k].isLegal(x, y, Ship.DIRECTION_VERTICAL)) {
                        unite[k].create(x, y, Ship.DIRECTION_VERTICAL, true);
                        coords = unite[k].getAllShipCells();
                        if (this.passesThroughHitCell(coords)) {
                            for (let i = 0; i < coords.length; i++)
                                this.probGrid[coords[i].x][coords[i].y] += 5000 * this.numHitCellsCovered(coords);
                        }
                        else {
                            for (let i = 0; i < coords.length; i++)
                                this.probGrid[coords[i].x][coords[i].y]++;
                        }
                    }
                    if (unite[k].isLegal(x, y, Ship.DIRECTION_HORIZONTAL)) {
                        unite[k].create(x, y, Ship.DIRECTION_HORIZONTAL, true);
                        coords = unite[k].getAllShipCells();
                        if (this.passesThroughHitCell(coords)) {
                            for (var j = 0; j < coords.length; j++)
                                this.probGrid[coords[j].x][coords[j].y] += 5000 * this.numHitCellsCovered(coords);
                        }
                        else {
                            for (var _j = 0; _j < coords.length; _j++)
                                this.probGrid[coords[_j].x][coords[_j].y]++;
                        }
                    }
                    if (this.virtualGrid.cells[x][y] === CONST.TOUCHE)
                        this.probGrid[x][y] = 0;
                }
            }
        }
    }

    initProbs() {
        for (var x = 0; x < Game.dimension; x++) {
            var colonne = [];
            this.probGrid[x] = colonne;
            for (var y = 0; y < Game.dimension; y++)
                colonne.push(0);
        }
    }

    resetProbs() {
        for (var x = 0; x < Game.dimension; x++) {
            for (var y = 0; y < Game.dimension; y++) {
                this.probGrid[x][y] = 0;
            }
        }
    }

    findHumanShip(x, y) {
        return this.gameObject.flotte_joueur.localisation(x, y);
    }

    passesThroughHitCell(espace) {
        for (var i = 0; i < espace.length; i++) {
            if (this.virtualGrid.cells[espace[i].x][espace[i].y] === CONST.TOUCHE)
                return true;
        }
        return false;
    }

    numHitCellsCovered(espace) {
        var cases = 0;
        for (var i = 0; i < espace.length; i++) {
            if(this.virtualGrid.cells[espace[i].x][espace[i].y] === CONST.TOUCHE)
            cases++;
        }
        return cases;
    }
}

function gen(min, max) {
	return Math.random() * (max - min) + min;
}

AI.CALCULE = [
    {'x': 7, 'y': 3, 'weight': gen(10, 20)}, {'x': 6, 'y': 2, 'weight': gen(10, 20)},
    {'x': 3, 'y': 7, 'weight': gen(10, 20)}, {'x': 2, 'y': 6, 'weight': gen(10, 20)},
    {'x': 6, 'y': 6, 'weight': gen(10, 20)}, {'x': 3, 'y': 3, 'weight': gen(10, 20)},
    {'x': 5, 'y': 5, 'weight': gen(10, 20)}, {'x': 4, 'y': 4, 'weight': gen(10, 20)},
    {'x': 0, 'y': 8, 'weight': gen(15, 25)}, {'x': 1, 'y': 9, 'weight': gen(20, 30)},
    {'x': 8, 'y': 0, 'weight': gen(15, 25)}, {'x': 9, 'y': 1, 'weight': gen(20, 30)},
    {'x': 9, 'y': 9, 'weight': gen(20, 30)}, {'x': 0, 'y': 0, 'weight': gen(20, 30)}
];







