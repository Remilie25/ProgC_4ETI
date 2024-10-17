/* Nom du fichier : factorielle.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : Implementer factorielle en recursif.
*/

#include <stdio.h>

unsigned int factorielle(unsigned int n){
  //Cette fonciton calcule n!.
  if (n == 0){
    printf("factorielle(0) renvoie 1\n");
    return 1;
  } else{
    unsigned int result = n * factorielle(n - 1);
    printf("factorielle(%u) renvoie %u\n", n, result);
    return result;
  }
}

int main(){
  printf("%u! = %u\n\n", 3U, factorielle(3U));
  printf("%u! = %u\n\n", 4U, factorielle(4U));
  printf("%u! = %u\n\n", 5U, factorielle(5U));
  printf("%u! = %u\n\n", 6U, factorielle(6U));
  return 0;
}
