/*
 * Déclaration des fonctions permettant de générer un code de Gold.
 */

#ifndef __CODEUR_GOLD_H__
#define __CODEUR_GOLD_H__



/*
 * Retourne un code de Gold de longueur longueur dans sequence.
 * registres : vecteur d'initialisation des registres.
 * pol1 : tableau représentant le premier polynôme. La première valeur est le
 * nombre d'étages n. Un 0 indique la fin du tableau.
 * pol2 : deuxième polynôme.
 * longueur : longueur de la séquence à retourner.
 * sequence : zone mémoire où écrire le résultat. Doit être de taille longueur.
 */
char * code_gold(char * registres,
				 int * pol1,
				 int * pol2,
				 int longueur,
				 char * sequence);



#endif // __CODEUR_GOLD_H__
