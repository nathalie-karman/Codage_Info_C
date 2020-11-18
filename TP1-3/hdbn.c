/*
 * Fonctions de codage et de décodage HDBn.
 */

#define __HDBN_C__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "hdbn.h"
#include "rt.h"
#include "hadamard.h"

void HDBn_coder(int n,
				char * message,
				int taille_message,
				char * message_code_N,
				char * message_code_P) {
	char viol_N = +1, viol_P = -1, un_N = -1, un_P = -1;
	int i;
	
	memcpy(message_code_N, message, taille_message);
	memcpy(message_code_P, message, taille_message);
	
	for(i = 0; i <= taille_message - n; i += HDBn_coder_local(n,
		message_code_N + i, taille_message - i, &viol_N, &un_N));
	
	for(i = 0; i <= taille_message - n; i += HDBn_coder_local(n,
		message_code_P + i, taille_message - i, &viol_P, &un_P));
}

char * HDBn_decoder(int n,
					char * message_code_N,
					char * message_code_P,
					int taille_message,
					char * message) {
	char un_N = -1, un_P = -1;
	int i;
	
	char messageP[taille_message];
	memcpy(message, message_code_N, taille_message);
	memcpy(messageP, message_code_P, taille_message);
	
	for(i = 0; i <= taille_message - n; i += HDBn_decoder_local(n, message + i,
		taille_message - i, &un_N));
	for(i = 0; i <= taille_message - n; i += HDBn_decoder_local(n, messageP + i,
		taille_message - i, &un_P));
	
	for(i = 0; i < taille_message; i++)
		message[i] = message[i] || messageP[i];
	
	return message;
}

void HDBn_coder_rt(int envoie, int reception) {
	char message[RT_TAILLE_MESSAGE];
	char message_code_N[RT_TAILLE_MESSAGE];
	char message_code_P[RT_TAILLE_MESSAGE];
	
	while(1) {
		read(reception, message, RT_TAILLE_MESSAGE);
		HDBn_coder(RT_HDBN_N, message, RT_TAILLE_MESSAGE, message_code_N,
				   message_code_P);
		write(envoie, message_code_N, RT_TAILLE_MESSAGE);
		write(envoie, message_code_P, RT_TAILLE_MESSAGE);
	}
}

void HDBn_coder_rt_envoyer(agent_t agent, char * message) {
	write(agent.envoie, message, RT_TAILLE_MESSAGE);
}

void HDBn_coder_rt_recevoir(agent_t agent,
							char * message_code_N,
							char * message_code_P) {
	read(agent.reception, message_code_N, RT_TAILLE_MESSAGE);
	read(agent.reception, message_code_P, RT_TAILLE_MESSAGE);
}

void HDBn_decoder_rt(int envoie, int reception) {
	char message[RT_TAILLE_MESSAGE];
	char message_code_N[RT_TAILLE_MESSAGE];
	char message_code_P[RT_TAILLE_MESSAGE];
	
	while(1) {
		read(reception, message_code_N, RT_TAILLE_MESSAGE);
		read(reception, message_code_P, RT_TAILLE_MESSAGE);
		HDBn_decoder(RT_HDBN_N, message_code_N, message_code_P,
					 RT_TAILLE_MESSAGE, message);
		write(envoie, message, RT_TAILLE_MESSAGE);
	}
}

void HDBn_decoder_rt_envoyer(agent_t agent,
							 char * message_code_N,
							 char * message_code_P) {
	write(agent.envoie, message_code_N, RT_TAILLE_MESSAGE);
	write(agent.envoie, message_code_P, RT_TAILLE_MESSAGE);
}

char * HDBn_decoder_rt_recevoir(agent_t agent, char * message) {
	read(agent.reception, message, RT_TAILLE_MESSAGE);
	return message;
}

static int HDBn_coder_local(int n,
							char * message,
							int taille_message,
							char * viol,
							char * un) {
	if(taille_message >= n + 1 && HDBn_suite0(n, message)) {
		if(*viol > 0) {
			if(*un > 0)
				message[0] = -1;
			*viol = *un = message[n] = -1;
		} else {
			if(*un < 0)
				message[0] = +1;
			*viol = *un = message[n] = +1;
		}
		return n + 1;
	} else {
		if(message[0])
			*un = message[0] = *un * -1;
		return 1;
	}
}

static int HDBn_decoder_local(int n,
							  char * message,
							  int taille_message,
							  char * un) {
	int pol, i;
	if(taille_message >= n + 1 && (pol = HDBn_bourrage_viol(n, message))) {
		for(i = 0; i <= n; i++)
			message[i] = 0;
		*un = (char) pol;
		return n + 1;
	} else {
		if(message[0]) {
			if(message[0] == *un) {
				message[0] = 0;
			} else {
				message[0] = 1;
				*un *= -1;
			}
		}
		return 1;
	}
}

static int HDBn_suite0(int n, char * message) {
	int i;
	for(i = 0; i <= n; i++)
		if(message[i])
			return 0;
	return 1;
}

static int HDBn_bourrage_viol(int n, char * message) {
	int i, un;
	if(!(un = message[0]))
		return 0;
	for(i = 1; i < n; i++)
		if(message[i])
			return 0;
	return message[n] == un;
}
