/**
* @function deploiement
* Permet de monter l'application "Riot",
* et de d&eacute;finir quel composant utiliser.
* @see results
*/
function deploiement(){
    riot.compile().then(()=>{
        riot.install(function(component){
            component.api = new results();
        })
        riot.mount('app');
    });
}

/**
* @function cache
* Permet de d&eacute;finir les donn&eacute;es recherch&eacute;es,
* de les obtenir et de les stocker en cache,
* pour v&eacute;rifier s'il n'y a pas de staturation de requetes.
*/
function cache(){
    /**** Artiste ou groupe de musique ****/
    this.artists = [];
    /* Définir ce qu'est censé être un auteur dans la recherche */
    this.setCreator = function(createur){
        for(let i = 0; i < createur.artists.length; i++){
            if((this.artists[i] == undefined) || 
                    (!(this.artists,createur.artists[i])))
                this.artists.push(createur.artists[i]);
        }
    }
    /* Obtenir les données de l'auteur */
    this.getCreator = function(element){
        let cache = [];
        for(let i = 0; i < this.artists.length; i++){
            if(element == this.artists[i].name.substring(0, element.length))
                cache.push(this.artists[i]);
        }
        return cache;
    }

    /**** Musique ou chanson ****/
    this.musics = [];
    /* Définir ce qu'est censé être une musique dans la recherche */
    this.setSong = function(son){
        for(let i = 0; i < son.recordings.length; i++){
            if((this.musics[i] == undefined) || 
                    (!(this.musics, son.recordings[i]))) 
                this.musics.push(son.recordings[i]);
        }		
    }
    /* Obtenir les données d'une musique */
    this.getSong = function(element){
        let cache = [];
        for(let i = 0; i < this.musics.length; i++){
            if(element == this.musics[i].title.substring(0, element.length))
                cache.push(this.musics[i]);
        }
        return cache;
    }

    /**** Album de musique ****/
    this.albums = [];
    /* Définir ce qu'est censé être un album dans la recherche */
    this.setAlbum = function(album){
        for(let i = 0; i < album.releases.length; i++) {
            if((this.albums[i] == undefined) || 
                    (!(this.albums, album.releases[i])))
                this.albums.push(album.releases[i]);
        }		
    }
    /* Obtenir les données d'un ablum */
    this.getAlbum = function(element){
        let cache = [];
        for(let i = 0; i < this.albums.length; i++) {
            if(element == this.albums[i].title.substring(0, element.length))
                cache.push(this.albums[i]);
        }
        return cache;
    }
}

/**
* @function results
* Permet d'envoyer des requête ajax pour extraire,
* en json, les informations dont on a besoin,
* avec les informations dans le pr&eacute;sente dans le cache.
* @see cache
*/
function results(){
    const message = "Erreur de réseau ou saisie trop rapide";
    /* Mémoire cache */
    this.tmp = new cache();

    /**** Requête de recherche d'un élément par url musicBrain ****/
    this.search = function(url, parametre){
        return new Promise((envoie, echec)=>{
            let ajax = new XMLHttpRequest();
            ajax.header = "Access-Control-Allow-Origin:*";
            ajax.open('GET', url + parametre + "&fmt=json");
            ajax.responseType = "json";
            ajax.onload = function(){
                if(ajax.status === 200){
                    try{
                        localStorage.setItem(url, ajax.response);
                    }catch(e){ localStorage.clear(); }
                    envoie(ajax.response);
                }
                /* Problème venant de connexion réseau aux bases de donnée de MusicBrain,
                ou d'un envoie de requête trop important par saisie au clavier trop rapide. */
                else{
                    echec(message);
                    alert(message);
                }
            };
            /* Problème venant de connexion réseau aux bases de donnée de MusicBrain,
            ou d'un envoie de requête trop important par saisie au clavier trop rapide. */
            ajax.onerror = function(){ 
                echec(message);
                alert(message);
            };
            ajax.send();
        })	
    }

    /**** Requête pour l'auteur d'une musique ****/
    this.getCreator = function(createur){
        /* S'il y a présence, dans le cache, d'éléments pour cette requête, 
        on relève simplement l'élément cherché. */
        if(this.tmp.getCreator(createur).length != 0)
            return new Promise((envoie)=>{envoie(this.tmp.getCreator(createur));})
        /* Sinon, on envoie une requête correspondante à l'élément recherché. */
        else{
            return new Promise((envoie)=>{
                this.search("https://musicbrainz.org/ws/2/artist/?query=artist:", 
                        createur).then((object)=>{
                    this.tmp.setCreator(object);
                    envoie(object.artists);
                });
            })
        }
    };

    /**** Requête pour une musique ****/
    this.getSong = function(son){
        /* S'il y a présence, dans le cache, d'éléments pour cette requête, 
        on relève simplement l'élément cherché. */
        if(this.tmp.getSong(son).length != 0)
            return new Promise((envoie)=>{envoie(this.tmp.getSong(son));})
        /* Sinon, on envoie une requête correspondante à l'élément recherché. */
        else{
            return new Promise((envoie)=>{
                this.search("https://musicbrainz.org/ws/2/recording/?query=recording:", 
                        son).then((object)=>{
                    this.tmp.setSong(object);
                    envoie(object.recordings);
                });
            })
        }
    };

    /**** Requête pour un album ****/
    this.getAlbum = function(album){
        /* S'il y a présence, dans le cache, d'éléments pour cette requête, 
        on relève simplement l'élément cherché. */
        if(this.tmp.getAlbum(album).length != 0)
            return new Promise((envoie)=>{envoie(this.tmp.getAlbum(album));})
        /* Sinon, on envoie une requête correspondante à l'élément recherché. */
        else{
            return new Promise((envoie)=>{
                this.search("https://musicbrainz.org/ws/2/release/?query=release:", 
                        album).then((object)=>{
                    this.tmp.setAlbum(object);
                    envoie(object.releases);
                });
            })
        }
    }
}