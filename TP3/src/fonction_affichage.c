/* Nom du fichier : fonciton_affichage.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : Afficher un tableau d'entier ou de floattant.
 */

#include <stdio.h>

void print_int_tab(int* tab_ptr, unsigned int len){
  //Cette fonction affiche un tableau d'entier.
  unsigned int indice = 1;
  printf("%d", *tab_ptr);
  for(; indice < len; indice++){
    printf(", %d", *(tab_ptr + indice));
  }
}

void print_float_tab(float* tab_ptr, unsigned int len){
  //Cette fonction affiche un tableau de float.
  unsigned int indice = 1;
  printf("%f", *tab_ptr);
  for(; indice < len; indice++){
    printf(", %f", *(tab_ptr + indice));
  }
}
