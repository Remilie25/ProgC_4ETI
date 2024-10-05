/* Nom du fichier : variables.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : creer et afficher une variable de chaque type de base.
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

  printf("unsigned short: %hu\n", a);
  printf("short: %hd\n", b);
  printf("unsigned int: %u\n", c);
  printf("int: %d\n", d);
  printf("unsigned long int: %lu\n", e);
  printf("long int: %ld\n", f);
  printf("unsigned long long int: %llu\n", g);
  printf("long long int: %lld\n", h);
  printf("float: %f\n", i);
  printf("double: %g\n", j);
  printf("long double: %Lg\n", k);  
  printf("unsigned char: %hhu\n", l);
  printf("char: %c\n", m);

  return 0;    
}
