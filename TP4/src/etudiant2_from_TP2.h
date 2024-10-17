/* Nom du fichier : etudiant2_from_TP2.h
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : Prototypes d'une structure d'etudiant et ses fonctions utiles. Extrait du ../TP2/etudiant2.c.
*/

#include <stdio.h>

//Copier du fichier etudiant.c car on ne peut pas creer de nouveau fichier.
void print_note_tab(float * tab_ptr, int indice_max);

//Definition du type etudiant
typedef struct etudiant {
  char nom[30];
  char prenom[30];
  char adresse[60];
  struct notes{
    float progC[5]; 
    float syst_exploit[5];
  } notes;
} etudiant;

void print_etudiant(etudiant* db_ptr, short etudiant);

void init_etudiant(etudiant* etu_ptr);

char* string_of_etudiant(etudiant* etu_ptr);

void safe_float_sscanf(char* str_ptr, char* pattern, float* dest, float default_value);
