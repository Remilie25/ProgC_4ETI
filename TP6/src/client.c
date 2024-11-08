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

#include "cJSON.h"
#include "client.h"
#include "bmp.h"

//TODO faire le cas ou le serv envoie erreur de commande.


cJSON* analyse(char *pathname, char* color_num_str)
{/* Cette fonction analyse les color_num_str premieres couleurs d'une image se trouvant dans pathname.
    Elle retourne le json rempli des couleurs analysees. Retourne NULL en cas d'erreur.
    color_num_str doit representer un nombre <= 30.*/
  // compte de couleurs
  couleur_compteur *cc = analyse_bmp_image(pathname);
  unsigned char color_num;
  //Si color_num_str vaut NULL alors color_num prend la valeur 10.
  if (!color_num_str || sscanf(color_num_str, "%hhu", &color_num) != 1){
    color_num = 10;
  }

  //Si la valeur est interdite => retour sur la valeur par defaut.
  if (!color_num || color_num > 30){
    color_num = 10;
  }

  //Construit le json a envoyer
  cJSON* json = cJSON_CreateObject();
  if(cJSON_AddStringToObject(json, "function", "analyse") == NULL){
    cJSON_Delete(json);
    return NULL; //erreur
  }
  
  int count;
  char temp_string[10];
  if (cc->size < color_num)
  {
    color_num = cc->size;
  }
  if(cJSON_AddNumberToObject(json, "num_colour", color_num) == NULL){
    cJSON_Delete(json);
    return NULL; //erreur
  }

  //Ajout d'un tableau de couleur (vide au depart)
  cJSON* colours = cJSON_AddArrayToObject(json, "colours");;
  cJSON* colour;

  // choisir color_num couleurs
  for (count = 1; count < color_num + 1 && cc->size - count > 0; count++)
  {
    if (cc->compte_bit == BITS32)
    {
      sprintf(temp_string, "#%02x%02x%02x,", cc->cc.cc24[cc->size - count].c.rouge, cc->cc.cc32[cc->size - count].c.vert, cc->cc.cc32[cc->size - count].c.bleu);
    }
    if (cc->compte_bit == BITS24)
    {
      sprintf(temp_string, "#%02x%02x%02x,", cc->cc.cc32[cc->size - count].c.rouge, cc->cc.cc32[cc->size - count].c.vert, cc->cc.cc32[cc->size - count].c.bleu);
    }
    //Creation et ajout d'une nouvelle couleur
    colour = cJSON_CreateString(temp_string);
    cJSON_AddItemToArray(colours, colour);
  }
  return json;
}

int envoie_couleurs(int socketfd, char *commande)
{
  unsigned short last_char = (unsigned short) strlen(commande) - 1;
  //commande finie par '\0' et unsigned short car commande est definie pour 1024 caracteres
  if (commande[last_char] == '\n'){
    commande[last_char] = 0;
  }
  /*Pour separer la commande par l'espace. Le 1er mot etant la fonction "analyse", le 2e le chemin et le
    3e le nombre de couleurs <= 30.*/
  strtok(commande, " ");
  char* pathname = strtok(NULL, " ");
  char* color_num_str = strtok(NULL, " ");
  cJSON* json = analyse(pathname, color_num_str);

  //Convertion JSON -> string
  char* data = cJSON_PrintUnformatted(json);
  
  // Envoie le message au serveur
  int write_status = write(socketfd, data, strlen(data));
  cJSON_Delete(json);
  free(data);
  if (write_status < 0)
  {
    perror("Erreur d'écriture");
    return -1;
  }

  return 0;
}



/*Code copie du TP5 et modifie pour correspondre aux consignes du TP6*/

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
  cJSON* json = cJSON_CreateObject(); //Initialise le json
  //ajoute l'action demande au serveur. S'il y a une erreur, on libere l'allocation du json.
  if (cJSON_AddStringToObject(json, "function", "message") == NULL){
    cJSON_Delete(json);
    return -1;
  }
  
  /*Si le message a etait entre par la commade, alors il y a un espace puis un caractere non nul
    Si tel est le cas on prepare data. Sinon on demande d'ecrire un message.*/
  if (commande[6] == ' ' && commande[7]){
    if (commande[strnlen(commande, sizeof(commande)) - 1] == '\n'){ // enleve le retour a la ligne
      commande[strnlen(commande, sizeof(commande)) - 1] = 0;
    }
    
    if (cJSON_AddStringToObject(json, "message", commande + 7) == NULL){
      cJSON_Delete(json);
      return -1;
    }
  }
    
  else{
    // Demande à l'utilisateur d'entrer un message
    char message[1024];
    printf("Votre message (max 1000 caractères): ");
    fgets(message, sizeof(message), stdin);
    if (message[strnlen(message, sizeof(message)) - 1] == '\n'){ // enleve le retour a la ligne
      message[strnlen(message, sizeof(message)) - 1] = 0;
    }
    
    if (cJSON_AddStringToObject(json, "message", message) == NULL){
      cJSON_Delete(json);
      return -1;
    }
  }

  //Convertion JSON -> string
  char* data = cJSON_PrintUnformatted(json);
  
  // Envoie le message au serveur
  int write_status = write(socketfd, data, strlen(data));
  cJSON_Delete(json);
  free(data);
  if (write_status < 0)
  {
    perror("Erreur d'écriture");
    return -1;
  }

  // Lit les données de la socket
  char data2[1024];
  int read_status = read(socketfd, data2, sizeof(data2));
  if (read_status < 0)
  {
    perror("Erreur de lecture");
    return -1;
  }

  //Parse le json. data contient le json sous forme de string
  cJSON* answer_json = cJSON_Parse(data2);
  if (answer_json == NULL){ //Si la lecture ne marche pas...
    const char* error_ptr = cJSON_GetErrorPtr();
    if (error_ptr != NULL){
      fprintf(stderr, "Error before: %s\n", error_ptr);
    }
    return -1;
  }

  //Recupere et stocke le resultat.
  cJSON* answer  = cJSON_GetObjectItemCaseSensitive(answer_json, "answer");
  if (cJSON_IsString(answer) && answer->valuestring != NULL){
    // Affiche le message reçu du client
    printf("Message reçu: %s\n", answer->valuestring);
  }
  return 0; // Succès
}

void ajoute_num_data(char* mot, int* num){
  /*Cette fonction convertit en int num representer dans mot.
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
    char data[max_len_int + 1];
    // + 1 pour le caractere nul. nombre sert a extraire la valeur du nombre stocker dans le fichier.
    
    if(fichier > 0){
      if(read(fichier, data, max_len_int)){
	sscanf(mot, "%d", num);
      }
    }
    else{
      printf("Error no such file.\n");
    }
    close(fichier);
  }
  else if (!strncmp(mot, "res", 3)){
    //Teste si l'on reutilise le resultat precedent.
    *num = resultat;
  }
  else{
    //Sinon mot est directement un nonmbre.
    sscanf(mot, "%d", num);
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

  /* Initialise la separation de la commande par le caractere ' '. La fonction ne nous interesse pas, on sait
     deja que c'est calcule*/
  strtok(commande, " ");
  char* mot = strtok(NULL, " "); // Pour continuer a lire la commande mot par mot
  char* op; //Stockera l'emplacement de l'operateur.

  //Si l'utilisateur a rentre la version de calcule avec le ':', on se decale sur l'operateur
  if(mot && mot[0] == ':'){
    mot = strtok(NULL, " ");
  }

  //Si l'utilisateur a demande le calcule d'une moyenne
  if(mot && !strncmp(mot, "moyenne", 7)){
    mot = strtok(NULL, " "); // Pour obtenir le chemin vers le dossier des notes
    mot[strlen(mot) - 1] = '/'; // Pour supprimer le retour chariot et preparer la lecture des notes.
    return moyenne_dossier(socketfd, mot); //On donne la main a moyenne_dossier et on ne va pas plus loin
  }

  //Construction de la requete en json
  cJSON* json = cJSON_CreateObject();
  //ajoute l'action demandee au serveur. S'il y a une erreur, on libere l'allocation du json.
  if (cJSON_AddStringToObject(json, "function", "calcule") == NULL){
    cJSON_Delete(json);
    return -1;
  }

  //Ajoute l'operateur dans le json
  if(mot){
    op = mot;
    if (cJSON_AddStringToObject(json, "op", mot) == NULL){
      cJSON_Delete(json);
      return -1;
    }
    mot = strtok(NULL, " ");
  }

  //Ajoute le premier nombre dans data.
  if(mot){
    int num;
    ajoute_num_data(mot, &num);

    if (cJSON_AddNumberToObject(json, "num1", num) == NULL){
      cJSON_Delete(json);
      return -1;
    }
    mot = strtok(NULL, " ");
  }
  
  //Si l'operateur necessite deux nombres
  if(op && *op != '~' && mot){
    int num;
    ajoute_num_data(mot, &num);

    if (cJSON_AddNumberToObject(json, "num2", num) == NULL){
      cJSON_Delete(json);
      return -1;
    }
  }

  //Convertion JSON -> string
  char* data = cJSON_PrintUnformatted(json);
  
  // Envoie le message au serveur
  int write_status = write(socketfd, data, strlen(data));
  cJSON_Delete(json);
  free(data);
  if (write_status < 0)
  {
    perror("Erreur d'écriture");
    return -1;
  }

  // Lit les données de la socket
  char data2[1024];
  int read_status = read(socketfd, data2, sizeof(data2));
  if (read_status < 0)
  {
    perror("Erreur de lecture");
    return -1;
  }

  //Parse le json. data contient le json sous forme de string
    cJSON* answer_json = cJSON_Parse(data2);
    if (answer_json == NULL){ //Si la lecture ne marche pas...
      const char* error_ptr = cJSON_GetErrorPtr();
      if (error_ptr != NULL){
	  fprintf(stderr, "Error before: %s\n", error_ptr);
        }
      return -1;
    }

    //Recupere et stocke le resultat.
    cJSON* answer  = cJSON_GetObjectItemCaseSensitive(answer_json, "answer");
    if (cJSON_IsNumber(answer)){
      resultat = answer->valueint;
    }

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
    printf("Pas de manuel pour %s.\n", fonction);
    help();
  }
}

void help(){
  //Cette fonction affiche de l'aide
  printf("Entrer :\n'envoie [MESSAGE]' pour envoyer un message.\n'calcule [:] OPERATEUR NUM1 [NUM2]' pour demander le resultat d'un calcul\n'analyse IMAGE [NBR_COULEUR]' pour demander l'analyse d'une image bmp.\n'exit' pour quitter.\n'help' pour afficher ce menu d'aide\n'man COMMANDE' pour avoir eventuellement plus d'aide sur une commande\n");
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
  
  printf("Client CLI 2.0 on linux\nType 'help' for help.\n");
  while (!fermeture_demandee)
  {
    // Demande à l'utilisateur d'entrer une commande
    char commande[1024];
    printf("Client:$ ");
    fgets(commande, sizeof(commande), stdin); // commande finie par '\0' cf "man fgets".

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
    else if(!strncmp(fonction, "analyse", 7)){
      envoie_couleurs(socketfd, commande);
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
