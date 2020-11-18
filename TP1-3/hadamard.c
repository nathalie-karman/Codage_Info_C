#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

#include "hadamard.h"

#define BINAIRE 2

//calcul des étapes à effectuer
static int calcul_etapes(int nb_utilisateurs){  //N = 2^p

  int nb_etape=0;
  int n=0;

  while(n < nb_utilisateurs){
      n = pow(BINAIRE,nb_etape++);
  }
  return n;
}

void detruire_matrice(int taille,char** matrice_Hadamard){

  for (int i = 0; i < taille; i++)
      free(matrice_Hadamard[i]);

  free(matrice_Hadamard);

}
void afficher_matrice(int taille,char** matrice_Hadamard){
    printf("affichage de la matrice Hadamard\n\n");
    for(int i=0; i< taille;i++){

      for (int j=0; j < taille; j++) {
          if(matrice_Hadamard[i][j]==-1)
            printf(" %d  ",matrice_Hadamard[i][j]);
          else
            printf("  %d  ",matrice_Hadamard[i][j]);
      }
        printf("\n" );
    }


}

void copier_matrice(int x, int y, char** matrice, char** matrice_finale, int n){
    int i,j;
  //  printf("%d\n",matrice_finale[i][j] );
    int indice_x=x, indice_y=y;

    for ( i=0; i < n; i++){

        for ( j=0; j < n ; j++){

              matrice_finale[indice_x][indice_y] = matrice[i][j];

              indice_y++;

        }
        indice_y=y;
        indice_x++;

    }
}

char** inverser_matrice(char ** mat_a_inverser, int taille, char** matrice_sortie){

    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {

          matrice_sortie[i][j] = mat_a_inverser[i][j]* (-1);
        }
    }
    return matrice_sortie;
}

char** generer_hadamard(int nb_utilisateurs, int * taille_matrice_generee){

  int n =calcul_etapes(nb_utilisateurs);  // matrice de nb_utilisateurs x nb_utilisateurs
  int n_initial=1;
  *taille_matrice_generee=n;
  //matrices utilisées dans le programme
  char** Ho = malloc(sizeof(*Ho)* n);
  char** petite_matrice=malloc(sizeof(*Ho));  //matrice initiale
  char ** matrice_temp=malloc(sizeof(*matrice_temp)*n); //


  //allocation des lignes des matrices
  petite_matrice[0]=malloc(sizeof(*Ho));
  petite_matrice[0][0]=1;
  for(int i=0; i< n ;i++)
     Ho[i] = malloc( sizeof(char) * n );
  for(int i=0; i< n ;i++)
    matrice_temp[i] = malloc( sizeof(char) * n );
  //faire une boucle jusqu à atteindre le N
    copier_matrice(0, 0,petite_matrice, Ho,n_initial);    //crée la matrice de base 2x2
    while (n_initial < n) {

        copier_matrice(n_initial, 0,Ho, Ho,n_initial);
        copier_matrice(0, n_initial,Ho, Ho,n_initial);
        inverser_matrice(Ho, n_initial, matrice_temp);
        copier_matrice(n_initial, n_initial,matrice_temp, Ho,n_initial);
        n_initial*=2;
    }

    detruire_matrice(1,petite_matrice);
    detruire_matrice(n,matrice_temp);
    return Ho;


}
