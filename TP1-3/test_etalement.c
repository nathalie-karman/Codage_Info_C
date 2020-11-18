/*
 * Test des modules etalement.[ch] et desetalement.[ch].
 */

#include <stdio.h>
#include <stdlib.h>

#include "etalement.h"
#include "desetalement.h"
#include "message.h"
#include "hadamard.h"

int main() {
	char m1[] = {+1, -1, +1};
	char m2[] = {-1, -1, +1};
	char m3[] = {-1, +1, +1};
	char m4[] = {+1, +1, -1};
	char * messages[] = {m1, m2, m3, m4};
	int nb_messages = 4;
	int taille_message = 3;
	
	printf("Messages :\n");
	int i;
	for(i = 0; i < nb_messages; i++) {
		afficher_message(messages[i], taille_message);
		printf("\n");
	}
	
	int taille_matrice;
	char ** matrice = generer_hadamard(nb_messages, &taille_matrice);
	char etalement[taille_message * taille_matrice];
	etaler(messages, nb_messages, taille_message, matrice, taille_matrice,
		   etalement);
	
	printf("Étalement : ");
	afficher_etalement(etalement, taille_message, taille_matrice);
	printf("\n");
	
	/* -------- DESETALEMENT --------- */
	
	char ** messages_decodes = malloc(sizeof(char *) * taille_matrice);
	for(i = 0; i < taille_matrice; i++)
		messages_decodes[i] = malloc(sizeof(char) * taille_message);
	
	nb_messages = desetaler(etalement, taille_message * taille_matrice, matrice,
							taille_matrice, messages_decodes);
	
	printf("Messages :\n");
	for(i = 0; i < nb_messages; i++) {
		afficher_message(messages_decodes[i], taille_message);
		printf("\n");
	}
	
	for(i = 0; i < taille_matrice; i++)
		free(messages_decodes[i]);
	free(messages_decodes);
	
	return 0;
}
