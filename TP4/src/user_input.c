/* Nom du fichier : user_input.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : Recuperer la reponse de l'utilisateur.
 */

#include <stdio.h>

int int_input(){
  /*Recupere un entier rentre par l'utilisateur en evitant des debordements.
    sizeof(int) * 4 * 3/ 10 + 4 est superieure au nombre de carateres maximal pour un nombre representable
    par int.*/
  char num_str[(sizeof(int) * 4 * 3 / 10 ) + 4];
  int num_ecrit;
  fgets(num_str, sizeof(num_str), stdin);
  sscanf(num_str, "%d", &num_ecrit);

  return num_ecrit;
}

unsigned long unsigned_long_input(){
  /*Recupere un long entier non signe rentre par l'utilisateur en evitant des debordements.
    sizeof(unsigned long) * 4 * 3/ 10 + 4 est superieure au nombre de carateres maximal pour un nombre
    representable par int.*/
  char num_str[(sizeof(unsigned long) * 4 * 3 / 10 ) + 4];
  unsigned long num_ecrit;
  fgets(num_str, sizeof(num_str), stdin);
  sscanf(num_str, "%lu", &num_ecrit);

  return num_ecrit;
}
