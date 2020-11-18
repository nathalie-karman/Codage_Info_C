/*
 * Utilitaires pour les différents modules.
 */

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int puis2(int n) {
	int i, res = 1;
	for(i = 1; i <= n; i++)
		res *= 2;
	return res;
}

char * tab_xor(char * dest, char * t1, char * t2, int longueur) {
	int i;
	for(i = 0; i < longueur; i++)
		dest[i] = xor(t1[i], t2[i]);
	return dest;
}
