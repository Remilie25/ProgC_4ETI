/* Nom du fichier : boucles.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : tracer un triangle avec '*' sur le bords et '#' a l'interieur.
              compteur est la hauteur du triangle (max 9).
 */

#include <stdio.h>


int main(){
  int compteur = 9; //doit etre < 10
  int ligne = 0;
  int colonne = 0;

  printf("Avec boucle for\n");
  //boucle d'affichage avec for
  for (;ligne < compteur; ligne++){
    for (colonne = 0;colonne <= ligne; colonne++){
      if (colonne == ligne) {
	printf("*\n");
      } else if (colonne == 0 || (ligne + 1) == compteur) {
	printf("* ");
      } else {
	printf("# ");
      }
    }
  }

  //separation
  printf("\n\nAvec boucle while :\n");

  ligne = 0;
  //boucle d'affichage avec while
  while (ligne < compteur){
    colonne = 0;
    while (colonne <= ligne){
      if (colonne == ligne) {
	printf("*\n");
      } else if (colonne == 0 || (ligne + 1) == compteur) {
	printf("* ");
      } else {
	printf("# ");
      }
      colonne++;
    }
    ligne++;
  }
  
  return 0;
}
