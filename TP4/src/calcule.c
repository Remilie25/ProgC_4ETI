/* Nom du fichier : calcule.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : faire une calculatrice en ligne de commande
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "operator.h"

int main(int argc, char** argv){
  if (argc < 3 || argc > 4){
    printf("Trop peu ou trop d'arguments donnes. Veuillez donner un operateur parmis (+, -, *, /, %%, &, |, ~) et un ou deux operands.\n");
    return 1;
  }else{
    int num1, num2;

    //Recuperation des valeurs
    if (1 != sscanf(argv[2], "%d", &num1)){
      printf("num1 doit etre de type int !\n");
      return 1;
    }
    if (argv[1][0] != '~'){
      if (1 != sscanf(argv[3], "%d", &num2)){
	printf("num2 doit etre de type int !\n");
	return 1;
      }
    }

    //Realisation de l'operation
    printf("%d %c %d\n", num1, *argv[1], num2);
    faire_operation(&num1, argv[1], &num2);
    printf("Resultat : %d\n", num1);
    return 0;
  }
}
