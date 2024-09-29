/* Nom du fichier : puissance.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : Calcul a a la puissance b et l'affiche. a, b et le resultat sont des int.
 */

#include <stdio.h>

int puissance(int a, int b){
  /*Cette fonciton calcule a a la puissance b sur un int.*/
  int resultat = 1;
  for (;b > 0; b--){
    resultat *= a; 
  }
  return resultat;
}

int main(){
  int a = 2;
  int b = 8;
  printf("%d a la puissance %d vaut %d\n", a, b, puissance(a, b));
  return 0;
}
