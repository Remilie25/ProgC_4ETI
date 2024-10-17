/* Nom du fichier : fichier.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : declaration des fonctions pour lire et ecrire dans un fichier
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void lire_fichier(char* nom_de_fichier){
  //Cette fonction affiche le contenu du fichier du nom_de_fichier.
  int fichier = open(nom_de_fichier, O_RDONLY);
  char charactere;

  if(fichier > 0){
    //Lecture
    printf("Contenu du fichier %s", nom_de_fichier);
    while(read(fichier, &charactere, 1)){
      printf("%c", charactere);
    }
  }
  else{
    printf("Error no such file.\n");
  }
  close(fichier);
}

unsigned char ecrire_dans_fichier(char* nom_de_fichier, char* message){
  int fichier = open(nom_de_fichier, O_CREAT|O_WRONLY|O_APPEND, S_IRUSR|S_IWUSR);
  int len = strnlen(message, 100);
  if (write(fichier, message, len) != len){
    return 1;
  }
  else{
    return 0;
  }
  close(fichier);
}

void erase_EOL(char* str_ptr, unsigned long len){
  /*Cette fonction modifie la chaine de characteres pointee par str_ptr et met un caractere nul au premier
    retour a la ligne rencontree.*/
  unsigned long indice = 0;
  while(indice < len && str_ptr[indice] != '\n' && str_ptr[indice] != 0){
    indice++;
  }
  if (str_ptr[indice] == '\n'){
    str_ptr[indice] = 0;
  }
}

void clear_file(char* nom_de_fichier){
  int fichier = open(nom_de_fichier, O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR);
  close(fichier);
}
