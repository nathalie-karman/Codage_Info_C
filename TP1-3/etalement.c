/*
 * Fonctions d'étalement des messages
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "etalement.h"
#include "message.h"
#include "hadamard.h"
#include "agent_life_cycle.h"
#include "rt.h"

char * etaler_un_message(char * message,
						 char * sequence_etalement,
						 int taille_message,
						 int taille_sequence,
						 char * message_etale) {
	int i, j;
	for(i = 0; i < taille_message; i++) {
		for(j = 0; j < taille_sequence; j++) {
			message_etale[i * taille_sequence + j] = message[i] *
				sequence_etalement[j];
		}
	}
	return message_etale;
}

char * etaler(char ** messages,
			  int nb_messages,
			  int taille_message,
			  char ** matrice_hadamard,
			  int taille_matrice,
			  char * etalement) {
	if(nb_messages > taille_matrice) {
		fprintf(stderr,
				"Le nombre de messages (%d) est supérieur aux nombre d'utilisateurs supporté (%d).",
				nb_messages,
				taille_matrice);
		return NULL;
	}
	// Intervalle entre deux séquences choisies de matrice_hadamard
	int intervalle = taille_matrice / nb_messages;
	char resultats[nb_messages][taille_message * taille_matrice];
	int i, j;
	for(i = 0; i < nb_messages; i++) {
		etaler_un_message(messages[i], matrice_hadamard[i * intervalle],
						  taille_message, taille_matrice, resultats[i]);
	}
	for(i = 0; i < taille_message * taille_matrice; i++) {
		etalement[i] = 0;
		for(j = 0; j < nb_messages; j++)
			etalement[i] += resultats[j][i];
	}
	return etalement;
}

void etaler_rt(int envoie, int reception) {
	int taille_matrice, nb_messages, i;
	char ** matrice = generer_hadamard(RT_NB_UTILISATEURS, &taille_matrice);
	char * messages[taille_matrice];
	for(i = 0; i < taille_matrice; i++) {
		if((messages[i] = malloc(RT_TAILLE_MESSAGE)) == NULL) {
			perror("Problème mémoire");
			exit(1);
		}
	}
	char etalement[taille_matrice * RT_TAILLE_MESSAGE];
	
	while(1) {
		read(reception, &nb_messages, sizeof(int));
		printf("nb_messages = %d\n", nb_messages);
		for(i = 0; i < nb_messages; i++)
			read(reception, messages[i], RT_TAILLE_MESSAGE);
		etaler(messages, nb_messages, RT_TAILLE_MESSAGE, matrice,
			   taille_matrice, etalement);
		write(envoie, etalement, taille_matrice * RT_TAILLE_MESSAGE);
	}
}

void etaler_rt_envoyer(agent_t agent, int nb_messages, char ** messages) {
	printf("nb_messages 1 = %d\n", nb_messages);
	write(agent.envoie, &nb_messages, sizeof(int));
	int i;
	for(i = 0; i < nb_messages; i++)
		write(agent.envoie, messages[i], RT_TAILLE_MESSAGE);
}

char * etaler_rt_recevoir(agent_t agent, char * etalement) {
	read(agent.reception, etalement, RT_NB_UTILISATEURS * RT_TAILLE_MESSAGE);
	return etalement;
}

void afficher_etalement(char * etalement,
						int taille_message,
						int taille_sequence) {
	int i;
	for(i = 0; i < taille_message; i++) {
		afficher_message(etalement + i * taille_sequence, taille_sequence);
		if( i < taille_message - 1)
			printf(" ||");
	}
}
