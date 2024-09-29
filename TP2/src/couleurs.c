/* Nom du fichier : couleurs.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : Gerer une base de donnees de 10 couleurs avec une structure.
*/

#include <stdio.h>

//Definition du type couleur. Chaque composante sur 1 octect.
typedef struct couleur{
  unsigned char rouge;
  unsigned char vert;
  unsigned char bleu;
  unsigned char alpha;
} couleur;

void print_couleur(couleur* db_ptr, short couleur){
  //Cette fonction affiche la couleur a l'indice couleur de la base de donnees pointee par db_ptr
  printf("Couleur %hd :\nRouge : %hhu\nVert : %hhu\nBleu : %hhu\nAlpha : %hhu\n\n", couleur + 1,
	 db_ptr[couleur].rouge, db_ptr[couleur].vert, db_ptr[couleur].bleu, db_ptr[couleur].alpha);
}

int main(){
  couleur database[10] = {{0xef, 0x78, 0x12, 0xff}, {0xac, 0x18, 0x1, 0x1f}, {0x23, 0xa8, 0xb2, 0xf5},
			  {0x45, 0x15, 0xff, 0x3f}, {0xdd, 0xdd, 0xdd, 0xff}, {0xe4, 0x56, 0x12, 0x66},
			  {0xef, 0x78, 0x12, 0xff}, {0xef, 0x78, 0x12, 0xff}, {0xef, 0x78, 0x12, 0xff}};
  database[8].rouge = 0x11;
  database[8].vert = 0x22;
  database[8].bleu = 0x33;
  database[8].alpha = 0x44;
  database[9].rouge = 0x55;
  database[9].vert = 0x66;
  database[9].bleu = 0x77;
  database[9].alpha = 0x88;

  short couleur = 0;
  for(; couleur < 10; couleur++){
    print_couleur(database, couleur);
  }
  
  return 0;
}
