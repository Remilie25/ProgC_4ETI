/* Nom du fichier : main.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif :
     1. realiser une operation entre deux entiers. L'operation et les entiers sont entres par l'utilisateur.
     2. lecture et ecriture de fichiers.
     7. gerer une liste simplement chainee de couleur.
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "user_input.h"
#include "operator.h"
#include "fichier.h"
#include "liste.h"

int main(){
  char exercice[3]; //Trois characteres : 1 pour l'operateur, 1 pour le retour chariot et 1 pour '\0'.
  printf("Entrez le numero de l'exercice que vous voulez faire (1, 2 ou 7) : ");
  fgets(exercice, sizeof(exercice), stdin);

  switch (exercice[0]){//Seul le premier charactere nous interesse.
  case '1':

    //Exercice 1
    int num1, num2;
    char op[3]; //Trois characteres : 1 pour l'operateur, 1 pour le retour chariot et 1 pour '\0'.

    //Recuperation de l'operation a realiser.
    printf("Entrez num1 (int) : ");
    num1 = int_input();
  
    printf("\nEntrez l'operateur (+, -, *, /, %%, &, |, ~) : ");
    fgets(op, sizeof(op), stdin);

    if (op[0] != '~'){//Seul le premier charactere nous interesse.
      printf("\nEntrez num2 (int) : ");
      num2 = int_input();
    }

    faire_operation(&num1, op, &num2);

    printf("Resultat : %d\n", num1);
    break;

  case '2':
    //Exercice 2
    //Lecture ou ecriture dans un fichier.
    char lecture_ou_ecriture[3]; //Trois characteres : 1 pour l'operateur, 1 pour le retour chariot et 1 pour '\0'.
    char path[100]; //Chemin du fichier.
  
    printf("Que souhaitez-vous faire ?\n 1. Lire un fichier\n 2. Ecrire dans un fichier\nVotre choix : ");
    fgets(lecture_ou_ecriture, sizeof(lecture_ou_ecriture), stdin);

    if (*lecture_ou_ecriture == '1'){//Seul le premier charactere nous interesse.
      //Lecture
      printf("Entrez le nom du fichier a lire : ");
      fgets(path, sizeof(path), stdin);
      erase_EOL(path, sizeof(path));
      
      lire_fichier(path);
    }
    else{
      //Ecriture. Si le fichier existe deja, il sera complete (mode APPEND).
      char message[100]; /*Longueur fixee de message. Mais ce n'est pas la longueur maximale du message le
			   plus long. Une boucle while lit tous les characteres jusqu'a ce qu'il n'est plus
			   rien a lire ou que l'ecriture a echoue.
			  */
      unsigned char state = 0; //Stocke la valeur de retour de la fonction ecrire_dans_fichier. 0 <=> pas d'erreur
    
      printf("Entrez le nom du fichier dans lequel vous souhaitez ecrire : ");
      fgets(path, sizeof(path), stdin);
      erase_EOL(path, sizeof(path));
      
      printf("Entrez le message à écrire. Pour signifier la fin du fichier il taper un End-Of-File : CTRL-D sur UNIX sinon CTRL-Z. Entrez votre message : ");

      //Boucle pour recuperer l'ensemble du message.
      while(fgets(message, sizeof(message), stdin) && !state){
	//Tant qu'il reste quelque chose a ecrire et qu'il n'y a pas eu d'erreur d'ecriture
	state = ecrire_dans_fichier(path, message);
      }

      //Il y a-t-il eu une erreur
      if (state){
	printf("Votre message n'a pas pu etre ecrit entierement.\n");
      }
      else{
	printf("Votre message a ete ecrit dans le fichier %s\n", path);
      }
    }
    break;

  case '7' :
    //initialisation du PRNG
    srandom(time(NULL));

    //initialisation de la liste chainee de couleur vide
    couleur_list c_list;
    c_list.couleur_item_pointeur = NULL;

    //Remplissage de la liste.
    couleur database[10];//pour stocker les couleurs crees.

    for (unsigned char indice = 0; indice < 10; indice++){
      database[indice] = couleur_from_long(random());
      insertion(database + indice, &c_list);
    }
    parcours(&c_list);
    free_couleur_list(&c_list);
  }
  
  return 0;
}
