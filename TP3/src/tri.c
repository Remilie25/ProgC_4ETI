/* Nom du fichier : tri.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : Implementer le tri rapide de tableau d'entiers.
   Voir le fichier "tri_rapide.c" pour la partie interessante du code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonction_affichage.h"
#include "init_random_tab.h"
#include "tri_rapide.h"
  

int main() {
  //Initialisation du generateur de nombres pseudo aleatoires
  srandom(time(NULL));
  
  //Initialisation du tableau d'entier
  unsigned int len = 100;
  int* int_tab = (int*) init_random_tab(len, 'i');

  //Trie et affichage
  printf("Tableau non trie :\n");
  print_int_tab(int_tab, len);

  tri_rapide(int_tab, 0, len - 1);

  printf("\nTableau trie :\n");
  print_int_tab(int_tab, len);

  printf("\n");

  free(int_tab);
  int_tab = NULL;
  
  return 0;
}
