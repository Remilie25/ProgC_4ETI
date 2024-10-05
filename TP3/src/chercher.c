/* Nom du fichier : chercher.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : Renvoyer l'appartenance d'un element a une liste.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonction_affichage.h"
#include "init_random_tab.h"

int main() {
  //Initialisation du generateur de nombres pseudo aleatoires
  srandom(time(NULL));
  
  //Initialisation du tableau d'entier
  unsigned int len = 100;
  int* int_tab = (int*) init_random_tab(len, 'i');

  printf("Tableau :\n");
  print_int_tab(int_tab, len);
  
  /*Recupere un entier rentre par l'utilisateur en evitant des debordements.
    sizeof(int) * 4 * 3/ 10 + 4 est superieure au nombre de carateres maximal pour un nombre representable par int.*/
  printf("\n\nEntrez le nombre a chercher (nombre sur un int) : ");
  char num_str[(sizeof(int) * 4 * 3 / 10 ) + 4];
  int num_cherche;//nbr a chercher
  fgets(num_str, sizeof(num_str), stdin);
  sscanf(num_str, "%d", &num_cherche);
  
  //Recherche
  unsigned char found = 0; //booleen : nul => element pas trouve; sinon trouve.
  
  for (unsigned int indice = 0; indice < len; indice++){
    if (int_tab[indice] == num_cherche){
      found = 1;
      printf("Resultat : entier present\n");
    }
  }
  if (!found){
    printf("Resultat : entier absent\n");
  }

  free(int_tab);
  int_tab = NULL;
  
  return 0;
}
