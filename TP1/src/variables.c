/* Nom du fichier : variables.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : creer et affiche une variable de chaque type de base.
 */

#include <stdio.h>


int main() {
  unsigned short a = 1;
  short b = -2;
  unsigned int c = 3;
  int d = -4;
  unsigned long e = 5ul;
  long f = 0xfffffl;
  unsigned long long g = 7ull;
  long long h = 0x12345678;
  float i = 8.0;
  double j = 9E0;
  long double k = 1E1;
  unsigned char l = 'a';
  char m = 'b';
  printf(" a = %hu\n b = %hd\n c = %u\n d = %d\n e = %lu\n f = %ld\n g = %llu\n h = %lld\n i = %f\n j = %g\n k = %Lg\n l = %hhu\n m = %c\n", a, b, c, d, e, f, g, h, i, j, k, l, m);
}
