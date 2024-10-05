/* Nom du fichier : recherche_dichotomique.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : Renvoyer l'appartenance d'un element a une liste triee par recherche dichotomique.
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

  tri_rapide(int_tab, 0, len - 1);
  
  printf("Tableau trie :\n");
  print_int_tab(int_tab, len);
  
  /*Recupere un entier rentre par l'utilisateur en evitant des debordements.
    sizeof(int) * 4 * 3/ 10 + 4 est superieure au nombre de carateres maximal pour un nombre representable par int.*/
  printf("\n\nEntrez le nombre a chercher (nombre sur un int) : ");
  char num_str[(sizeof(int) * 4 * 3 / 10 ) + 4];
  int num_cherche;
  fgets(num_str, sizeof(num_str), stdin);
  sscanf(num_str, "%d", &num_cherche);
  
  //Recherche dichotomique, si l'entier est present sont indice appartient a [borne_min, borne_max[.
  unsigned int borne_min = 0;
  unsigned int borne_max = len;
  unsigned int milieu;

  while (borne_max - borne_min > 1){
    milieu = (borne_max + borne_min) / 2;
    if (int_tab[milieu] < num_cherche){
      //Le nbr cherche est strictement plus grand et plus besoin de traiter l'element d'indice milieu
      borne_min = milieu + 1; 
    }
    else if (int_tab[milieu] == num_cherche){ //Trouve sortons de la boucle.
      borne_min = milieu;
      borne_max = milieu + 1;
    }
    else{ //Le nbr cherche est strictement plus petit et plus besoin de traiter l'element d'indice milieu
      borne_max = milieu;
    }
  }

  if (int_tab[borne_min] == num_cherche){
    printf("Resultat : entier present\n");
  }
  else{
    printf("Resultat : entier absent\n");
  }

  free(int_tab);
  int_tab = NULL;
  
  return 0;
}
