class Ship {
    constructor(type, playerGrid, player) {
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

    isLegal(x, y, direction) {
        if (this.withinBounds(x, y, direction)) {
            for (var i = 0; i < this.shipLength; i++) {
                if (direction === Ship.DIRECTION_VERTICAL) {
                    if (this.playerGrid.cells[x + i][y] === CONST.NAVIRE ||
                        this.playerGrid.cells[x + i][y] === CONST.RATE ||
                        this.playerGrid.cells[x + i][y] === CONST.COULE)
                        return false;
                }
                else {
                    if (this.playerGrid.cells[x][y + i] === CONST.NAVIRE ||
                        this.playerGrid.cells[x][y + i] === CONST.RATE ||
                        this.playerGrid.cells[x][y + i] === CONST.COULE)
                        return false;
                }
            }
            return true;
        }
        else { return false; }
    }

    withinBounds(x, y, direction) {
        if (direction === Ship.DIRECTION_VERTICAL)
            return x + this.shipLength <= Game.dimension;
        else
            return y + this.shipLength <= Game.dimension;
    }

    dommages_scoring() {
        this.damage++;
        if (this.isSunk()) { this.sinkShip(false); }
    }

    isSunk() {
        return this.damage >= this.maxDamage;
    }

    sinkShip(virtual) {
        this.damage = this.maxDamage;
        this.sunk = true;
        if (!virtual) {
            var allCells = this.getAllShipCells();
            for (var i = 0; i < this.shipLength; i++)
                this.playerGrid.curseur(allCells[i].x, allCells[i].y, 'sunk', this.player);
        }
    }

    getAllShipCells() {
        var resObject = [];
        for (var i = 0; i < this.shipLength; i++) {
            if (this.direction === Ship.DIRECTION_VERTICAL)
                resObject[i] = { 'x': this.xPosition + i, 'y': this.yPosition };
            else
                resObject[i] = { 'x': this.xPosition, 'y': this.yPosition + i };

        }
        return resObject;
    }

    create(x, y, direction, virtual) {
        this.xPosition = x;
        this.yPosition = y;
        this.direction = direction;
        if (!virtual) {
            for (var i = 0; i < this.shipLength; i++) {
                if (this.direction === Ship.DIRECTION_VERTICAL)
                    this.playerGrid.cells[x + i][y] = CONST.NAVIRE;
                else
                    this.playerGrid.cells[x][y + i] = CONST.NAVIRE;

            }
        }

    }
}

Ship.DIRECTION_VERTICAL = 0;
Ship.DIRECTION_HORIZONTAL = 1;