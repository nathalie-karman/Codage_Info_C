#ifndef _CODAGE_ARITHMETIQUE_H
#define _CODAGE_ARITHMETIQUE_H


/*
* Principe du codeur arithmétique
* L'utilisateur pourrait choisir si il veut coder par ordre d'apparition ou ordre alphabétique
* Message entrée : une chaîne de caractères
* Message sortie : représentationd et la chaîne en un nombre flottant
* Taille message : taille du message à coder
* Calcul Occurrence : tableau de flottant (hachage?) qui découle des statistiques d'apparition de la lettre dans le messager à coder
* Borne inférieure : flottant qui définit le début de la sous chaîne jusqu à la fin du message codé (i.e. début de la chaîne avec "B" aura une borne_inf= 0,2, "BI" borne_inf= )
* Borne supérieure : flottant qui définit la fin de la sous chaîne jusqu à la fin du message codé
*/
void encoder_arithmetique(char* ,int , double tab[]);




#endif // _CODAGE_ARITHMETIQUE_H  
