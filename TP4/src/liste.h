/* Nom du fichier : liste.h
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : gerer une liste simplement chainee.
*/

//Type couleur
typedef struct couleur{
  unsigned char rouge;
  unsigned char vert;
  unsigned char bleu;
  unsigned char alpha;
} couleur;

/*Type liste simplement chainee de couleur. Sans precision du sujet, les listes sont affranchies de leurs
  surcout structurel d'element de debut et de fin ne stockant aucune information utile. Ainsi une liste vide
  est un pointeur de type couleur_list de valeur NULL, sinon il y a au moins un element. De meme, sans
  precision du sujet, la liste ne stockera pas directement la couleur mais un pointeur vers cette derniere.*/
typedef struct couleur_item{
  couleur* valeur_couleur;
  struct couleur_item* prochaine_couleur;
} couleur_item;

/*Comme le sujet impose que insertion prenne en entree un pointeur de liste et non un pointeur de pointeur de
  liste et qu'insertion ne retourne rien. Alors couleur_list n'est pas le type precedent car l'appel de
  insertion sur la liste vide ne pourrait pas marcher du fait du choix que la liste vide est le pointeur de
  type couleur_list NULL. Mais couleur_list est une structure composee d'un pointeur pointant vers
  couleur_item. De ce fait, insertion pourra modifier le pointeur de couleur_item.*/
typedef struct couleur_list{
  couleur_item* couleur_item_pointeur;
} couleur_list;

void print_couleur(couleur* col);

couleur couleur_from_long(long data);

void insertion(couleur* couleur_inserer, couleur_list* c_list);

void parcours(couleur_list* c_list);

void free_couleur_list(couleur_list* c_list);
