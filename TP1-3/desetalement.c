/*
 * Fonctions de désétalement des messages reçus
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "desetalement.h"
#include "rt.h"
#include "hadamard.h"

char * desetaler_un_message(char * recu,
							char * sequence_etalement,
							int taille_recu,
							int taille_sequence,
							char * message) {
	char inter[taille_recu];
	int i, j;
	for(i = 0; i < taille_recu; i++) {
		inter[i] = recu[i] * sequence_etalement[i % taille_sequence];
	}
	int taille_message = taille_recu / taille_sequence;
	char somme;
	for(i = 0; i < taille_message; i++) {
		somme = 0;
		for(j = 0; j < taille_sequence; j++) {
			somme += inter[i * taille_sequence + j];
		}
		message[i] = somme / taille_sequence;
	}
	return message;
}

void desetaler_rt(int envoie, int reception) {
	int taille_matrice, i;
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
		read(reception, etalement, taille_matrice * RT_TAILLE_MESSAGE);
		desetaler(etalement, taille_matrice * RT_TAILLE_MESSAGE, matrice,
				  taille_matrice, messages);
		for(i = 0; i < taille_matrice; i++)
			write(envoie, messages[i], RT_TAILLE_MESSAGE);
	}
}

void desetaler_rt_envoyer(agent_t agent, char * etalement) {
	write(agent.envoie, etalement, RT_NB_UTILISATEURS * RT_TAILLE_MESSAGE);
}

char ** desetaler_rt_recevoir(agent_t agent, char ** messages) {
	int i;
	for(i = 0; i < RT_NB_UTILISATEURS; i++)
		read(agent.reception, messages[i], RT_TAILLE_MESSAGE);
	return messages;
}

int desetaler(char * recu,
			  int taille_recu,
			  char ** matrice_hadamard,
			  int taille_matrice,
			  char ** messages) {
	int i, j = 0;
	for(i = 0; i < taille_matrice; i++) {
		desetaler_un_message(recu, matrice_hadamard[i], taille_recu,
							 taille_matrice, messages[j]);
		if(messages[j][0])
			j++;
	}
	return j;
}
