#ifndef _HADAMARD_H_
#define _HADAMARD_H_



/*

 */
 /*
  * Cette fonction désalloue tout l'espace mémoire alloué
  */
void detruire_matrice(int ,char** );
/*
 * Affichage de la matrice générée
 */
void afficher_matrice(int,char** );
/*
 * Recopie une matrice de taille X[x,x] dans une matrice de taille supérieure Y[y,y]
 * On recopie toujours l'inverse de la matrice [x,x] dans la 4è partie de la matrice Y en bas, à droite
 *
 */
void copier_matrice(int , int, char** , char**, int );
/*
 * Fonction qui permet d'inverser une matrice A passée en paramètre
 * et de remplir une matrice B contenant l'inverse
 */
char** inverser_matrice(char ** , int , char** );
/*
 * Génère la matrice de hadamard en accord avec le nombre d'utilisateur en paramètre
 * Commence par calculer le nombre d'étapes p à effectuer "n"
 * Crée 2 matrices de la taille finale attendue [nxn] et la matrice initiale qui contient "1", le premier bit
 *
 * On part de la matrice initiale de taille 1 jusqu à obtenir la matrice finale de Hadamard
 */
char** generer_hadamard(int, int* );

#endif
