/* Nom du fichier : repertoire.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : afficher les fichiers et repertoires dans un repertoires
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include "repertoire.h"

void lire_dossier(const char* chemin_dossier){
  /*Cette fonction affiche les fichiers et dossiers dans le dossier au chemin chemin_dossier. Les fichiers
    caches (commencant par ".") sont pas affiches.*/
  DIR* dossier_ptr = opendir(chemin_dossier);
  errno = 0;
  if (dossier_ptr){
    //Si le dossier a ete ouvert
    struct dirent* dossier = readdir(dossier_ptr);

    while (dossier){
      if (dossier->d_name[0] != '.'){
	printf("%s\t", dossier->d_name);
      }
      dossier = readdir(dossier_ptr);
    }
    printf("\n");
    
  }else{
    printf("Dossier non trouve.\n");
    printf("Err : %s\n", strerror(errno));
  }
}

unsigned char insert_queue(char* str, unsigned long len, str_queue* queue){
  /*Cette fonction insere str a la fin de la queue. Renvoie 1 si erreur sinon 0. Elle copie str dans le nouvel
    element.*/
  str_list* new_item = (str_list*) calloc(1, sizeof(str_list));
  char* new_str = (char*) malloc(len + 1);
  if (new_item && new_str){
    strncat(new_str, str, len); //copie str dans new_str
    new_item->str = new_str;
    new_item->len = len;
    if (queue->last){
      queue->last->next_str = new_item;
    }
    queue->last = new_item;
    return 0; 
  }
  return 1;
}

void free_first(str_queue* queue){
  //Cette fonction libere le premier element de queue.
  str_list* tmp = queue->first;
  queue->first = tmp->next_str;
  
}

void print_queue(str_queue* queue){
  //Cette fonction affiche la queue
  str_list* list = queue->first;
  while (list){
    printf("%s\n",list->str);
    list = list->next_str;
  }
}

void lire_dossier_recursif(char* chemin_dossier){
  /*Cette fonction affiche les fichiers et dossiers de l'abre enracine au dossier donne par chemin_dossier.
    Les fichiers caches (commencant par ".") sont pas affiches. Algo : parcours en largeur recursif.
    Imite la fonction ls mais ne trie pas (l'ordre d'affichage est dicte par readdir).*/

  void auxiliaire(str_queue* queue){
    /*Cette fonction sert a avoir la queue en parametre et que lire_dossier_recursif prenne que le chemin en
      entree comme le veut la consigne. La queue sert a faire le parcours en largeur.*/

    if (queue->first){
      /*S'il reste un dossier a afficher son contenu.
	Les fichiers non pas de sous fichiers ou sous dossiers, ils seront rejetes par opendir.*/
    
      DIR* dossier_ptr = opendir(queue->first->str);
      if (dossier_ptr){
	//Si le dossier a ete ouvert
	struct dirent* dossier = readdir(dossier_ptr);

	if(dossier){
	  printf("%s:\n", queue->first->str);
	}

	while (dossier){
	  //Tant qu'il y a un fichier ou un dossier : l'afficher et l'ajouter dans la queue.
	  if (dossier->d_name[0] != '.'){
	    //Affichage
	    printf("%s\t", dossier->d_name);
	    //Mise a jour de la queue avec le nouveau chemin a afficher
	    unsigned short d_name_len = (unsigned short) strnlen(dossier->d_name, 256);
	    //limite a 256 car dans la doc d_name est sur 256 octets. d_name est cense finir par un caratere nul
	    unsigned long path_len = d_name_len + queue->first->len;
	    if ((path_len + 1) < queue->first->len){
	      printf("Le nouveau chemin est trop long. Depassement des unsigned long.");
	      return;
	    }

	    //Est-ce que le '/' est deja present ou a ajouter ? => ajustement de la longueur
	    if (queue->first->str[queue->first->len - 1] != '/'){
	      path_len++;
	      if (!(path_len + 1)){
		printf("Le nouveau chemin est trop long. Depassement des unsigned long.");
		return;
	      }
	    }
	    char path[path_len + 1]; //nouveau chemin. +1 pour le caractere nul
	    strncpy(path, queue->first->str, queue->first->len);
	    path[queue->first->len] = 0; // Pour s'assurer que path termine par le caractere nul.

	    //Est-ce que le '/' est deja present ou a ajouter ?
	    if (queue->first->str[queue->first->len - 1] != '/'){
	      path[queue->first->len] = '/';
	      path[queue->first->len + 1] = 0; // Pour s'assurer que path termine par le caractere nul.
	    }
	    strncat(path, dossier->d_name, d_name_len);
	  
	    insert_queue(path, path_len, queue);
	  }
	  dossier = readdir(dossier_ptr);
	}
	//On vient de finir le premier element donc on l'enleve
	printf("\n\n");
      }
      free_first(queue);
      auxiliaire(queue);
    }
  }

  str_queue queue;
  queue.last = NULL;
  //Pour que l'insertion marche (sinon il n'y aura pas de fin de chaine marque par un pointeur nul).
  insert_queue(chemin_dossier, strlen(chemin_dossier), &queue);
  /*strlen au lieu de strnlen car le sujet ne permet pas d'ajouter en parametre la longueur. De toute facon,
    le chemin_dossier vient de argv qui met des char* finis par un caratere nul.*/
  queue.first = queue.last;
  
  auxiliaire(&queue);
}


void lire_dossier_iteratif(char* chemin_dossier){
  /*Cette fonction affiche les fichiers et dossiers de l'abre enracine au dossier donne par chemin_dossier.
    Les fichiers caches (commencant par ".") sont pas affiches. Algo : parcours en largeur iteratif.
    Imite la fonction ls mais ne trie pas (l'ordre d'affichage est dicte par readdir).*/

  str_queue s_queue;
  str_queue* queue = &s_queue;
  
  queue->last = NULL;
  //Pour que l'insertion marche (sinon il n'y aura pas de fin de chaine marque par un pointeur nul).
  insert_queue(chemin_dossier, strlen(chemin_dossier), queue);
  /*strlen au lieu de strnlen car le sujet ne permet pas d'ajouter en parametre la longueur. De toute facon,
    le chemin_dossier vient de argv qui met des char* finis par un caratere nul.*/
  queue->first = queue->last;
  
  while (queue->first){
    /*S'il reste un dossier a afficher son contenu.
      Les fichiers non pas de sous fichiers ou sous dossiers, ils seront rejetes par opendir.*/
    
    DIR* dossier_ptr = opendir(queue->first->str);
    if (dossier_ptr){
      //Si le dossier a ete ouvert
      struct dirent* dossier = readdir(dossier_ptr);

      if(dossier){
	printf("%s:\n", queue->first->str);
      }

      while (dossier){
	//Tant qu'il y a un fichier ou un dossier : l'afficher et l'ajouter dans la queue.
	if (dossier->d_name[0] != '.'){
	  //Affichage
	  printf("%s\t", dossier->d_name);
	  //Mise a jour de la queue avec le nouveau chemin a afficher
	  unsigned short d_name_len = (unsigned short) strnlen(dossier->d_name, 256);
	  //limite a 256 car dans la doc d_name est sur 256 octets. d_name est cense finir par un caratere nul
	  unsigned long path_len = d_name_len + queue->first->len;
	  if ((path_len + 1) < queue->first->len){
	    printf("Le nouveau chemin est trop long. Depassement des unsigned long.");
	    return;
	  }

	  //Est-ce que le '/' est deja present ou a ajouter ? => ajustement de la longueur
	  if (queue->first->str[queue->first->len - 1] != '/'){
	    path_len++;
	    if (!(path_len + 1)){
	      printf("Le nouveau chemin est trop long. Depassement des unsigned long.");
	      return;
	    }
	  }
	  char path[path_len + 1]; //nouveau chemin. +1 pour le caractere nul
	  strncpy(path, queue->first->str, queue->first->len);
	  path[queue->first->len] = 0; // Pour s'assurer que path termine par le caractere nul.

	  //Est-ce que le '/' est deja present ou a ajouter ?
	  if (queue->first->str[queue->first->len - 1] != '/'){
	    path[queue->first->len] = '/';
	    path[queue->first->len + 1] = 0; // Pour s'assurer que path termine par le caractere nul.
	  }
	  strncat(path, dossier->d_name, d_name_len);
	  
	  insert_queue(path, path_len, queue);
	}
	dossier = readdir(dossier_ptr);
      }
      //On vient de finir le premier element donc on l'enleve
      printf("\n\n");
    }
    free_first(queue);
  }
}


