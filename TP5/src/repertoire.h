/* Nom du fichier : repertoire.h
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : afficher les fichiers et repertoires dans un repertoires
 */

void lire_dossier(const char* chemin_dossier);

//Type de liste de caracteres
typedef struct str_list{
  char* str;
  unsigned long len;
  struct str_list* next_str;
} str_list;


//Type pour faire une queue de str (FIFO).
typedef struct str_queue{
  str_list* first;
  str_list* last;
} str_queue;


unsigned char insert_queue(char* str, unsigned long len, str_queue* queue);

void free_first(str_queue* queue);

void print_queue(str_queue* queue);

void lire_dossier_recursif(const char* chemin_dossier);

void lire_dossier_iteratif(const char* chemin_dossier);
