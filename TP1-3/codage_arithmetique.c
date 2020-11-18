/*
  * Fonctions de codage et de décodage arithmétique
  * Message codé : message en entrée représenté par un nombre flottant
  */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "codage_arithmetique.h"
/*
Pour le codage arithmétique, on proposera une forme de protocole pour la transmission de la valeur sur le signal F

Le protocole se basera sur l'ordre d'appariion des lettres, et non pas l ordre alphabétique
*/

//on classera par ordre d apparition
void tableau_des_bornes(char* message,int taille_message,  double tab[]){

    int taille_tab_bornes = taille_message*2;

    double tableau_des_bornes[taille_tab_bornes];  //au minimum le double de la taille totale du message
    double deja_coche[taille_message];  //booleen qui garde en "mémoire" si une lettre a déjà été définie par ses bornes
    int i ;
    tableau_des_bornes[0];

    for (i =0 ; message[i]; i++){

        for (int j = 0; i < message[j]; j++) {

        }
    }


}

 // on va renvoyer un tableau de int car problème avec
void calcul_occurrence(char* message,int taille_message,  double tab[], char tableau_des_occurrences[]){


    int k=0;
    for (int i = 0 ; message[i]; i++){

      tab[i] = 0.0;

      for(int j = 0 ; j <taille_message ;j++){

          if(char c= strchr(message,message[i])){

            tab[toupper(c)-'A'] +=  1.0;  //on met à jour la table de l alhabet

            if(tab[i] == 1.0){  //on met à jour la table de l alphabet de la chaine
              tableau_des_occurrences[k]=toupper(message[i]);
              k++;
            }
          }

      }
    }

    for (int i=0; i <taille_message; i++){

        tab[i]=tab[i]/(double)taille_message;  //rapport de l apparition sur la totalité du msg
    }

    *taille_alphabet = k;

}
void afficher_alphabet_du_message(char* message, char alphabet_chaine,){

}
void encoder_arithmetique(char* message,int taille_message,double tableau_proportions[]){

      int alphabet_chaine=0;  //variable qui sera initialisée dans la fonction "calcul_occurrence"
      char tableau_des_occurrences[27]; //tableau qui contiendra l alphabet de la chaîne
      printf("%s la taille du msg %d \n",message , taille_message);

      calcul_occurrence(message,taille_message,tableau_proportions, tableau_des_occurrences,&alphabet_chaine);

      for (int i=0; i < taille_alphabet; i++){

          printf("lettre %c la taille du msg %f \n",tableau_des_occurrences[i],tableau_proportions[i]);

      }


}

/***********/

int main(){
        int taille= strlen("Vacances");
        char* msg=malloc(sizeof(char)*taille);
        strcpy(msg,"Vacances");
        double tab[taille];        //tableau de double pour double précision sur les floats
                                                                                        //(opérations sur floats simples ingérables surtout si c est par ordre d'apparition)

        encoder_arithmetique(msg,taille,tab);
        free(msg);
//        printf("message codé %f\n",msg_codey );
        return 0;
} 
