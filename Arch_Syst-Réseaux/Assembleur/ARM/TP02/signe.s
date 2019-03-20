/* 
Question 2 ] Signe
Ecriver un programme vérifiant si un nombre est négatif, positif ou zéro.
Avec un opérateur spécifique : teq
Si le nombre est négatif il sera affiché "Negatif !", 
sinon il sera affiché "Positif !" ou "Zero !" si le chiffre .
*/

.equ SYS_EXIT, 1
.equ SYS_WRITE, 4

.arm
.data

/* Définition en mémoire */
entier: .word -1
event_1: .asciz "Negatif !\n"
len_event_1 = . - event_1
event_2: .asciz "Positif !\n"
len_event_2 = . - event_2
event_3: .asciz "Zero !\n"
len_event_3 = . - event_3

.text
.globl _start

_start:
    /* Chargement de constante définies */
    ldr r0, =entier
    /* Chargment depuis la mémoire */
    ldr r1, [r0]
    /* teq == Comparaison par un ou exlusif bit à bit,
    entre le contenu de r1 et 0. (Si les deux sont identiques,
    la valeur est vrai) */
    teq r1, #0
    mov r0, #0
    /* Chargement de valeur si la condition est inférieur à 0 */
    ldrlt r1, =event_1
    ldrlt r2, =len_event_1
    /* Chargement de valeur si la condition est supérieur à 0 */
    ldrgt r1, =event_2
    ldrgt r2, =len_event_2
    /* Chargement de valeur si la condition est égale à 0 */
    ldreq r1, =event_3
    ldreq r2, =len_event_3
    /* Permet de passer à une étiquette "sortie" */
    b sortie

    sortie:
        /* Affichage sur la sortie standard 4 */
        mov r7, #SYS_WRITE
        swi #0
        /* Sortie standard*/
        mov r0, #0
        mov r7, #SYS_EXIT
        swi #0
.end
