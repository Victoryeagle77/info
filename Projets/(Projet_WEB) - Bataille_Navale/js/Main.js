/* Permet d'effectuer l'animation de cross-fade apres selection d'un titre */
function animation(){
	var i, undefined;
	const e = document.createElement('div');
	let transitions = {
		'transition' : 'transitionend',
		'OTransition' : 'otransitionend', 
		'MozTransition' : 'transitionend',
		'WebkitTransition' : 'webkitTransitionEnd'
	};
    /* Chercher parmis tous les élements que l'on veut animer */
	for(i in transitions) {
		if((transitions.hasOwnProperty(i)) && (e.style[i] !== undefined))
			return transitions[i];
	}
}

/* Fonction de débogage et d'initialisation */
function setDebug(parametre) {
	DEBUG_MODE = parametre;
	localStorage.setItem('DEBUG_MODE', parametre);
	window.location.reload();
}
