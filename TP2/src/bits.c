/* Nom du fichier : bits.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : Verifier que le 4e et 2e bit de gauche d'un entier soit a un. A priori si l'on verifie le 20e bit de gauche cela implique que le processeur doit avoir sizeof(int) >= 3 (20 < 24 = 3 * 8),  
 */

#include <stdio.h>

int main(){
  int mask = 0b1;

  //d qui ne marche pas pour sizeof(int) = 4
  //int d = 0b00000000000000000001000000000000;
  //int d = 0b00010000000000000000000000000000;

  //d qui marche pour sizeof(int) = 4
  int d = 0b00010000000000000001000000000000;

  //verification du 4e et 20e bit en partant de la gauche
  d >>= (sizeof(int) * 8 - 20);
  if (!(d & mask)){
    printf("%d\n",0);
    return 0;
  }

  d >>= 16;

  printf("%d\n", (d & mask));
  return 0;
}
