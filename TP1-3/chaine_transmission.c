/*
 * Modélisation d'une chaîne de transmission.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "agent_life_cycle.h"
#include "etalement.h"
#include "desetalement.h"
#include "hdbn.h"
#include "message.h"
#include "rt.h"

int main() {
	
	int i;
	
	/* Création des threads */
	agent_t ag_etalement = AgentCreate(etaler_rt);
	agent_t ag_desetalement = AgentCreate(desetaler_rt);
	agent_t ag_hdbn_coder = AgentCreate(HDBn_coder_rt);
	agent_t ag_hdbn_decoder = AgentCreate(HDBn_decoder_rt);
	
	/**************************************************************************
	 *                               ETALEMENT                                *
	 **************************************************************************/
	
	/* Messages à envoyer */
	char m1[] = {+1, -1, +1, +1, -1, +1, +1, +1};
	char m2[] = {-1, -1, +1, +1, -1, -1, +1, +1};
	char m3[] = {-1, +1, +1, -1, +1, +1, -1, -1};
	char m4[] = {+1, +1, -1, -1, -1, -1, +1, +1};
	char * messages[] = {m1, m2, m3, m4};
	int nb_messages = 4;
	
	printf("\n***** ETALEMENT *****\n\n");
	printf("Messages à envoyer :\n");
	for(i = 0; i < nb_messages; i++) {
		afficher_message(messages[i], RT_TAILLE_MESSAGE);
		printf("\n");
	}
	
	/* Invocation de l'agent d'étalement */
	assert(!AgentInvoke(ag_etalement));
	
	/* Envoie des messages */
	etaler_rt_envoyer(ag_etalement, nb_messages, messages);
	
	char etalement[RT_TAILLE_MESSAGE];
	
	/* Réception de l'étalement */
	etaler_rt_recevoir(ag_etalement, etalement);
	
	printf("\nÉtalement :\n");
	afficher_etalement(etalement, RT_TAILLE_MESSAGE, RT_NB_UTILISATEURS);
	printf("\n");
	
	/* Arrêt de l'agent */
	assert(!AgentQuit(ag_etalement));
	
	/**************************************************************************
	 *                              DESETALEMENT                              *
	 **************************************************************************/
	
	/* Invocation de l'agent */
	assert(!AgentInvoke(ag_desetalement));
	
	/* Envoie de l'étalement */
	desetaler_rt_envoyer(ag_desetalement, etalement);
	
	/* Tableau des messages reçus */
	char * messages_recus[RT_NB_UTILISATEURS];
	for(i = 0; i < RT_NB_UTILISATEURS; i++)
		messages_recus[i] = malloc(RT_TAILLE_MESSAGE);
	
	/* Réception des messages */
	desetaler_rt_recevoir(ag_desetalement, messages_recus);
	
	printf("\n***** DESETALEMENT *****\n\n");
	printf("Messages reçus :\n");
	for(i = 0; i < RT_NB_UTILISATEURS; i++) {
		afficher_message(messages[i], RT_NB_UTILISATEURS);
		printf("\n");
	}
	
	/* Arrêt de l'agent */
	assert(!AgentQuit(ag_desetalement));
	
	return 0;
}
