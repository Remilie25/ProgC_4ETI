/* Nom du fichier : etudiant2_from_TP2.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : Definition d'une structure d'etudiant et fonctions utiles. Extrait du ../TP2/etudiant2.c.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "etudiant2_from_TP2.h" /*Pour recuperer la definition d'etudiant. Elle a ete mise dans le .h pour que
				  la definition d'etudiant soit commune a tous les fichiers.*/

//Copier du fichier etudiant.c car on ne peut pas creer de nouveau fichier.
void print_note_tab(float * tab_ptr, int indice_max){
  /*Cette fonction affiche un tableau de note jusqu'a indice_max pour des notes entre 0 et 20.
    Les notes sont supposees avoir au maximum deux chiffres apres la virgule.*/
  short indice = 0; //maximum 5 notes donc short suffit.
  for(;indice < indice_max && tab_ptr[indice] < 20. && tab_ptr[indice] > 0.; indice++){
    printf("%.2f\t", tab_ptr[indice]);
  }
}

void print_etudiant(etudiant* db_ptr, short etudiant){
  //Cette fonction affiche l'etudiant a l'indice etudiant de la base de donnees pointee par db_ptr
  printf("Etudiant.e %hd:\nPrenom : %s\nNom : %s\nAdresse : %s\nNotes de progC : ", etudiant + 1,
	 (db_ptr + etudiant)->nom, (db_ptr + etudiant)->prenom, (db_ptr + etudiant)->adresse);
  print_note_tab((db_ptr + etudiant)->notes.progC, 5);
  printf("\nNotes de syst_exploit : ");
  print_note_tab((db_ptr + etudiant)->notes.syst_exploit, 5);
  printf("\n\n");
}

void init_etudiant(etudiant* etu_ptr){
  /*Cette fonction initialise un etudiant : met le caractere nul en debut de string et met les notes a -1 car
  seul les notes entre 0 et 20 comptent.*/
  etu_ptr->nom[0] = 0.;
  etu_ptr->prenom[0] = 0.;
  etu_ptr->adresse[0] = 0.;
  for(unsigned char indice = 0; indice < 5; indice++){
    etu_ptr->notes.progC[indice] = -1.;
    etu_ptr->notes.syst_exploit[indice] = -1.;
  }
}

char* string_of_etudiant(etudiant* etu_ptr){
  //Cette fonction renvoie les informations de l'etudiant pointe par etu_ptr dans une string.
  const unsigned long len_nom = strnlen(etu_ptr->nom, sizeof(etu_ptr->nom));
  const unsigned long len_prenom = strnlen(etu_ptr->prenom, sizeof(etu_ptr->prenom));
  const unsigned long len_adresse = strnlen(etu_ptr->adresse, sizeof(etu_ptr->adresse));
  const char tab = '\t';

  char* etu_str = (char*) calloc(len_nom + len_prenom + len_adresse + 50 + 1 + 12, sizeof(char));
  /*taille de la chaine de caracteres pour un etudiant :
    taille du nom,prenom,adresse + 10 notes de 0 a 20 avec deux chiffres apres la virgule + 1 pour '\0' et 12
    separateur '\t' + 1 pour le retour a la ligne.*/

  char* end_etu_ptr = etu_str + len_nom + len_prenom + len_adresse + 2; 
  /*stocke la position du caractere nul de etu_str apres ecriture du nom, prenom, adresse.
    position d'origine + longueur de chaque chaine (nom, prenom, adresse) + les 2 separateurs*/
  
  strncat(etu_str, etu_ptr->nom, len_nom);
  strncat(etu_str, &tab, 1);
  strncat(etu_str, etu_ptr->prenom, len_prenom);
  strncat(etu_str, &tab, 1);
  strncat(etu_str, etu_ptr->adresse, len_adresse);
  //Notes progC
  /*On limite l'ecriture a 32 car pour chaque note on a au maximum 4 chiffres, 1 virgule et un '\t' + le
   premier '\t' + le caratere nul de fin.*/
  end_etu_ptr += snprintf(end_etu_ptr, 32, "\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t", etu_ptr->notes.progC[0],
			 etu_ptr->notes.progC[1], etu_ptr->notes.progC[2],
			 etu_ptr->notes.progC[3], etu_ptr->notes.progC[4]);
  //Notes syst_eploit
  end_etu_ptr += snprintf(end_etu_ptr, 31, "%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n", etu_ptr->notes.syst_exploit[0],
			 etu_ptr->notes.syst_exploit[1], etu_ptr->notes.syst_exploit[2],
			 etu_ptr->notes.syst_exploit[3], etu_ptr->notes.syst_exploit[4]);

  return etu_str;
}

void safe_float_sscanf(char* str_ptr, char* pattern, float* dest, float default_value){
  /*Cette fonction realise sscanf(str_ptr, pattern, dest) s'il n'y a pas d'erreur. Sinon elle met la
    default_value. Le pattern est un seul specificateur de float.*/
  if(1 != sscanf(str_ptr, pattern, dest)){
    *dest = default_value;
  }
}


