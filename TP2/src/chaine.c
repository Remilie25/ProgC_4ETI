/* Nom du fichier : chaine.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : trois fonctions realisant :
        - le calcul de longueur d'une chaine de carateres
	      - la copie d'une chaine de carateres
	      - la concatenation de chaine de carateres.
 */

#include <stdio.h>
#include <limits.h>

unsigned long string_len (char* str_ptr){
  //Cette fonction calcule la longueur d'un tableau de char (doit etre representable sur un unsigned long).
  unsigned long indice = 0;

  for(;str_ptr[indice] != '\0'; indice++){
    if (indice == ULONG_MAX){
      return indice; //sinon boucle infini.
    }
  }

  return indice;
}

void string_copy(char* src_ptr, char* dest_ptr, unsigned long dest_len){
  /*Cette fonction copie la chaine de char pointee par src_ptr dans la chaine pointee par dest_len sans
    deborder. dest_len est la longueur de la chaine destination en comptant le '\n' final.*/
  unsigned long indice = 0;
  while (src_ptr[indice] != '\0' && indice < dest_len){
    dest_ptr[indice] = src_ptr[indice];
    indice ++;
  }
  /*Si la boucle s'est arretee, c'est soit qu'elle a lu le caractere '\0' et il faut l'ajouter a la
    destination. Soit qu'elle est arrivee au bout de la chaine destination et il faut ajouter '\0'.*/
  dest_ptr[indice] = '\0';
}

void string_concatenate(char* src_ptr, char* dest_ptr, unsigned long dest_len){
  /*Cette fonction concatene deux chaines de caracteres : de celle pointee par src_ptr vers celle pointee par
    dest_ptr. dest_len est la longueur de la chaine destination en comptant le '\n' final.*/
  
  //sert a savoir ou commencer a ecrire dans la destination. A soustraire de dest_len.
  unsigned long decalage = string_len(dest_ptr);
  string_copy(src_ptr, dest_ptr + decalage, dest_len - decalage);
}


int main(){
  // la partie "En trop !" n'est pas concaténé car elle est plus grande que la taille de la chaine 2, a la fin la 2e chaine est pleine
  char chaine_a_copier[20] = "Hello";
  char chaine_a_concatener_et_tronquer[20] = " world ! En trop !"; 
  char resultat1[14];
  string_copy(chaine_a_copier, resultat1, sizeof(resultat1) / sizeof(resultat1[0]));
  char resultat2[14];
  string_copy(resultat1, resultat2, sizeof(resultat2) / sizeof(resultat2[0]));
  string_concatenate(chaine_a_concatener_et_tronquer, resultat2, sizeof(resultat2) / sizeof(resultat2[0]));

  printf("Chaine copiee : %s\tet sa longueur : %lu\nchaine concatenee : %s\n",
	 resultat1, string_len(resultat1), resultat2);
  return 0;
}
