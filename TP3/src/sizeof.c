/* Nom du fichier : sizeof.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : comprendre les pointeurs et leur tailles en octect
 */

#include <stdio.h>

int main() {
  //Types de base
  printf("Tailles des types de base :\n\nLes entiers :\nsizeof(unsigned short) : %lu\nsizeof(short) : %lu\nsizeof(unsigned int) : %lu\nsizeof(int) : %lu\nsizeof(unsigned long) : %lu\nsizeof(long) : %lu\nsizeof(unsigned long long) : %lu\nsizeof(long long) : %lu\n\nLes nombres a virgule floattante :\nsizeof(float) : %lu\nsizeof(double) : %lu\nsizeof(long double) : %lu\n\nLes characteres :\nsizeof(unsigned char) : %lu\nsizeof(char) : %lu\n",
	 sizeof(unsigned short), sizeof(short), sizeof(unsigned int), sizeof(int), sizeof(unsigned long),
	 sizeof(long), sizeof(unsigned long long), sizeof(long long), sizeof(float), sizeof(double),
	 sizeof(long double), sizeof(unsigned char), sizeof(char));

  //Pointeurs
  printf("\n\nTailles des pointeurs :\n\nLes entiers :\nsizeof(unsigned short*) : %lu\nsizeof(short*) : %lu\nsizeof(unsigned int*) : %lu\nsizeof(int*) : %lu\nsizeof(unsigned long*) : %lu\nsizeof(long*) : %lu\nsizeof(unsigned long long*) : %lu\nsizeof(long long*) : %lu\n\nLes nombres a virgule floattante :\nsizeof(float*) : %lu\nsizeof(double*) : %lu\nsizeof(long double*) : %lu\n\nLes characteres :\nsizeof(unsigned char*) : %lu\nsizeof(char*) : %lu\n",
	 sizeof(unsigned short*), sizeof(short*), sizeof(unsigned int*), sizeof(int*), sizeof(unsigned long*),
	 sizeof(long*), sizeof(unsigned long long*), sizeof(long long*), sizeof(float*), sizeof(double*),
	 sizeof(long double*), sizeof(unsigned char*), sizeof(char*));

  //Pointeurs de pointeurs
  printf("\n\nTailles des pointeurs de pointeurs :\n\nLes entiers :\nsizeof(unsigned short**) : %lu\nsizeof(short**) : %lu\nsizeof(unsigned int**) : %lu\nsizeof(int**) : %lu\nsizeof(unsigned long**) : %lu\nsizeof(long**) : %lu\nsizeof(unsigned long long**) : %lu\nsizeof(long long**) : %lu\n\nLes nombres a virgule floattante :\nsizeof(float**) : %lu\nsizeof(double**) : %lu\nsizeof(long double**) : %lu\n\nLes characteres :\nsizeof(unsigned char**) : %lu\nsizeof(char**) : %lu\n",
	 sizeof(unsigned short**), sizeof(short**), sizeof(unsigned int**), sizeof(int**),
	 sizeof(unsigned long**), sizeof(long**), sizeof(unsigned long long**), sizeof(long long**),
	 sizeof(float**), sizeof(double**), sizeof(long double**), sizeof(unsigned char**), sizeof(char**));

  //On remarque que tous les pointeurs on la meme taille. Meme ceux avec plus d'etoiles. Ce qui est logique
  //car les adresses en memoire sont sur 8 octect pour un processeur et un OS sur 64 bits.
  
  return 0;
}
