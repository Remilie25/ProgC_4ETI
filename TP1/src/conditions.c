/* Nom du fichier : conditions.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : Faire la somme des nombres divisibles par 5 et 7 mais pas 11 pour les nombres de 1 a 1000.
              Si la somme depasse 5000, on s'arrete.
 */

#include <stdio.h>


int main(){
  int nombre = 1;
  int somme = 0;
  for (;nombre < 1001; nombre++){
    if ( (!(nombre % 5) || !(nombre % 7)) && nombre % 11){
      somme += nombre;
    } else if (!(nombre & 11)){
      continue;
    }
    if (somme > 5000){
      break;
    }
  }
  printf("La somme vaut : %d\n", somme);
  return 0;
}
