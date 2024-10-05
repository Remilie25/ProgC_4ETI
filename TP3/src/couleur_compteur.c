/* Nom du fichier : couleur_compteur.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Definition du type couleur. Chaque composante sur 1 octect.
typedef struct couleur{
  unsigned char rouge;
  unsigned char vert;
  unsigned char bleu;
  unsigned char alpha;
} couleur;

int is_same_couleur(couleur c0, couleur c1){
  //Cette fonction renvoie si les deux couleurs sont egales.
  return (c0.rouge == c1.rouge && c0.vert == c1.vert && c0.bleu == c1.bleu && c0.alpha == c1.alpha);
}

couleur couleur_from_long(long data){
  //Cette fonction prend les octets d'un long pour faire une couleur.

  //Definition d'une union pour lire octet par octet.
  union int_byte{
    int data;
    char byte[sizeof(int)];
  };
  
  union int_byte tmp;
  tmp.data = (int) data;
  
  couleur col = {tmp.byte[0], tmp.byte[1], tmp.byte[2], tmp.byte[3]};
  
  return col;
}

typedef struct couleur_occurrence{
  couleur col;
  unsigned int occ;
} couleur_occurrence;

typedef struct bool_n_int{
  unsigned char bool;
  unsigned int integer;
} bool_n_int;

bool_n_int is_couleur_in(couleur col, couleur_occurrence* tab_ptr, unsigned int len){
  /*Cette fonction renvoie si col appartient au tableau de couleur pointe par tab_ptr et l'indice de la
    premiere apparition.*/

  bool_n_int result; // Le booleen indique si col appartient au tableau et l'entier son indide.
  
  for(unsigned int indice = 0; indice < len; indice++){
    if (is_same_couleur(col, tab_ptr[indice].col)){
      result.bool = 1;
      result.integer = indice;
      return result;
    }
  }
  result.bool = 0;
  result.integer = 0;	
  return result;
}

void print_occ_tab(couleur_occurrence* tab_ptr, unsigned int len){
  for(unsigned int indice = 0; indice < len; indice++){
    printf("%02hhx %02hhx %02hhx %02hhx : %u\n", tab_ptr[indice].col.rouge, tab_ptr[indice].col.vert,
	   tab_ptr[indice].col.bleu, tab_ptr[indice].col.alpha, tab_ptr[indice].occ);
  }
}

int main() {
  //Initialisation du generateur de nombres pseudo aleatoires
  srandom(time(NULL));

  //Initialisation du tableau de couleurs.
  const unsigned int len = 100;
  couleur col_tab[len];

  for(unsigned int indice = 0; indice < len; indice++){
    col_tab[indice] = couleur_from_long(random());
  }

  //Construction du tableau regroupant couleur_occurrence
  couleur_occurrence occ_tab[len]; /*Il y a tellement de couleurs differentes que la probabilite que le
					tableau d'occurrence soit de taille comparable a la taille de col_tab
					est tres grande. D'ou la meme taille.*/
  unsigned int next_empty_slot = 0; //Stocke le prochain indice a remplir de occ_tab. C'est aussi le nbr d'element.
  bool_n_int tmp;

  for(unsigned int indice = 0; indice < len; indice++){
    tmp = is_couleur_in(col_tab[indice], occ_tab, next_empty_slot);
    if (tmp.bool){
      occ_tab[tmp.integer].occ++;
    }
    else{
      occ_tab[next_empty_slot].col = col_tab[indice];
      occ_tab[next_empty_slot].occ = 1;
      next_empty_slot++;
    }
  }

  print_occ_tab(occ_tab, next_empty_slot);
  
  return 0;
}
