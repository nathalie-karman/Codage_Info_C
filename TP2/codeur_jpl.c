/*
 * Définition des fonctions permettant de générer un code JPL.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "codeur_jpl.h"
#include "codeur_lm.h"

char * code_jpl(char * registres,
				int longueur,
				char * sequence,
				/*int * pol1,*/
				...) {
	memset(sequence, 0, longueur);
	char seq_tmp[longueur];
	va_list ap;
	va_start(ap, sequence);
	int * pol = va_arg(ap, int *);
	while(pol != NULL) {
		code_lm(registres, pol, longueur, seq_tmp);
		tab_xor(sequence, sequence, seq_tmp, longueur);
		pol = va_arg(ap, int *);
	}
	va_end(ap);
	return sequence;
}
