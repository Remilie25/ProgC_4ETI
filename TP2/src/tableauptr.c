/* Nom du fichier : tableauptr.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : creer deux tableaux aleatoirement, un d'entier et l'autre de float, et multiplie par 3 les elements d'indice pair. Les operations doivent etre fait avec des pointers.
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "fonction_affichage.h"

float float_from_long_bytes(long k){
  //Cette fonction renvoie le float ayant les memes premiers octects que l'entier k.
  union float_from_long{
    long integer;
    float real_number;
  };
  union float_from_long tmp;
  tmp.integer = k;
  return tmp.real_number;
}


int main(){
  //Initialisation du PRNG
  srandom(time(NULL));

  //Definition des tableaux et de la fonction d'affichage
  int int_tab[25];
  float float_tab[25];

  void print_etat(char* moment){
    //Cette fonction affiche l'etat des tableaux
    printf("Tableaux %s modifications :\n int_tab :\n", moment);
    print_int_tab(int_tab, sizeof(int_tab) / sizeof(*int_tab));
    printf("\n\nfloat_tab :\n");
    print_float_tab(float_tab, sizeof(float_tab) / sizeof(*float_tab));
    printf("\n\n");
  }

  //Initialisation des tableaux
  short indice = 0;

  for(; indice < 25; indice++){
    *(int_tab + indice) = (int) random();
    *(float_tab + indice) = float_from_long_bytes(random());
  }

  //Affichage avant modif
  print_etat("avant");
  
  //Traitement : multiplication par 3 si indice % 2 == 0
  for(indice = 0; indice < 25; indice += 2){
    *(int_tab + indice) *=3;
    *(float_tab + indice) *= 3;
  }

  //Affichage apres modif
  print_etat("apres");
  
  return 0;
}
