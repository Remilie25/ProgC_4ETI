/* Nom du fichier : octets.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : parcourir les types de base octet par octet
 */

#include <stdio.h>

void print_byte(void* data_ptr, unsigned long size){
  //Affiche size octets en partant de data_ptr.
  char* byte_ptr = (char*) data_ptr;
  for (unsigned long indice = 0; indice < size; indice++){
    printf(" %hhx", *(byte_ptr + indice));
  }
}

int main() {
  //Definition d'une variable de chaque type 
  unsigned short a = 25;
  short b = -20;
  unsigned int c = 30;
  int d = -40;
  unsigned long e = 50ul;
  long f = 0xfffffl;
  unsigned long long g = 70ull;
  long long h = 0x12345678;
  float i = 80.08164;
  double j = 9E1;
  long double k = 1E10;
  unsigned char l = 'a';
  char m = 'b';

  //Affichage. Pour mon ordinateur et mon os, j'ai obtenu little endian comme annoce en cours.
  printf("Octects de unsigned short :\n");
  print_byte(&a, sizeof(a));

  printf("\n\nOctects de short :\n");
  print_byte(&b, sizeof(b));

  printf("\n\nOctects de unsigned int :\n");
  print_byte(&c, sizeof(c));

  printf("\n\nOctects de int :\n");
  print_byte(&d, sizeof(d));

  printf("\n\nOctects de unsigned long :\n");
  print_byte(&e, sizeof(e));

  printf("\n\nOctects de long :\n");
  print_byte(&f, sizeof(f));

  printf("\n\nOctects de unsigned long long :\n");
  print_byte(&g, sizeof(g));

  printf("\n\nOctects de long long :\n");
  print_byte(&h, sizeof(h));

  printf("\n\nOctects de float :\n");
  print_byte(&i, sizeof(i));

  printf("\n\nOctects de double :\n");
  print_byte(&j, sizeof(j));

  printf("\n\nOctects de long double :\n");
  print_byte(&k, sizeof(k));

  printf("\n\nOctects de unsigned char :\n");
  print_byte(&l, sizeof(l));

  printf("\n\nOctects de char :\n");
  print_byte(&m, sizeof(m));
  printf("\n");
  
  return 0;
}
