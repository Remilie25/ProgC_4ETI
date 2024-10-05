/* Nom du fichier : opérateurs.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : effectuer toutes les operations de base sur les entiers.
 */

#include <stdio.h>


int main() {
  int a = 16;
  int b = 3;
  printf("addition : %d\nsoustraction : %d\nmultiplier : %d\ndiviser : %d\nmodulo : %d\ncomparaison : %d\nsuperieur : %d\n", 
   a+b, a-b, a*b, a/b, a%b, a==b, a>b);
}
