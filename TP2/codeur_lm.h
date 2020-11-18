/*
 * Déclaration des fonctions permettant de générer un code à longueur maximale.
 */

#ifndef __CODEUR_LM_H__
#define __CODEUR_LM_H__

#include "utils.h"



/*
 * Calcule la longueur maximale à partir du nombre d'étages.
 */
#define long_max(n) (puis2(n) - 1)



/*
 * Retourne un code de longueur maximale 2^n - 1 dans sequence.
 * registres : vecteur d'initialisation des registres.
 * polynome : tableau représentant le polynôme. La première valeur est le nombre
 * d'étages n. Un 0 indique la fin du tableau.
 * longueur : longueur de la séquence à retourner.
 * sequence : zone mémoire où écrire le résultat. Doit être de taille longueur.
 */
char * code_lm(char * registres, int * polynome, int longueur, char * sequence);



#endif // __CODEUR_LM_H__
