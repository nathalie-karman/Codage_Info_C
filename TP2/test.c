/*
 * Programme de test des différents codeurs.
 */

#include <stdio.h>
#include <stdlib.h>

#include "codeur_lm.h"
#include "codeur_gold.h"
#include "codeur_jpl.h"

void afficher_sequence(char * sequence, int longueur) {
	int i;
	for(i = 0; i < longueur; i++)
		sequence[i] ? putchar('1') : putchar('0');
}

int main() {
	
	printf("\nCODEUR À LONGUEUR MAXIMALE\n\n");
	
	char registres[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	
	printf("Polynôme de génération = [4; 1]\n");
	int n = 4;
	int l = long_max(n);
	char sequence[l];
	int polynome[] = {4, 1, 0};
	code_lm(registres, polynome, l, sequence);
	afficher_sequence(sequence, l);
	putchar('\n');
	
	printf("Polynôme de génération = [5; 2]\n");
	n = 5;
	l = long_max(n);
	char seq2[l];
	int pol2[] = {5, 2, 0};
	code_lm(registres, pol2, l, seq2);
	afficher_sequence(seq2, l);
	putchar('\n');
	
	printf("Polynôme de génération = [5; 4; 2; 1]\n");
	n = 5;
	l = long_max(n);
	char seq3[l];
	int pol3[] = {5, 4, 2, 1, 0};
	code_lm(registres, pol3, l, seq3);
	afficher_sequence(seq3, l);
	putchar('\n');
	
	printf("\nCODEUR GOLD\n\n");
	
	printf("Polynômes : [5; 2], [5; 4; 2; 1]\n");
	n = 5;
	l = long_max(n);
	char seq4[l];
	int pol41[] = {5, 2, 0};
	int pol42[] = {5, 4, 2, 1, 0};
	code_gold(registres, pol41, pol42, l, seq4);
	afficher_sequence(seq4, l);
	putchar('\n');
	
	printf("\nCODEUR JPL\n\n");
	
	printf("Polynômes : [2; 1], [3; 1] et [5; 2]\n");
	n = 5;
	l = long_max(n);
	char seq5[l];
	int pol51[] = {2, 1, 0};
	int pol52[] = {3, 1, 0};
	int pol53[] = {5, 2, 0};
	code_jpl(registres, l, seq5, pol51, pol52, pol53, NULL);
	afficher_sequence(seq5, l);
	putchar('\n');
	
	return 0;
}
