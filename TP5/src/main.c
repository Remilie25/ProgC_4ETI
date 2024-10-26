/* Nom du fichier : main.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif :
     1. afficher le contenu d'un dossier.
*/

#include <stdio.h>
#include "repertoire.h"

int main(int argc, char** argv){

  if (argc < 2) {
    printf("Un numero d'algorithme est necessaire.\n1. ls\n2. ls -R version recursive\n3. ls -R verion iterative.\nEx : %s <num> <nom_du_repertoire>\n", argv[0]);
    return 1;
  }
  
  switch (argv[1][0]){//Seul le premier charactere nous interesse.
  case '1':
    
    //Exercice 1
    if (argc < 3) {
      printf("Un chemin vers un dossier est necessaire. (Ex : %s 1 <nom_du_repertoire>)\n", argv[0]);
      return 1;
    }
    lire_dossier(argv[2]);
    break;

  case '2':

    //Exercice 2
    if (argc < 3) {
      printf("Un chemin vers un dossier est necessaire. (Ex : %s 2 <nom_du_repertoire>)\n", argv[0]);
      return 1;
    }
    lire_dossier_recursif(argv[2]);
    break;

  case '3':

    //Exercice 3
    if (argc < 3) {
      printf("Un chemin vers un dossier est necessaire. (Ex : %s 3 <nom_du_repertoire>)\n", argv[0]);
      return 1;
    }
    lire_dossier_iteratif(argv[2]);
    break;

  }
  return 0;
}
