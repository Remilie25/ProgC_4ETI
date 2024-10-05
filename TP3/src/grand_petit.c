/* Nom du fichier : grand_petit.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : Trouver le plus grand et plus petit element d'un tableau d'entiers.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "init_random_tab.h"

int min(int* tab_ptr, unsigned int len){
  //Cette fonciton retourne l'entier minimal d'un tableau donne par le pointeur tab_ptr.
  int min_temp = tab_ptr[0];
  unsigned int indice = 1;

  for(; indice < len; indice++){
    if (min_temp > tab_ptr[indice]){
      min_temp = tab_ptr[indice];
    }
  }
  return min_temp;
}

int max(int* tab_ptr, unsigned int len){
  //Cette fonciton retourne l'entier maximal d'un tableau donne par le pointeur tab_ptr.
  int max_temp = tab_ptr[0];
  unsigned int indice = 1;

  for(; indice < len; indice++){
    if (max_temp < tab_ptr[indice]){
      max_temp = tab_ptr[indice];
    }
  }
  return max_temp;
}

int main() {
  //Initialisation du generateur de nombres pseudo aleatoires
  srandom(time(NULL));
  
  //Initialisation du tableau d'entier
  unsigned int len = 100;
  int* int_tab = init_random_tab(len, 'i');

  printf("L'entier le plus grand est : %d\nL'entier le plus petit est : %d\n", max(int_tab, len), min(int_tab, len));

  free(int_tab);
  int_tab = NULL;
  
  return 0;
}
