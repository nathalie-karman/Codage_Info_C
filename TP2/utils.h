/*
 * Utilitaires pour les différents modules.
 */

#ifndef __UTILS_H__
#define __UTILS_H__



/*
 * Ou exclusif booléen.
 */
#define xor(a, b) (!((a) == (b)))



/*
 * Retourne le résultat de 2^n
 */
int puis2(int n);



/*
 * Effectue une opération xor sur chaqun des éléments de t1 et t2 de taille
 * longueur et écrit le résultat dans dest de taille longueur.
 */
char * tab_xor(char * dest, char * t1, char * t2, int longueur);



#endif // __UTILS_H__
