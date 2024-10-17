/* Nom du fichier : chercherfichier.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : compter le nombre de fois qu'une phrase apparait dans un fichier.
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "fichier.h"
#include "user_input.h"

//Type de liste de caracteres
typedef struct char_list{
  char character;
  struct char_list* next_char;
} char_list;


//Type pour stocker un pointeur vers le premier et denier element de la liste (fl pour first last)
typedef struct subsequence_fl{
  char_list* first;
  char_list* last;
} subsequence_fl;


unsigned char is_regexp(const char* regexp, char_list* subsequence){
  /*Cette fonction renvoie 1 si regexpr == sub_sequence, ie chaque caractere sont egaux. Sinon 0.
    regexp et subsequence doivent avoir la meme longueur.
    regexp : chaine de caracteres normale. sub_sequence : liste chainee de caracteres*/

  unsigned long indice = 0;
  while (regexp[indice] && subsequence && regexp[indice] == subsequence->character){
    //Tant que on n'a pas atteint la fin d'une des 2 structures et que les carateres sont egaux.
    indice++;
    subsequence = subsequence->next_char;
  }
  if (!regexp[indice]){
    return 1;
  }
  return 0;
}


unsigned char next_char_read(char* char_ptr, const int file_descriptor){
  /*Cette fonction renvoie 0 <=> EOF, 1 <=> il reste des carateres sur la lignes, 2 <=> EOL.
    Elle met le prochain caractere lu dans un fichier ouvert (file_descriptor) sur le pointeur char_ptr.
    Attention les retours a la ligne sont convertis en caratere nul ! (L'exercice ne permet pas
    qu'une phrase soit a cheval sur plusieurs ligne...)*/
  char character;
  unsigned char returned_value = (unsigned char) read(file_descriptor, &character, 1);
  if (character == '\n'){
    *char_ptr = 0;
    return 2;
  } else{
    *char_ptr = character;
  }
  return returned_value;
}

unsigned char init_subsequence(subsequence_fl* subsequence, const int file_descriptor,
			       const unsigned long regexp_len){
  /*Cette fonction initialise la sous-suite en la remplissant avec les caracteres et pointeurs.
    Elle donne les pointeurs de debut et de fin a subsequence.
    Renvoie 0 <=> EOF, 1 <=> il reste des carateres sur la lignes, 2 <=> EOL.*/
  char last_read_char;
  unsigned long len = 1;
  char_list* new_char; //Pour creer un nouvel element
  subsequence->first = (char_list*) calloc(1, sizeof(char_list));
  
  //Stocke 0 <=> EOF, 1 <=> il reste des carateres sur la lignes, 2 <=> EOL.
  unsigned char state = next_char_read(&last_read_char, file_descriptor); 
  
  if (!state){
    //Si aucun caractere n'a ete lu => fin de fichier donc rien a faire. Sinon on continue.
    return 0;
  }
  //Initialisation de la sous-suite avec un seul caractere
  subsequence->last = subsequence->first;
  subsequence->first->character = last_read_char;
    
  while(len < regexp_len && subsequence->last->character){
    //Tant que la sous-suite et de longueur inferieure a regexp_len et que nous ne lisons pas le caractere nul.
    //Recupere un nouveau caractere
    state = next_char_read(&last_read_char, file_descriptor); 

    if (!state){
      //Si aucun caractere n'a ete lu => fin de fichier donc rien a faire. Sinon on continue.
      return 0;
    }
    new_char = (char_list*) malloc(sizeof(char_list));
    new_char->character = last_read_char;
    new_char->next_char = NULL;
    //Inclu le nouveau caractere dans la chaine.
    subsequence->last->next_char = new_char;
    subsequence->last = new_char;
    len++;
  }
  return state;
}

void free_subsequence(char_list* subsequence){
  /*Cette fonction libere l'espace memoire alloue a subsequence. Algo : appel recursif sur la structure,
    ie parcours en profondeur*/
  if (subsequence->next_char){
    //Si il existe un prochain caratere, on libere le prochain caractere en 1er (appel recursive).
    free_subsequence(subsequence->next_char);
  }
  //Dans tous les cas on libere le caratere actuel.
  free(subsequence);
}


unsigned char next_subsequence(subsequence_fl* subsequence, unsigned char state,
			       const int file_descriptor, const unsigned long regexp_len){
  /*Cette fonciton calcul la prochaine sous-suite a tester sur la meme ligne si possible. Sinon elle change
    de ligne. Renvoie 0 <=> EOF, 1 <=> il reste des carateres sur la lignes, 2 <=> EOL.*/

  if (state == 2){//Si on est en bout de ligne, il faut recreer une sous-suite sur la prochaine ligne.
    free_subsequence(subsequence->first);
    return init_subsequence(subsequence, file_descriptor, regexp_len);
  }
  //Sinon
  char last_read_char;
  state = next_char_read(&last_read_char, file_descriptor); 

  if (!state){
    //Si aucun caractere n'a ete lu => fin de fichier donc rien a faire. Sinon on continue.
    return 0;
  }
  char_list* new_char = (char_list*) malloc(sizeof(char_list));
  new_char->character = last_read_char;
  new_char->next_char = NULL;
  //Inclu le nouveau caractere dans la chaine.
  subsequence->last->next_char = new_char;
  subsequence->last = new_char;
  //Suppression du premier caractere.
  char_list* tmp = subsequence->first->next_char;
  free(subsequence->first);
  subsequence->first = tmp;
  return state;
}

void print_regexp_occurrence_in_file_by_line(const char* regexp, const char* file, const unsigned long regexp_len){
  /*Cette fonction compte le nombre d'expressions regulieres trouvees dans file qui est un chemin vers un
    fichier. Sans precision du sujet les regexp peuvent se chevaucher, ie elles ne doivent pas etre disjointes
    pour compter pour 2. Ex : regexp = "aba", dans le fichier, il y a "ababa", alors la fonction renvoie 2.
    Algorithme : Parcours le fichier caractere par caratere en maintenant une sous-suite de longueur
    regexp_len et appelle is_regexp pour savoir si la sous-suite est regexp ou pas.
    Une version alterenative aurait pu etre de ne pas stocker la sous-suite et de rouvrir le fichier a
    chaque appel a is_regexp (car on ne peut pas revenir en arriere une fois un caractere lu).*/

  int file_descriptor = open(file, O_RDONLY);
  if(file_descriptor <= 0){
    printf("Error no such file.\n");
    return; //S'il n'y a pas de fichier => il n'y a pas de regexp donc erreur
  }

  unsigned int line = 1;
  unsigned int count = 0;
  /*Il est plus efficace de stocker la sous-suite dans une liste chainee car sinon chaque nouveau caractere a
    ajouter et enlever pour faire la sous suite suivante couterait O(regexp_len) operations. Cependant nous
    augmentons la taille memoire requise pour stocker un pointeur vers le prochain caratere pour chaque
    caractere. Initialisation de la sous-suite :*/
  subsequence_fl subsequence;
  /*Stocke 0 si on est a la fin du fichier, 1 si on est sur une ligne non entierement lue, 2 sinon.*/
  unsigned char state = init_subsequence(&subsequence, file_descriptor, regexp_len);
  
  while (state){ //Tant que nous n'avons pas lu la fin du fichier.
    if (is_regexp(regexp, subsequence.first)){
      count++;
    }
    state = next_subsequence(&subsequence, state, file_descriptor, regexp_len);
    if (state == 2 || state == 0){
      //Si on change de ligne ou on atteint la fin du fichier => affichage eventuel et on continue.
      if (count){
	printf("Ligne %u, %u fois\n", line, count);
      }
      line++;
      count = 0;
    }
  }
  free_subsequence(subsequence.first);
  close(file_descriptor);
}

int main(){
  char path[100];
  printf("Entrez le nom du fichier dans lequel chercher la phrase : ");
  fgets(path, sizeof(path), stdin);
  erase_EOL(path, sizeof(path));

  printf("Entrez la longueur de votre phrase : ");
  unsigned long len = unsigned_long_input();

  char phrase[len + 1]; //+1 pour le caractere nul
  printf("Entrez la phrase a cherche : ");
  fgets(phrase, sizeof(phrase), stdin);
  phrase[len] = 0; //Force le dernier caractere a nul.
  erase_EOL(phrase, sizeof(phrase));

  //Calcule du nbr d'occurrence par ligne
  printf("Resultat de la recherche :\n");
  print_regexp_occurrence_in_file_by_line(phrase, path, len);
}
