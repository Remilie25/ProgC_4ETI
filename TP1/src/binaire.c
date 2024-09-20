/* Nom du fichier : binaire.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : conversion d'un nombre en base 10 vers un nombre en base 2 par l'algorithme d'Euclid ou par mask
 */

#include <stdio.h>


int main(){
  int nombre = 158;

  //version algorithme d'Euclid:
  
  int quotient = nombre; //stocke le quotient de chaque etape du procede d'Euclid.
  char bin_tab[sizeof(int) * 8]; //stocke les bits du nombre dans l'ordre LSB.
  short int index = 0; //pointe vers le prochain emplacement a remplir du bin_tab.

  //boucle de l'algorithme d'euclid
  while (quotient){
    if (quotient % 2){
      bin_tab[index] = '1';
    }
    else
      bin_tab[index] = '0';
    quotient /= 2;
    index++;
  }
  
  //affichage
  printf("La conversion en binaire de %d est ", nombre);
  for (index--;index >= 0; index--){ //On part de la derniere case remplie (index -1) et on parcours a l'envers.
    printf("%c", bin_tab[index]);
  }
  printf("\n");


  //Version alternative avec un mask :

  int mask = 1 << (sizeof(int) * 8 -2); // le MSB a 1, le reste a 0.

  printf("La conversion en binaire de %d est ", nombre);
  
  while(mask){
    if (nombre & mask){
      printf("1");
    } else {
      printf("0");
    }
    mask >>= 1; //division par 2 ou decalage a droite
  }

  printf("\n");
  
  return 0;
}
