/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>

#include "client.h"

int resultat = 0; //Pour stocker le dernier resultat du calcul demande au serveur.

/**
 * Fonction pour envoyer et recevoir un message depuis un client connecté à la socket.
 *
 * @param socketfd Le descripteur de la socket utilisée pour la communication.
 * @paran commande : la commande rentree.
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int envoie_recois_message(int socketfd, char* commande)
{
  char data[1024] = "message: "; //Initialisation avec l'etiquette "message: "

  /* Initialise la separation de la commande par le caractere ' '. La fonction ne nous interesse pas, on sait
     deja que c'est calcule*/
  strtok(commande, " "); 
  char* mot = strtok(NULL, " "); // Pour continuer a lire la commande mot par mot

  //Si le message a etait entre par la commade, on prepare data. Sinon on demande d'ecrire un message.
  if (mot){
    // Construit le message
    while(mot){
      strcat(data, mot); //strcat ne debordera pas car strtok renvoie des char* finissant par '\0'
      strcat(data, " ");
      mot = strtok(NULL, " ");
  }
    
  }else{
    // Demande à l'utilisateur d'entrer un message
    char message[1024];
    printf("Votre message (max 1000 caractères): ");
    fgets(message, sizeof(message), stdin);
    
    // Construit le message
    strcat(data, message);
  }

  // Envoie le message au client
  int write_status = write(socketfd, data, strlen(data));
  if (write_status < 0)
  {
    perror("Erreur d'écriture");
    return -1;
  }

  // Réinitialisation de l'ensemble des données
  memset(data, 0, sizeof(data));

  // Lit les données de la socket
  int read_status = read(socketfd, data, sizeof(data));
  if (read_status < 0)
  {
    perror("Erreur de lecture");
    return -1;
  }

  // Affiche le message reçu du client
  printf("Message reçu: %s\n", data);

  return 0; // Succès
}

void ajoute_num_data(char* mot, char* data){
  /*Cette fonction ajoute num a data, la chaine de caractere a envoyer au serveur.
    Cependant des mots speciaux sont remplaces :
    'res' est remplace par la valeur de la variable globale resultat
    'chemin_vers_dossier/fichier_contenant_une_valeur.txt' est remplacer par la valeur de ce fichier.
    mot doit finir par un caractere nul.*/

  if (strchr(mot, '/')){
    //Teste si un slash se trouve dans mot se qui signifie que c'est un chemin vers un fichier.
    int fichier = open(mot, O_RDONLY);
    const unsigned long max_len_int = (sizeof(int) * 4 * 3 / 10 ) + 4;
    /*sizeof(int) * 4 * 3/ 10 + 4 est superieure au nombre de carateres maximal pour un nombre representable
      par int.*/
    int num; //le numero convertit en int
    char nombre[max_len_int + 1];
    // + 1 pour le caractere nul. nombre sert a extraire la valeur du nombre stocker dans le fichier.

    if(fichier > 0){
      if(read(fichier, nombre, max_len_int)){
	/*Extrait un entier du fichier ouvert.
	  Bien que la double convertion ait l'air inutile, elle nous debarasse de tous les problemes en
	  forcant le nombre sous forme de chaine de caractere soit un int. Et nous enleve le retour chariot.*/
	sscanf(nombre, "%d", &num);
	sprintf(nombre, "%d", num);
	strncat(data, nombre, max_len_int);
      }
    }
    else{
      printf("Error no such file.\n");
    }
    close(fichier);
  }
  else if (!strncmp(mot, "res", 3)){
    //Teste si l'on reutilise le resultat precedent.
    const unsigned long max_len_int = (sizeof(int) * 4 * 3 / 10 ) + 4;
    char nombre[max_len_int + 1];
    sprintf(nombre, "%d", resultat);
    strncat(data, nombre, max_len_int);
  }
  else{
    //Sinon mot est directement un nonmbre.
    strcat(data, mot);
  }
  
}

/**
 * Fonction pour calculer la moyenne des notes d'un eleve. Utilise envoie_operateur_numeros.
 *
 * @param socketfd Le descripteur de la socket utilisée pour la communication.
 * @paran commande : la commande rentree.
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int moyenne_dossier(int socketfd, char* chemin_dossier){
  /*Cette fonciton calcule la moyenne d'un eleve. commande doit respecter le template :
    calcule [:] moyenne ./dossier_de_notes
    chemin_dossier doit finir par le caractere nul. Il ne doit contenir que des fichiers textes.
    Elle returne 0 en cas de succès, -1 en cas d'erreur.*/

  resultat = 0;//reinitialise le resultat pour calculer la moyenne
  char commande[1024];
  //Pour stocke la commande avec laquelle on va appeler envoie_operateur_numeros.
  const char cmd_prefixe[] = "f + res ";
  /*f ne ser a rien. En temps normal il y aurait 'calcule' entree par l'utilisateur mais ici c'est moyenne
    qui appelle. Il faut juste que le template envoie_operateur_numeros de soit respecter (cf man calcule).
    Puis nous voulons sommer les notes d'ou '+ res' pour faire la somme de la somme partielle et de la
    derniere notes.*/
  int n = 0;
  /* Compte le nombre de note. On divisera leur somme par n. int car envoie_operateur_numeros ne prend que
     des int en entree*/
  
  DIR* dossier_ptr = opendir(chemin_dossier);
  errno = 0;
  if (dossier_ptr){
    //Si le dossier a ete ouvert
    struct dirent* fichier = readdir(dossier_ptr);

    while (fichier){//Tant qu'on a pas parcouru tout le repertoire
      if (fichier->d_type == DT_REG){//Si le fichier est un fichier (ce pourrait etre un repertoire)
	strncpy(commande, cmd_prefixe, sizeof(commande));
	strcat(commande, chemin_dossier); // dossier fini par le caractere nul.
	strcat(commande, fichier->d_name); // fichier->d_name fini par le caractere nul.
	envoie_operateur_numeros(socketfd, commande, 0);
	n++;
	if (n < 0){
	  printf("Depassement des entiers.");
	  return -1;
	}
      }
      fichier = readdir(dossier_ptr);
    }
    
    //Division par le nombre de notes pour obtenir la moyenne
    sprintf(commande, "f / res %d", n);
    envoie_operateur_numeros(socketfd, commande, 0);
    printf("%d\n", resultat);
    
    return 0;
    
  }else{
    printf("Dossier non trouve.\n");
    printf("Err : %s\n", strerror(errno));
    return -1;
  }
}




/**
 * Fonction pour envoyer et recevoir un calcul depuis un client connecté à la socket.
 *
 * @param socketfd Le descripteur de la socket utilisée pour la communication.
 * @paran commande : la commande rentree.
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int envoie_operateur_numeros(int socketfd, char* commande, unsigned char display){
  /*Cette fonction demande au serveur d'effectuer un calcul. Le calcul est dans la commande. display est nul
    si on ne veut pas d'affichage sinon la fonciton affiche le resulatat.*/

  char data[1024] = "calcule: ";
  
  //Initialisation avec l'etiquette "calcule: ". op pointe vers l'operateur (qui sera ajoute par la suite).
  char* op = data + strlen(data);

  /* Initialise la separation de la commande par le caractere ' '. La fonction ne nous interesse pas, on sait
     deja que c'est calcule*/
  strtok(commande, " ");
  char* mot = strtok(NULL, " "); // Pour continuer a lire la commande mot par mot

  //Si l'utilisateur a rentre la version de calcule avec le ':', on se decale sur l'operateur
  if(mot && mot[0] == ':'){
    op += 2; //Il y a obligatoirement un espace entre ':' et la suite. Voir help.
    mot = strtok(NULL, " ");
  }

  //Si l'utilisateur a demande le calcule d'une moyenne
  if(mot && !strncmp(mot, "moyenne", 7)){
    mot = strtok(NULL, " "); // Pour obtenir le chemin vers le dossier des notes
    mot[strlen(mot) - 1] = '/'; // Pour supprimer le retour chariot et preparer la lecture des notes.
    return moyenne_dossier(socketfd, mot); //On donne la main a moyenne_dossier et on ne va pas plus loin
  }


  //Ajoute l'operateur dans data. op pointe bien vers l'emplacement de l'operateur.
  if(mot){
    strcat(data, mot); //strcat ne debordera pas car strtok renvoie des char* finissant par '\0'
    strcat(data, " ");
    mot = strtok(NULL, " ");
  }

  //Ajoute le premier nombre dans data.
  if(mot){
    ajoute_num_data(mot, data);
    strcat(data, " ");
    mot = strtok(NULL, " ");
  }
  
  //Si l'operateur necessite deux nombres
  if(op && *op != '~' && mot){
    ajoute_num_data(mot, data);
  }

  // Envoie le message au serveur
  int write_status = write(socketfd, data, strlen(data));
  if (write_status < 0)
  {
    perror("Erreur d'écriture");
    return -1;
  }

  // Réinitialisation de l'ensemble des données
  memset(data, 0, sizeof(data));

  // Lit les données de la socket
  int read_status = read(socketfd, data, sizeof(data));
  if (read_status < 0)
  {
    perror("Erreur de lecture");
    return -1;
  }

  //Stocke le resultat
  int resultat_tmp;
  char etiquette[10];

  if (sscanf(data, "%7s: %d", etiquette, &resultat_tmp) != 2){
    printf("sscanf failed\n");
    return -1;
  }  
  if (strncmp(etiquette, "calcule",7)){
    printf("Erreur d'etiquette");
    return -1;
  }

  resultat = resultat_tmp; //Sauvegarde le resultat

  // Affiche le message reçu du client si display != 0
  if (display){
    printf("%d\n", resultat);
  }

  return 0; // Succès
}

void man(char* cmd){
  //Cette fonciton affiche de le manuel d'une commande ou appelle help() si pas de manuel
  strtok(cmd, " "); //separe cmd en mot. Le premier etant 'man'
  char* fonction = strtok(NULL, " ");
  if (!strncmp(fonction, "calcule", 7)){
    printf("NAME\ncalcule\n\nSYNOPSIS\ncalcule OPERATEUR NUM1 [NUM2]\ncalcule [:] moyenne CHEMIN_VERS_DOSSIER_DE_NOTES\n\nDESCRIPTION\n'calcule' calcule l'operation decrite par l'OPERATEUR sur NUM1 et eventuellement NUM2.\n");
    printf("Elle affiche le resultat. OPERATEUR est un operateur parmi {+, -, *, /, %%, |, &, ~}.\n");
    printf("NUM1 et NUM2 sont des nombres entiers sur %lu bits. Pour attribuer une valeur a NUM1\n", sizeof(int));
    printf("ou NUM2 a partir d'un fichier '.txt', il suffit de donner son chemin d'acces. Ils peuvent\n");
    printf("aussi prendre une valeur speciale qui est 'rep' pour le resultat du dernier calcule.\n");
    printf("CHEMIN_VERS_DOSSIER_DE_NOTES est un chemin vers un dossier de notes dans des fichiers '.txt'\n\nRETURN\nrien\n\nEXAMPLES\ncalcule + 1 2\ncalcule - chemin_vers_dossier/valeur_de_num.txt res\ncalcule / res 5\n");
    }
  else{
    printf("Commande %s non reconnue.\n", fonction);
    help();
  }
}

void help(){
  //Cette fonction affiche de l'aide
  printf("Entrer :\n'envoie [MESSAGE]' pour envoyer un message.\n'calcule [:] OPERATEUR NUM1 [NUM2]' pour demander le resultat d'un calcul\n'exit' pour quitter.\n'help' pour afficher ce menu d'aide\n'man COMMANDE' pour avoir eventuellement plus d'aide sur une commande\n");
}

void fonction_inconnue(){
  //Affiche un message d'erreur car la fonction n'est pas reconnue
  printf("Commande inconnue. Essayer 'help' pour obtenir de l'aide.\n");
}

int main()
{
  int socketfd;

  struct sockaddr_in server_addr;

  /*
   * Creation d'une socket
   */
  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd < 0)
  {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  // détails du serveur (adresse et port)
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  // demande de connection au serveur
  int connect_status = connect(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (connect_status < 0)
  {
    perror("connection serveur");
    exit(EXIT_FAILURE);
  }

  unsigned char fermeture_demandee = 0;
  
  printf("Client CLI 1.0 on linux\nType 'help' for help.\n");
  while (!fermeture_demandee)
  {
    // Demande à l'utilisateur d'entrer une commande
    char commande[1024];
    printf("Client:$ ");
    fgets(commande, sizeof(commande), stdin);

    // Separe la commande par le le caractere ' ' (remplace les ' ' par des '\0')
    char fonction[10];
    sscanf(commande, "%9c ", fonction); 

    // Appelle de la fonction correspondant a la commande
    if(!strncmp(fonction, "envoie", 6)){
      envoie_recois_message(socketfd, commande);
    }
    else if(!strncmp(fonction, "calcule", 7)){
      envoie_operateur_numeros(socketfd, commande, 1);
    }
    else if(!strncmp(fonction, "help", 4)){
      help();
    }
    else if(!strncmp(fonction, "man", 3)){
      man(commande);
    }
    else if(!strncmp(fonction, "exit", 4)){
      fermeture_demandee = 1;
    }
    else{
      fonction_inconnue();
    }
    
    
  }

  close(socketfd);
  return 0;
}
