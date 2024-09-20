/* Nom du fichier : cercle.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : calculer le perimetre et l'aire d'un cercle.
 */

#include <stdio.h>
#include <math.h>

int main() {
  float rayon = 10;
  printf("Périmetre du cercle %f\nAire du cercle %f\n", M_PI * rayon * 2, M_PI * rayon * rayon);
  return 0;
}
