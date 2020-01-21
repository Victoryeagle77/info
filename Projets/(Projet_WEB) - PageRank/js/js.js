/** 
* Programme permettant de calculer le pageRank d'un élève dans une ou plusieurs matières,
* selon le nombre de fois que l'on a voté pour lui, 
* et d'en déterminer un classement, du plus voté au moins voté.
* @author Ganaël Chabraison
* @author Arthur Chenu
* @version finale
*/

/** 
* @constructor main()
* est la fonction principale appelée dans index.html
* contenant toutes les fonctions nécessaires :
* @see selection() : A la définition des évènements produits lors du coche des cases.
* @see lister(ordre) : Au calcul du pageRank pour chaque matières séléctionnées, 
* et au listing des élèves établit ensuite à partir de ces informations.
* @see trier(pagerank) : Au calcul du pageRank pour chaque matières séléctionnées, 
* et au listing des élèves établit ensuite à partir de ces informations.
* @see charger() : Au calcul du pageRank pour chaque matières séléctionnées, 
* et au listing des élèves établit ensuite à partir de ces informations.
* @see afficher(id) : A l'affichage des résultats sous forme de tableau.
*/
function main(){

    const utilisateur = {};
    const matiere = [];

    /* Appel, dans la fonction principale du programme,
    de la fonction de séléction des matières. */
    selection();

    /** 
    * @constructor afficher()
    * permet de déterminer l'affichage du classement,
    * sous forme d'un tableau html à plusieurs colonnes. 
    * @param {String} id : Identifie un étudiant.
    */
    function afficher(id){
        /* En-tête du tableau */
        document.getElementById('classificateur').innerHTML = "<th>Classement</th>"
            + "<th>Logins</th>" + "<th>PageRank</th>";
        /* Création du tableau de récupération des valeurs */
	for(let i in id){
            /* Colonnes du tableau */
            const colonne = [];
            const container =  document.createElement('tr');
            for(let j=0; j<3; j++){
                colonne[j] = document.createElement('td');   
                /* Détermination des éléments à créer dans le tableau */
                if(j == 0) 
                    colonne[0].appendChild( /* Rang des étudiants */
                        document.createTextNode(i))
                else if(j == 1) 
                    colonne[1].appendChild( /* Logins des étudiants */
                        document.createTextNode(id[i][1]));
                else
                    colonne[2].appendChild( /* PageRakn des étudiants */
                        document.createTextNode(id[i][2]));    
                /* Placer les éléments précedemment créés dans les colonnes */
                container.appendChild(colonne[j]); 
            }
            /* Placer les colonnes dans le tableau */
            document.getElementById('classificateur').appendChild(container);
	}
    }
    
    /** 
    * @constructor trier()
    * permet de trier les étudiants par leur login et par matière,
    par rapport au pageRank, du plus au moins élevé.
    * @param {number[]} pagerank : calcul du pageRank de chaque étudiant
    * @see afficher(id)
    */
    function trier(pagerank){
        const classement = [];
        const id = {};
        let j = 0;
        /* Moyenne entre chaque pageRank pour une matière */
        for(let i = 0; i < pagerank.length; i++) {
            /* Le pageRank moyen pour plusieurs matières correspond à :
            (PageRank d'une matière)/(nombre de matière) */
            pagerank[i] /= matiere.length;
            classement[i] = pagerank[i];
        }

        /* Trie les chaines de caractères définies par les logins,
        et classe par odre décroissant, du plus grand au plus petit,
        en fonction du pageRank. */
        classement.sort().reverse();

        /* Pour les logins d'étudiants correspondant, dans l'ensemble des logins */
        for(let login in logins) {
            let rang;
            /* Compte les étudiants en fonction de leur pageRank correspondant */
            for(let k = 0; k < pagerank.length; k++) {
                /* Si le classement, pour un étudiant,
                correpond à son pageRank dans une matière */
                if(classement[k] == pagerank[j]){ rang = k + 1; break; }
            }
            let ordre = rang;

            /* Tant que le rang d'un élève est trouvé */
            while(id[rang] != undefined){ rang++; }
            
			/* Données dans le tableau à afficher */
            id[rang] = { ordre }; /* rang des étudiants */
            id[rang][1] = login; /* Logins des étudiants */
            id[rang][2] = pagerank[j];	/* PageRank */
            j++; /* Nombre de fois qu'il faut afficher */
        }
	afficher(id);
    }

    /**
    * @constructor lister()
    * permet de lister les étduiants selon la configuration des votes,
    * en extrayant du fichier JavaScript "pagerank.js", l'objet "votes",
    * en vérifiant qu'un vote correponde bien à un élève.
    * @param {Object} votes - Définit les logins votés dans une matière
    * @param {number} ordre - Définit la position des étudiants
    */
    function lister(ordre){
        for(let id in logins) {
            /* On extrait les données de la variable "votes" */
            if(votes[id] == undefined) { votes[id] = ordre; }
            /* On traite les étudiants n'ayant voté pour personne */
            for(let i = 0; i < matiere.length; i++) {
                if(votes[id][matiere[i]] == undefined){ votes[id] = ordre; } 
            }
        }
        /* Tableau de votes pour un élève dans une ou plusieurs matières */
        for(let login in logins) {
            /* Pour le nombre de matières choisies */
            for (let i = 0; i < matiere.length; i++) {
                let j = 0;
                /* On relève les étdudiants ayant votés */
                utilisateur[login][matiere[i]] = [];
                for(let elu in logins) {
                    /* Pour le nombre de votes relevé pour un étudiant dans une matière */
                    for(let k = 0; k < votes[elu][matiere[i]].length; k++) {
                        if(login == votes[elu][matiere[i]][k]) {
                            /* On compte le nombre de votes */	
                            utilisateur[login][matiere[i]][j] = elu;
                            j++;
                        }
                    }
                }
            }
        }
    }

    /**
    * @constructor charger()
    * permet de paramètrer les éléments d'affichage et de calcul du pageRank,
    * pour chaque étudiant dans une ou plusieurs matières, 
    * après séléction des matières par les cases à cocher.
    * @see lister(rang)
    * @see trier(pageRank)
    */
    function charger(){
        let liste = 0;
        const classificateur = [],  pagerank = [], tmp = [];
        const rang = {};
        
        /* Permet de relever tous les logins et de les compter */
        for(let login in logins) {
            utilisateur[login] = [];
            classificateur[liste] = login;
            /* Récupération des numéros de la liste */
            liste++;
        }

        /* Rechargement du tableau en cas de changement de matière */
        const load = document.getElementById("classificateur");
        while(load.firstChild)
            load.removeChild(load.firstChild);
        
        /* Si auncune matière n'est séléctionnée, ne rien afficher */
        if(matiere.length == 0) { return; }

        for(let i = 0; i < matiere.length; i++)
            /* Pour toutes les matières séléctionnées */
            rang[matiere[i]] = classificateur;

        lister(rang);

        /* Pour qu'il soit compris entre 0 et 1, 
        le pageRank de chaque étudiant est initialisé à 0. */
		for(let i = 0; i < liste; i++){ pagerank[i] = 0; }
        
        /* Pour tous les étudiants votés dans une matière */
        for(let i = 0; i < matiere.length; i++){
            let classement = {};
            const res = {};
            /* Pour tous les logins dans l'odre inverse */
            for(let login in logins){ classement[login] = 1/liste; }
            /* Les noeuds sont ici les possibilité de tomber,
            sur une ou plusieurs matières */
            for(let login in logins) {
                lien = utilisateur[login][matiere[i]];
                /* Probabilité de tomber sur un login pour une matière */
                let noeud = 0;
                for(let j = 0; j < lien.length; j++)
                    /* Permet de sommer les division des liens entrants par les liens sortants */
                    noeud += ((classement[lien[j]]) / (votes[lien[j]][matiere[i]].length));					
                /* Le calcul du pageRank est défini ainsi (1-p)/n+p*(somme des noeuds), 
                avec p défini à 0.85, donc pageRank = 0.15/n+0.85*(somme des noeuds). 
                On a ici la probabilité qu'un étudiant soit voté aléatoirement par quelqu'un. */
                res[login] = 0.15/liste + 0.85*noeud;
            }
            classement = res;
            tmp[i] = classement;
        }
	
	for(let i = 0; i < tmp.length; i++) {
           /* Pour toutes les matières séléctionnées, 
           on en fait la somme totale. */
	   let j = 0;
	   for(let k in tmp[i]){ pagerank[j] += tmp[i][k]; j++; }
        }
        trier(pagerank);
    }

    /**
    * @constructor selection()
    * permet de définir les actions lors de la séléction,
    * ou non, d'une case à cocher pour une ou plusieurs matières.
    * @see charger()
    */
    function selection(){
        /* Relève par leur id, les noms de matières séléctionnées */ 
        document.querySelectorAll("input").forEach(function(element) {
            /* Charger la page avec toutes les matières décochées */
            const checkbox = document.getElementsByTagName('input'); 
            for(let i = 0; i < checkbox.length; i++){ 
                if(checkbox[i].type=='checkbox'){ checkbox[i].checked = false; }
            }
            /* Si une matière est cochée */
            element.addEventListener('click', function(e) { 
                /* Ajoute dans le tableau la matière cochée, identifiée par son id html */
                if(element.checked == true){ matiere.push(element.id); }
                /* Ne permet de charger la valeur d'une matière,
                qu'une seule fois lorsqu'elle est cochée */
                else{ matiere.splice(matiere.indexOf(element.id), 1); }
                charger();
            });
        });
    }
}
