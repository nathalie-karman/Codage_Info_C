/*
 * Définition des fonctions permettant de contrôler le cycle de vie d'un agent.
 */

#define __AGENT_LIFE_CYCLE_C__
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>

#include "agent_life_cycle.h"

/*
 * Crée l'agent pour la fonction en paramètre.
 * La fonction prend en paramètre un descripteur de fichier pour envoyer les
 * données à l'application, un descripteur de fichier pour les recevoir et ne
 * retourne rien.
 */
agent_t AgentCreate(void (*fonction)(int envoie, int reception)) {
	agent_t agent = {
		.pid = -1,
		.envoie = -1,
		.reception = -1
	};
	pid_t pid = fork();
	int vers_app[2];
	int vers_agent[2];
	if(pipe(vers_app)) {
		fprintf(stderr, "Erreur à la création d'un tube : %d\n", errno);
		return agent;
	}
	if(pipe(vers_agent)) {
		fprintf(stderr, "Erreur à la création d'un tube : %d\n", errno);
		return agent;
	}
	switch(pid) {
		case -1: /* Erreur */
			perror("Erreur à la création de l'agent.");
			return agent;
		case 0: /* Agent */
			
			/* Fermeture des descripteurs de fichiers inutiles */
			close(vers_agent[1]);
			close(vers_app[0]);
			
			/* Capture du signal Invoke */
			struct sigaction sa_invoke = {
				.sa_flags = SA_RESETHAND,
				.sa_handler = hdl_invoke
			};
			sigemptyset(&sa_invoke.sa_mask);
			sigaction(SIG_INVOKE, &sa_invoke, NULL);
			
			/* Attente du signal Invoke */
			Initiated = 1;
			while(Initiated) pause();
	
			/* Capture du signal Wait */
			struct sigaction sa_wait = {
				.sa_flags = 0,
				.sa_handler = hdl_wait
			};
			sigemptyset(&sa_wait.sa_mask);
			sigaction(SIG_WAIT, &sa_wait, NULL);
			
			/* Ignorance du signal Wake Up */
			struct sigaction sa_wake_up_ign = {
				.sa_flags = 0,
				.sa_handler = SIG_IGN
			};
			sigemptyset(&sa_wake_up_ign.sa_mask);
			sigaction(SIG_WAKE_UP, &sa_wake_up_ign, NULL);
			
			/* Exécution de la fonction */
			while(1) fonction(vers_app[1], vers_agent[0]);
			
			exit(0);
		default: /* Application */
			agent.pid = pid;
			agent.envoie = vers_agent[1];
			agent.reception = vers_app[0];
			close(vers_app[1]);
			close(vers_agent[0]);
			return agent;
	}
}

/*
 * Invocation de l'agent donné. Retourne -1 en cas d'erreur, 0 sinon.
 */
int AgentInvoke(agent_t agent) {
	return kill(agent.pid, SIG_INVOKE);
}

/*
 * Destruction de l'agent. Tue le processus. Retourne -1 en cas d'erreur, 0
 * sinon.
 */
int AgentDestroy(agent_t agent) {
	return kill(agent.pid, SIGKILL);
	close(agent.envoie);
	close(agent.reception);
}

/*
 * Demande la fin de l'agent. Retourne -1 en cas d'erreur, 0 sinon.
 */
int AgentQuit(agent_t agent) {
	return kill(agent.pid, SIGQUIT);
	close(agent.envoie);
	close(agent.reception);
}

/*
 * Suspension de l'agent. Retourne -1 en cas d'erreus, 0 sinon.
 */
int AgentSuspend(agent_t agent) {
	return kill(agent.pid, SIGSTOP);
}

/*
 * Sort l'agent de l'état suspendu. Retourne -1 en cas d'erreur, 0 sinon.
 */
int AgentResume(agent_t agent) {
	return kill(agent.pid, SIGCONT);
}

/*
 * Met l'agent en état d'attente. Retourne -1 en cas d'erreur, 0 sinon.
 */
int AgentWait(agent_t agent) {
	return kill(agent.pid, SIG_WAIT);
}

/*
 * Sort l'agent de l'état d'attente. Retourne -1 en cas d'erreur, 0 sinon.
 */
int AgentWakeUp(agent_t agent) {
	return kill(agent.pid, SIG_WAKE_UP);
}



/*
 * HANDLERS
 */



/*
 * Traitement lors de l'invocation de l'agent.
 */
void hdl_invoke(int sig) {
	Initiated = 0;
}

/*
 * Traitement lors de l'attente.
 */
void hdl_wait(int sig) {
	
	/* Capture du signal Wake Up */
	struct sigaction sa_wake_up_ign;
	struct sigaction sa_wake_up = {
		.sa_flags = SA_RESETHAND,
		.sa_handler = hdl_wake_up
	};
	sigemptyset(&sa_wake_up.sa_mask);
	sigaction(SIG_WAKE_UP, &sa_wake_up, &sa_wake_up_ign);
	
	Waiting = 1;
	while(Waiting) pause();
	
	sigaction(SIG_WAKE_UP, &sa_wake_up_ign, NULL);
}

/*
 * Traitement lors de l'arrêt de l'attente.
 */
void hdl_wake_up(int sig) {
	Waiting = 0;
}
