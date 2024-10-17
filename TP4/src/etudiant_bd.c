/* Nom du fichier : etudiant2_bd.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : Gerer une structure d'etudiants avec des fichiers.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "etudiant2_from_TP2.h"
#include "fichier.h"

int main(){
  const unsigned int Nbr_etudiant = 5;
  etudiant database[Nbr_etudiant];
  char input[100]; //Stocke la derniere entree de l'utilisateur.
  char token_delim = ';'; //Separateur entre les notes.
  char* token; //pointe vers une note

  //Initialisation des notes (car la note nulle est une vraie note)
  for(unsigned char indice = 0; indice < 5; indice++){
    init_etudiant(database + indice);
  }

  //Remplissage du tableau par l'utilisateur
  for (unsigned int indice = 0; indice < Nbr_etudiant; indice++){
    printf("Entrez les details de l'etudiant.e %d :\nNom (%lu caracteres max) : ", indice + 1,
	   sizeof(database[indice].nom));
    fgets(input, sizeof(input), stdin);
    strncpy(database[indice].nom, input, sizeof(database[indice].nom));
    erase_EOL(database[indice].nom, sizeof(database[indice].nom));

    printf("Prenom (%lu caracteres max) : ", sizeof(database[indice].prenom));
    fgets(input, sizeof(input), stdin);
    strncpy(database[indice].prenom, input, sizeof(database[indice].prenom));
    erase_EOL(database[indice].prenom, sizeof(database[indice].prenom));

    printf("Adresse (%lu caracteres max) : ", sizeof(database[indice].adresse));
    fgets(input, sizeof(input), stdin);
    strncpy(database[indice].adresse, input, sizeof(database[indice].adresse));
    erase_EOL(database[indice].adresse, sizeof(database[indice].adresse));

    //Recuperation des notes
    //progC
    printf("Notes en programmation C (max 5 separees par des ';', rappel '.' pour la virgule) : ");
    fgets(input, sizeof(input), stdin);
    token = strtok(input, &token_delim); //Initialise strtok

    for(unsigned char indice_note = 0; indice_note < 5 && token != NULL; indice_note++){
      //Si token == NULL => pas de nouvelle note.
      safe_float_sscanf(token, "%f", &database[indice].notes.progC[indice_note], -1.);
      token = strtok(NULL, &token_delim);
    }
    //syst_exploit
    printf("Notes en systeme d'exploition (max 5 separees par des ';', rappel '.' pour la virgule) : ");
    fgets(input, sizeof(input), stdin);
    token = strtok(input, &token_delim); //Initialise strtok

    for(unsigned char indice_note = 0; indice_note < 5 && token != NULL; indice_note++){
      //Si token == NULL => pas de nouvelle note.
      safe_float_sscanf(token, "%f", &database[indice].notes.syst_exploit[indice_note], -1.);
      token = strtok(NULL, &token_delim);
    }
  }

  //Ecriture
  char nom_de_fichier[13] = "etudiant.txt";
  
  //Effacage de l'ancien fichier, sinon ecrire ajoutera a la fin.
  clear_file(nom_de_fichier);

  //Header
  ecrire_dans_fichier(nom_de_fichier, "Nom\tPrenom\tAdresse\tNotes progC\t\t\t\t\tNotes syst_exploit\t\t\t\t\n");
  //Corps
  char* str_etu; //Stocke la conversion d'un etudiant en chaine de caracteres.
  for(unsigned char indice = 0; indice < 5; indice++){
    str_etu = string_of_etudiant(database+indice);
    ecrire_dans_fichier(nom_de_fichier, str_etu);
    free(str_etu);
  }
  
  return 0;
}
