/* Nom du fichier : pyramide.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : affichage d'une pyramide. Chaque ligne croit de 1 a 
 */

#include <stdio.h>


int main(){
  int n = 9; //hauteur de la pyramide.
  int i = 1;
  int j = 1;

  for (;i <= n; i++){
    for (j = 0; j < n - i; j++){//espace pour centrer
      printf(" ");
    }
    for (j = 1; j <= i; j++){//demi etage ou les nombres croient
      printf("%d",j);
    }
    for (j = i - 1; j > 0; j--){//demi etage ou les nombres decroient
      printf("%d",j);
    }
    printf("\n");
  } 
  return 0;
}
