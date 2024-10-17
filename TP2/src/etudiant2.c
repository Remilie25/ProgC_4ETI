/* Nom du fichier : etudiant2.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : Gerer une base de donnees de cinq etudiants avec une structure.
*/

#include <stdio.h>
#include <string.h>

//Copier du fichier etudiant.c car on ne peut pas creer de nouveau fichier.
void print_note_tab(float * tab_ptr, int indice_max){
  /*Cette fonction affiche un tableau de note jusqu'a indice_max pour des notes entre 0 et 20.
    Les notes sont supposees avoir au maximum deux chiffres apres la virgule.*/
  short indice = 0; //maximum 5 notes donc short suffit.
  for(;indice < indice_max && tab_ptr[indice] < 20. && tab_ptr[indice] > 0.; indice++){
    printf("%.2f\t", tab_ptr[indice]);
  }
}

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

void print_etudiant(etudiant* db_ptr, short etudiant){
  //Cette fonction affiche l'etudiant a l'indice etudiant de la base de donnees pointee par db_ptr
  printf("Etudiant.e %hd:\nPrenom : %s\nNom : %s\nAdresse : %s\nNotes de progC : ", etudiant + 1,
	 (db_ptr + etudiant)->nom, (db_ptr + etudiant)->prenom, (db_ptr + etudiant)->adresse);
  print_note_tab((db_ptr + etudiant)->notes.progC, 5);
  printf("\nNotes de syst_exploit : ");
  print_note_tab((db_ptr + etudiant)->notes.syst_exploit, 5);
  printf("\n\n");
}

int main(){
  //initialisation de la base de donnee.
  etudiant database[5];

  //Nom et prenom
  strcpy((database[0].nom), "Bourges");
  strcpy(database[0].prenom, "Vincent");
  strcpy(database[1].nom, "Aussant");
  strcpy(database[1].prenom, "Esteban");
  strcpy(database[2].nom, "Del Turco");
  strcpy(database[2].prenom, "Nathan");
  strcpy(database[3].nom, "Romero");
  strcpy(database[3].prenom, "Etienne");
  strcpy(database[4].nom, "de Pretto");
  strcpy(database[4].prenom, "Remi");

  //Adresse
  strcpy(database[0].adresse, "La Doua");
  strcpy(database[1].adresse, "Lyon");
  strcpy(database[2].adresse, "Paris");
  strcpy(database[3].adresse, "Aix en Provence");
  strcpy(database[4].adresse, "Roquebrune Cap Martin");

  //Notes de progC et syst_exploit
  //Notes > 20 signifie pas de notes
  database[0].notes.progC[0] = 1.;
  database[0].notes.progC[1] = 2.;
  database[0].notes.progC[2] = 3.;
  database[0].notes.progC[3] = 21.;
  database[0].notes.progC[4] = 21.;
  database[1].notes.progC[0] = 4.;
  database[1].notes.progC[1] = 5.;
  database[1].notes.progC[2] = 6.;
  database[1].notes.progC[3] = 21.;
  database[1].notes.progC[4] = 21.;
  database[2].notes.progC[0] = 11.;
  database[2].notes.progC[1] = 12.;
  database[2].notes.progC[2] = 13.;
  database[2].notes.progC[3] = 21.;
  database[2].notes.progC[4] = 21.;
  database[3].notes.progC[0] = 4.;
  database[3].notes.progC[1] = 5.;
  database[3].notes.progC[2] = 6.;
  database[3].notes.progC[3] = 21.;
  database[3].notes.progC[4] = 21.;
  database[4].notes.progC[0] = 6.;
  database[4].notes.progC[1] = 7.;
  database[4].notes.progC[2] = 8.;
  database[4].notes.progC[3] = 9.;
  database[4].notes.progC[4] = 10.;
  database[0].notes.syst_exploit[0] = 4.;
  database[0].notes.syst_exploit[1] = 5.;
  database[0].notes.syst_exploit[2] = 6.;
  database[0].notes.syst_exploit[3] = 21.;
  database[0].notes.syst_exploit[4] = 21.;
  database[1].notes.syst_exploit[0] = 11.;
  database[1].notes.syst_exploit[1] = 12.;
  database[1].notes.syst_exploit[2] = 13.;
  database[1].notes.syst_exploit[3] = 21.;
  database[1].notes.syst_exploit[4] = 21.;
  database[2].notes.syst_exploit[0] = 4.;
  database[2].notes.syst_exploit[1] = 5.;
  database[2].notes.syst_exploit[2] = 6.;
  database[2].notes.syst_exploit[3] = 21.;
  database[2].notes.syst_exploit[4] = 21.;
  database[3].notes.syst_exploit[0] = 6.;
  database[3].notes.syst_exploit[1] = 7.;
  database[3].notes.syst_exploit[2] = 8.;
  database[3].notes.syst_exploit[3] = 9.;
  database[3].notes.syst_exploit[4] = 10.;
  database[4].notes.syst_exploit[0] = 1.;
  database[4].notes.syst_exploit[1] = 2.;
  database[4].notes.syst_exploit[2] = 3.;
  database[4].notes.syst_exploit[3] = 8.;
  database[4].notes.syst_exploit[4] = 21.;

  //affichage
  short eleve = 0;
  for(;eleve < 5; eleve++){
    print_etudiant(database, eleve);
  }
    
  return 0;
}
