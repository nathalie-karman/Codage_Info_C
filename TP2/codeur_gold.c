/*
 * Définition des fonctions permettant de générer un code de Gold.
 */

#include <stdio.h>
#include <stdlib.h>

#include "codeur_gold.h"
#include "codeur_jpl.h"

char * code_gold(char * registres,
				 int * pol1,
				 int * pol2,
				 int longueur,
				 char * sequence) {
	return code_jpl(registres, longueur, sequence, pol1, pol2, NULL);
}
