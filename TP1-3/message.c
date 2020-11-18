/*
 * Fonctions d'affichage des messages
 */

#include <stdio.h>
#include <stdlib.h>

#include "message.h"

void afficher_message(char * message, int taille_message) {
	int i;
	for(i = 0; i < taille_message; i++)
		printf(" %+d", message[i]);
}
