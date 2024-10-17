/* Nom du fichier : liste.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : gerer une liste simplement chainee.
*/

#include <stdlib.h>
#include <stdio.h>
#include "liste.h"

void print_couleur(couleur* col){
  //Cette fonction affiche la couleur col (du TP2)
  printf("Couleur :\nRouge : %hhu\nVert : %hhu\nBleu : %hhu\nAlpha : %hhu\n\n",
	 col->rouge, col->vert, col->bleu, col->alpha);
}

couleur couleur_from_long(long data){
  //Cette fonction prend les octets d'un long pour faire une couleur. (du TP3)

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

void insertion(couleur* couleur_inserer, couleur_list* c_list){
  /*Cette fonction insere la couleur_inserer au debut de la c_list. Comme le sujet ne precise pas, la fonction
    modifiera la couleur_inserer et la couleur en tete de liste.*/

  couleur_item* nouvelle_couleur = malloc(sizeof(couleur_item));
  nouvelle_couleur->valeur_couleur = couleur_inserer;
  nouvelle_couleur->prochaine_couleur = c_list->couleur_item_pointeur;
  c_list->couleur_item_pointeur = nouvelle_couleur;
}

void free_couleur_list(couleur_list* c_list){
  /*Cette fonction libere l'espace memoire alloue a c_list->couleur_item_pointeur, ie tous les pointeurs vers
    des couleur_item sont libere mais c_list non, c_list devient la liste vide.
    Algo : appel recursif sur la structure, ie parcours en profondeur. Attention a la pile d'appel !
           Version alternative en faisant une boucle while (col_to_free){
	                                               meme corps que le if;
						       col_to_free = c_list->couleur_item_pointeur;}*/
  couleur_item* col_to_free = c_list->couleur_item_pointeur;
  if (col_to_free){
    /*S'il existe une couleur (col_to_free non NULL), on copie le pointeur de la prochaine couleur dans c_list,
      on libere cette couleur (col_to_free) et on se rappelle recursivement.*/
    c_list->couleur_item_pointeur = col_to_free->prochaine_couleur;
    free(col_to_free);
    free_couleur_list(c_list);
  }
}


void parcours(couleur_list* c_list){
  //Cette fonction parcours c_list en affichant les couleurs. Algo : parcours en profondeur sans recursion.
  couleur_item* prochaine_col_afficher = c_list->couleur_item_pointeur;
  while (prochaine_col_afficher){
    print_couleur(prochaine_col_afficher->valeur_couleur);
    prochaine_col_afficher = prochaine_col_afficher->prochaine_couleur;
  }
}
