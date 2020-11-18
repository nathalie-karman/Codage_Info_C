/*
 * Fonctions de codage et décodage HDBn.
 */

#ifndef __HDBN_H__
#define __HDBN_H__

#include "agent_life_cycle.h"



/*
 * Code le message en utilisant le code HDBn.
 * n : nombre de symboles 0 autorisés à la suite
 * message : message à coder. Tableau d'entiers (char) à 0 ou 1.
 * taille_message : taille du message à coder
 * message_code_N : message codé, pulse +1
 * message_code_P : message codé, pulse -1
 * Les espaces mémoires de message_code_* doivent être réservés, de tailles
 * taille_message.
 */
void HDBn_coder(int n,
				char * message,
				int taille_message,
				char * message_code_N,
				char * message_code_P);


/*
 * Décode les messages codés en utilisant le code HDBn.
 * n : nombre de symboles 0 autorisés à la suite.
 * message_code_N : message codé, pulse +1
 * message_code_P : message codé, pulse -1
 * taille_message : taille du message
 * message : message décodé
 * L'espace mémoire de message doit être réservé, de taille taille_message.
 */
char * HDBn_decoder(int n,
					char * message_code_N,
					char * message_code_P,
					int taille_message,
					char * message);



/*
 * Fonction de codage temps réel. N est défini par RT_HDBN_N.
 */
void HDBn_coder_rt(int envoie, int reception);



/*
 * Envoie le message de taille RT_TAILLE_MESSAGE à coder à l'agent.
 */
void HDBn_coder_rt_envoyer(agent_t agent, char * message);



/*
 * Reçoit le message codé de taille RT_TAILLE_MESSAGE dans message_code_N et
 * message_code_P (l'espace mémoire doit être réservé).
 */
void HDBn_coder_rt_recevoir(agent_t agent,
							char * message_code_N,
							char * message_code_P);



/*
 * Fonction de décodage temps réel. N est défini par RT_HDBN_N.
 */
void HDBn_decoder_rt(int envoie, int reception);



/*
 * Envoie le message codé de taille RT_TAILLE_MESSAGE à décoder à l'agent.
 */
void HDBn_decoder_rt_envoyer(agent_t agent,
							 char * message_code_N,
							 char * message_code_P);



/*
 * Reçoit le message codé de taille RT_TAILLE_MESSAGE dans message (l'espace
 * mémoire doit être réservé).
 */
char * HDBn_decoder_rt_recevoir(agent_t agent, char * message);


#ifdef __HDBN_C__



/*
 * Code HDBn sur les premiers symboles du message.
 * viol : dernier viol
 * un : dernier +/- 1
 * taille_message : taille du message à partir du pointeur message
 * Retourne le nombre de symboles évalués.
 */
static int HDBn_coder_local(int n,
							char * message,
							int taille_message,
							char * viol,
							char * un);



/*
 * Décode HDBn sur les premiers symboles du message codé.
 * un : dernier +/- 1
 * taille_message : taille du message à partir du pointeur message
 * Retourne le nombre de symboles évalués.
 */
static int HDBn_decoder_local(int n,
							  char * message,
							  int taille_message,
							  char * un);



/* Teste si message de taille n + 1 contient une suite de 0 */
static int HDBn_suite0(int n, char * message);

/*
 * Teste si un message de taille n + 1 est de la forme +1 0 .. 0 +1 ou
 * -1 0 .. 0 -1. Retourne +1 ou -1 selon la polarité des symboles.
 */
static int HDBn_bourrage_viol(int n, char * message);



#endif // __HDBN_C__



#endif // __HDBN_H__
