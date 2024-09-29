/* Nom du fichier : etudiant.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : Gerer une base de donnees de cinq etudiants.
*/

#include <stdio.h>

void print_note_tab(float * tab_ptr, int indice_max){
  /*Cette fonction affiche un tableau de note jusqu'a indice_max pour des notes entre 0 et 20.
    Les notes sont supposees avoir au maximum deux chiffres apres la virgule.*/
  short indice = 0; //maximum 5 notes donc short suffit.
  for(;indice < indice_max && tab_ptr[indice] < 20. && tab_ptr[indice] > 0.; indice++){
    printf("%.2f\t", tab_ptr[indice]);
  }
}

int main(){
  /*Tableau tri-dimentionnelle. 1ere composante = 1 eleve, 2e = chaine de caracteres representant le nom ou
    le prenom.*/
  char nom_prenom[5][2][30] = {{"Bourges", "Vincent"}, {"Aussant", "Esteban"}, {"Del Turco", "Nathan"},
			       {"Romero", "Etienne"}, {"de Pretto", "Remi"}};

  //Tableau bi-dimensionnelle. 1ere composante = chaine de caracteres represantant l'adresse d'1 eleve.
  char adresse[5][60] = {"La Doua", "Lyon", "Paris", "Aix-en-Provence", "Roquebrune Cap Martin"};

  /*2 tableaux bi-dimensionnelle. 1ere composante = tableau de notes d'un eleve, 2e = une note d'un eleve.
    Si Note < 0 ou Note > 20 signifie pas de notes*/
  float notes_progC[5][5] = {{1., 2., 3., 4., 21.}, {4., 5., 6., 21., 21.}, {7., 8., 9., 12., 21.},
			     {1., 2., 3., 21., 21.}, {4., 5., 6., 12., 24.}};
  float notes_syst_exploit[5][5] = {{4., 5., 6., 12., 24.}, {1., 2., 3., 4., 21.}, {4., 5., 6., 21., 21.},
				    {7., 8., 9., 12., 21.}, {1., 2., 3., 21., 21.}};

  //affichage
  short eleve = 0;

  for(;eleve < 5; eleve++){
    printf("Nom : %s, Prenom : %s, Adresse : %s\nNotes en progC : ", nom_prenom[eleve][0],
	   nom_prenom[eleve][1], adresse[eleve]);
    print_note_tab(notes_progC[eleve], 5);
    printf("\nNotes en Syst_exploit : ");
    print_note_tab(notes_syst_exploit[eleve], 5);
    printf("\n\n");
  }
  
  return 0;
}

