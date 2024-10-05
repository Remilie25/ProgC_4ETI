/* Nom du fichier : init_random_tab.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : Initialiser des tableaux de nombres aleatoires.
 */

#include <stdlib.h>

void* init_random_tab(unsigned int len, char type){
  /*Cette fonction renvoie une adresse non typee pointant un tableau de "len" element de type "type".
    Si type = 'i' => les int sont de 0 a 1000 inclu.*/

  if (type == 'd' || type == 'i'){
    int* tab = (int*) malloc(sizeof(int) * len); //Allocation memoire pour le tableau.
    for(unsigned int indice = 0; indice < len; indice++){
      tab[indice] = ((int) random()) % 1001; //Pour generer un entier aleatoire entre 0 et 1000 inclu
    }
    return (void*) tab;
  }
  else if (type == 'f'){
    float* tab = (float*) malloc(sizeof(float) * len); //Allocation memoire pour le tableau.
    //To do
    return (void*) tab;
  }
  else{
    return NULL;
  }
}
