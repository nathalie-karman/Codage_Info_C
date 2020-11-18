/*
 * Déclaration des fonctions permettant de générer un code JPL.
 */

#ifndef __CODEUR_JPL_H__
#define __CODEUR_JPL_H__



/*
 * Retourne un code JPL de longueur longueur dans sequence.
 * registres : vecteur d'initialisation des registres.
 * longueur : longueur de la séquence à retourner.
 * sequence : zone mémoire où écrire le résultat. Doit être de taille longueur.
 * pol* : tableau représentant le polynôme. La première valeur est le nombre
 * d'étages n. Un 0 indique la fin du tableau.
 * La liste des polynômes doit être terminée d'un paramètre à NULL.
 */
char * code_jpl(char * registres,
				int longueur,
				char * sequence,
				/*int * pol1,*/
				...);



#endif // __CODEUR_JPL_H__
