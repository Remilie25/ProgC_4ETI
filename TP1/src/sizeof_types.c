/* Nom du fichier : sizeof_types.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : affichage de la taille en octects de chaque type de base.
 */

#include <stdio.h>


int main() {
  printf("Tailles des types de base :\n\nLes entiers :\nsizeof(unsigned short) : %lu\nsizeof(short) : %lu\nsizeof(unsigned int) : %lu\nsizeof(int) : %lu\nsizeof(unsigned long) : %lu\nsizeof(long) : %lu\nsizeof(unsigned long long) : %lu\nsizeof(long long) : %lu\n\n",
	 sizeof(unsigned short), sizeof(short), sizeof(unsigned int), sizeof(int), sizeof(unsigned long),
	 sizeof(long), sizeof(unsigned long long), sizeof(long long));
  printf("Les nombres a virgule floattante :\nsizeof(float) : %lu\nsizeof(double) : %lu\nsizeof(long double) : %lu\n\n", 
   sizeof(float), sizeof(double),sizeof(long double));
  printf("Les characteres :\nsizeof(unsigned char) : %lu\nsizeof(char) : %lu\n", 
   sizeof(unsigned char), sizeof(char));
  return 0;
}
