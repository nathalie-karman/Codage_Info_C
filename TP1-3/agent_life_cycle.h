/*
 * Déclaration des fonctions permettant de contrôler le cycle de vie d'un agent.
 */

#ifndef __AGENT_LIFE_CYCLE_H__
#define __AGENT_LIFE_CYCLE_H__

#include <signal.h>



/*
 * MACROS
 */



#define	SIG_INVOKE	SIGRTMIN + 0
#define	SIG_WAIT	SIGRTMIN + 1
#define	SIG_WAKE_UP	SIGRTMIN + 2



/*
 * TYPES
 */



/*
 * Structure représentant un agent contenant le PID de son processus et les
 * descripteurs de fichier d'envoie et de réception de messages.
 */
typedef struct {
	pid_t pid;
	int envoie;
	int reception;
} agent_t;



/*
 * VARIABLES LOCALES
 */

#ifdef __AGENT_LIFE_CYCLE_C__

/*
 * État d'attente du processus
 */
int Waiting;

/*
 * État où le processus est crée mais pas encore invoqué.
 */
int Initiated;

#endif // __AGENT_LIFE_CYCLE_C__


/*
 * TRANSITIONS DE L'AGENT
 */



/*
 * Crée l'agent pour la fonction en paramètre.
 * La fonction prend en paramètre un descripteur de fichier pour envoyer les
 * données à l'application, un descripteur de fichier pour les recevoir et ne
 * retourne rien.
 */
agent_t AgentCreate(void (*fonction)(int envoie, int reception));

/*
 * Invocation de l'agent donné. Retourne -1 en cas d'erreur, 0 sinon.
 */
int AgentInvoke(agent_t agent);

/*
 * Destruction de l'agent. Tue le processus. Retourne -1 en cas d'erreur, 0
 * sinon.
 */
int AgentDestroy(agent_t agent);

/*
 * Demande la fin de l'agent. Retourne -1 en cas d'erreur, 0 sinon.
 */
int AgentQuit(agent_t agent);

/*
 * Suspension de l'agent. Retourne -1 en cas d'erreus, 0 sinon.
 */
int AgentSuspend(agent_t agent);

/*
 * Sort l'agent de l'état suspendu. Retourne -1 en cas d'erreur, 0 sinon.
 */
int AgentResume(agent_t agent);

/*
 * Met l'agent en état d'attente. Retourne -1 en cas d'erreur, 0 sinon.
 */
int AgentWait(agent_t agent);

/*
 * Sort l'agent de l'état d'attente. Retourne -1 en cas d'erreur, 0 sinon.
 */
int AgentWakeUp(agent_t agent);



/*
 * HANDLERS
 */

#ifdef __AGENT_LIFE_CYCLE_C__

/*
 * Traitement lors de l'invocation de l'agent.
 */
void hdl_invoke(int sig);

/*
 * Traitement lors de l'attente.
 */
void hdl_wait(int sig);

/*
 * Traitement lors de l'arrêt de l'attente.
 */
void hdl_wake_up(int sig);



#endif // __AGENT_LIFE_CYCLE_C__



#endif // __AGENT_LIFE_CYCLE_H__
