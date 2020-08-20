/*** Fonction permettant d'écrire la date actuelle sur la page ***/
function Datation() {
    document.write(new Date().getDate() + "/" + (new Date().getMonth()+1) + "/" + new Date().getFullYear());
}

/*** Récupèration des valeurs dan l'url par découpage de chaine de caractère ***/
function Parametre() {
    let data = [], tmp = [], id = ["nom", "longueur", "largeur"];
    for(let i=0; i<3; i++){
        tmp = location.search.substring(1).split("&")[i].split("=");
        data[i] = unescape(tmp[1]);
    }

    /* Traitement du nom du projet */
    if(data[0].length != 0)
        document.getElementById(id[0]).innerHTML = data[0];
    else 
        document.getElementById(id[0]).innerHTML = "Aucun nom spécifié";

    /* Traitement des dimensions du projet */
    for(let i=1; i<3; i++){
        if(data[i] != 0)
            document.getElementById(id[i]).innerHTML = data[i] + " cm";
        else
            document.getElementById(id[i]).innerHTML = "Aucune dimension spécifiée";
    }
}

/*** Fontion permettant de créer graphiquement des objets,
de la forme que l'on désire, et de les manipuler par leurs dimensions. ***/
function Modelisation() {
    /* Etat booléens différents permettant d'identifier la phase de dessin,
    et de déplacement des points */
    let deplace = false, dessine = false, origine = true;
    /* Ici l'élément svg est notre canvas, commode pour utiliser la librairie d3.min.js */
    let canvas = d3.select('body').select('div').select('#page3').append('svg')
        .attr('height', '800').attr('width', '90%').attr('id', 'c')
        .style({background: '#222'}).style({position: 'relative'})
        .style({margin: 'auto'}).style({border: '3px solid #888'});
    let points = [], g;
    /* Avec d3, définie le comportement lors du déplacement de la souris,
    (Après le placement du premier point d'origine) */
    let bouger = d3.behavior.drag().on('drag', deplacement).on('dragend', function() { deplace = false; });

    /* Permet de gérer le déplacement d'une figure par ses points */
    function deplacement(){
        let points = [], cercle;
        /* Mode déplacement et non de dessin */
        deplace = true;
        let cercles = d3.select(this.parentNode).selectAll('circle');
        d3.select(this).attr('cx', d3.event.x).attr('cy', d3.event.y);
        for (let i = 0; i < cercles[0].length; i++) {
            cercle = d3.select(cercles[0][i]);
            points.push([cercle.attr('cx'), cercle.attr('cy')]);
        }
        d3.select(this.parentNode).select('polygon').attr('points', points);
    }

    /* Génère un code couleur hexadécimale aléatoire */
    function coloration(){
        /* Divise la chaine de caracètre 0123456789ABCDEF,
        (créé une sous-chaine) */
        let chaine = '0123456789ABCDEF'.split('');
        let couleur = '#';
        /* Choisir 6 caractère */
        for (let i = 0; i < 6; i++)
            /* # + couleur hexadécimale */
            couleur += chaine[Math.floor(Math.random() * 16)];
        return couleur;
    }

    /* Permet de terminer une figure en en reliant tous les points */
    function figure(){
        let g = canvas.append('g');
        canvas.select('g.drawPoly').remove();
        g.append('polygon')
        .attr('points', points)
        /* Remplie la forme avec une couleur aléatoire */
        .style('fill', coloration());
        /* Permet de définir les points,
        après la construction d'un segment (points posé) */
        for(let i = 0; i < points.length; i++) {
            circle = g.selectAll('circles')
            /* Allocation du tableau points au Document Object Model, 
            pour une mise à jours sans fuite mémoire. */
            .data([points[i]])
            /* Jointure du tableau de donnée définie par la méthode data(),
            pour définir les éléments à ajouter. */
            .enter().append('circle')
            .attr('cx', points[i][0]).attr('cy', points[i][1])
            .attr('r', 3).attr('fill', '#0f0').attr('is-handle', 'true')
            .style({cursor: 'move'})
            .call(bouger);
        }
        /* Modifier la variable i du tableau points pour qu'elle vale 0, 
        Permettant ainsi de terminer et délier la figure tracé. */
        points.splice(0);
        dessine = false;
    }

    canvas.on('mouseup', function() {
        dessine = true;
        /* Premier point d'une figure à poser à la souris */
        origine = [d3.mouse(this)[0], d3.mouse(this)[1]];
        if(canvas.select('g.drawPoly').empty()) 
            g = canvas.append('g').attr('class', 'drawPoly');
        if(d3.event.target.hasAttribute('is-handle')){ 
            figure(); 
            return;
        };
        points.push(d3.mouse(this));
        g.select('polyline').remove();
        /* Définie l'aspect d'un segment de construction */
        g.append('polyline').attr('points', points).style('fill', 'none').attr('stroke', '#fff');
        for(let i = 0; i < points.length; i++) {
            /* Permet de définir les points (extrémités des segments),
            pendant la construction d'un segment */
            g.append('circle')
            .attr('cx', points[i][0]).attr('cy', points[i][1])
            /* Aire des cercles (taille) */
            .attr('r', 3).attr('fill', 'red').attr('is-handle', 'true')
            .style({cursor: 'crosshair'});
        }
    });

    canvas.on('mousemove', function() {
        let g = d3.select('g.drawPoly');
        /* Tracer une ligne */
        g.select('line').remove();
        /* La ligne est définie comme un segment partant d'un point a,
        pour atteindre un point b */
        g.append('line').attr('x1', origine[0]).attr('y1', origine[1])
        .attr('x2', d3.mouse(this)[0] + 2).attr('y2', d3.mouse(this)[1])
        /* Permet de prévisualiser un segment de construction,
        (qui n'est pas encore) */
        .attr('stroke', '#fff').attr('stroke-width', 1);
    })
}