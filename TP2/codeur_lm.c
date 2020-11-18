/*
 * Définition des fonctions permettant de générer un code à longueur maximale.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "codeur_lm.h"
#include "utils.h"

char * code_lm(char * registres, int * polynome, int longueur, char * sequence)
{
	int n = polynome[0], i, i_seq;
	char reg[n];
	char reg_suiv[n];
	
	/* Initialisation */
	memcpy(reg, registres, n);
	
	/* Copie du dernier registre dans la séquence */
	sequence[0] = 1;
	
	for(i_seq = 1; i_seq < longueur; i_seq++) {
		/* Décalage */
		for(i = 0; i < n - 1; i++)
			reg_suiv[i + 1] = reg[i];
		
		/* Calcul du premier registre */
		reg_suiv[0] = 0;
		for(i = 0; polynome[i] != 0; i++)
			reg_suiv[0] = xor(reg_suiv[0], reg[polynome[i] - 1]);
		
		/* Recopie dans reg[] */
		memcpy(reg, reg_suiv, n);
		
		/* Copie du dernier registre dans la séquence */
		sequence[i_seq] = reg[n - 1];
	}
	
	return sequence;
}
