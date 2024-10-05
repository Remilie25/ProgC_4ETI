/* Nom du fichier : chercher2.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : Renvoyer l'appartenance d'une phrase a une liste de phrase.
 */

#include <stdio.h>

int main() {
  char phrase_tab[10][50] = {"Bonjour, comment ça va ?", "Le temps est magnifique aujourd'hui.",
    "C'est une belle journée.", "La programmation en C est amusante.", "Les tableaux en C sont puissants.",
    "Les pointeurs en C peuvent être déroutants.", "Il fait beau dehors.",
    "La recherche dans un tableau est intéressante.", "Les structures de données sont importantes.",
    "Programmer en C, c'est génial."};

  /*Recupere la phrase rentre par l'utilisateur en evitant des debordements.*/
  printf("Entrez la phrase a chercher (maximum 50 characteres ascii, ex : 'é' vaut 2 char ascii) : ");
  char phrase_cherchee[51];
  fgets(phrase_cherchee, sizeof(phrase_cherchee), stdin);
  
  for(unsigned short indice_phrase = 0; indice_phrase < 10; indice_phrase++){
    unsigned short indice_char = 0;

    while (phrase_tab[indice_phrase][indice_char] == phrase_cherchee[indice_char]){
      indice_char++;
    }

    if (!phrase_tab[indice_phrase][indice_char] && phrase_cherchee[indice_char] == 10){
      /*La phrase rentree finie par un retour a la ligne alors que celle enregistree fini par un charactere
	nul. Dans les dexu cas, meme si le charactere de fin est different, il marque la fin de la phrase et
	n'en fait pas parti.*/
      printf("Phrase trouvee\n");
      return 0;
    }
  }
  printf("Phrase non trouvee\n");
  
  return 0;
}
