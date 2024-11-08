/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <math.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/epoll.h>

#include "cJSON.h"
#include "serveur.h"
#include "operator.h"

int socketfd;

int visualize_plot()
{
  const char *browser = "firefox";

  char command[256];
  snprintf(command, sizeof(command), "%s %s", browser, svg_file_path);

  int result = system(command);

  if (result == 0)
  {
    printf("SVG file opened in %s.\n", browser);
  }
  else
  {
    printf("Failed to open the SVG file.\n");
  }

  return 0;
}

double degreesToRadians(double degrees)
{
  return degrees * M_PI / 180.0;
}

int plot(cJSON *data)
// Cette fonction affiche les couleurs de data dans un diagrame.
{
  int i;
  cJSON* token;
  cJSON* colours = cJSON_GetObjectItemCaseSensitive(data, "colours");
  cJSON* num_colour_json = cJSON_GetObjectItemCaseSensitive(data, "num_colour");
  unsigned char num_colour;

  if (!cJSON_IsNumber(num_colour_json) || !cJSON_IsNumber(num_colour_json)){
    return 1;
  }
  num_colour = (unsigned char) num_colour_json->valueint;

  double angles[num_colour];
  memset(angles, 0, sizeof(angles));

  FILE *svg_file = fopen(svg_file_path, "w");
  if (svg_file == NULL)
  {
    perror("Error opening file");
    return 1;
  }

  fprintf(svg_file, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
  fprintf(svg_file, "<svg width=\"400\" height=\"400\" xmlns=\"http://www.w3.org/2000/svg\">\n");
  fprintf(svg_file, "  <rect width=\"100%%\" height=\"100%%\" fill=\"#ffffff\" />\n");

  double center_x = 200.0;
  double center_y = 200.0;
  double radius = 150.0;

  double start_angle = -90.0;

  i = 0;

  //Boucle sur toutes les couleurs.
  cJSON_ArrayForEach(token, colours){
    if (!cJSON_IsString(token) || (token->valuestring == NULL)){
      return 1;
    }
    
    angles[i] = 360.0 / num_colour;

    double end_angle = start_angle + angles[i];

    double start_angle_rad = degreesToRadians(start_angle);
    double end_angle_rad = degreesToRadians(end_angle);

    double x1 = center_x + radius * cos(start_angle_rad);
    double y1 = center_y + radius * sin(start_angle_rad);
    double x2 = center_x + radius * cos(end_angle_rad);
    double y2 = center_y + radius * sin(end_angle_rad);

    token->valuestring[strlen(token->valuestring) - 1] = 0; //enleve la virgule
    
    fprintf(svg_file, "  <path d=\"M%.2f,%.2f A%.2f,%.2f 0 0,1 %.2f,%.2f L%.2f,%.2f Z\" fill=\"%s\" />\n",
            x1, y1, radius, radius, x2, y2, center_x, center_y, token->valuestring);

    start_angle = end_angle;
    i++;
  }

  fprintf(svg_file, "</svg>\n");

  fclose(svg_file);

  visualize_plot();
  return 0;
}

/*Code copie du TP5 et modifie pour correspondre aux consignes du TP6*/

int socketfd; // Déclaration globale de socketfd

/**
 * Cette fonction envoie un json au client (client_socket_fd) puis libere le json.
 * @param client_socket_fd : Le descripteur de socket du client.
 * @param json : Le json a envoyer.
 * @return EXIT_SUCCESS en cas de succès, EXIT_FAILURE en cas d'erreur.
 */
int renvoie_message(int client_socket_fd, cJSON* json)
{
  //Convertit le json en string pour l'envoyer.
  char* data = cJSON_PrintUnformatted(json);
  //envoie au client data
  int data_size = write(client_socket_fd, (void *)data, strlen(data));
  //Libere le json et sa convertion en string.
  cJSON_Delete(json);
  free(data);
  

  if (data_size < 0)
  {
    perror("Erreur d'écriture");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

/**
 * Cette fonction lit les données envoyées par le client,
 * et renvoie un message en réponse.
 * @param socketfd : Le descripteur de socket du serveur.
 * @param data : Le message.
 * @return EXIT_SUCCESS en cas de succès, EXIT_FAILURE en cas d'erreur.
 */
int recois_envoie_message(int client_socket_fd, cJSON* data)
{
  cJSON* message = cJSON_GetObjectItemCaseSensitive(data, "message");
  if (cJSON_IsString(message) && (message->valuestring != NULL))
    {
      printf("Message reçu: %s\n", message->valuestring);
    }

  

  // Demande à l'utilisateur d'entrer un message
  char answer[1024];
  printf("Votre message (max 1000 caractères): ");
  fgets(answer, sizeof(answer), stdin);
    
  // Construit le json de reponse
  cJSON* answer_json = cJSON_CreateObject(); //Initialise le json
  
  if (cJSON_AddStringToObject(answer_json, "answer", answer) == NULL ||
      cJSON_AddStringToObject(answer_json, "function", "answer") == NULL){ //Si l'insertion ne marche pas
    cJSON_Delete(answer_json);
    return EXIT_FAILURE;
  }

  return renvoie_message(client_socket_fd, answer_json);
}

/**
 * Cette fonction lit les données envoyées par le client,
 * et renvoie le resultat de l'operation en réponse.
 * @param socketfd : Le descripteur de socket du serveur.
 * @param data : Le json du calcul demande.
 * @return EXIT_SUCCESS en cas de succès, EXIT_FAILURE en cas d'erreur.
 */
int recois_numeros_calcule(int client_socket_fd, cJSON* json)
{
  cJSON *json_op, *json_num1, *json_num2;
  char op;
  int num1;
  int num2 = 0;
  
  //extraction de l'operation
  json_op = cJSON_GetObjectItemCaseSensitive(json, "op");
  json_num1 = cJSON_GetObjectItemCaseSensitive(json, "num1");

  //Calcule de l'operation demandee
  if (cJSON_IsString(json_op) && (json_op->valuestring != NULL) && cJSON_IsNumber(json_num1)){
    op = json_op->valuestring[0];
    num1 = json_num1->valueint;
    if (op != '~'){
      json_num2 = cJSON_GetObjectItemCaseSensitive(json, "num2");
      if (cJSON_IsNumber(json_num2)){
	num2 = json_num2->valueint;
      }
      else{
	return EXIT_FAILURE;
      }
    }
  }
  else{
    return EXIT_FAILURE;
  }
  
  faire_operation(&num1, &op, &num2);
  
  //Construit le json de reponse
  cJSON* answer_json = cJSON_CreateObject(); //Initialise le json

  if (cJSON_AddNumberToObject(answer_json, "answer", num1) == NULL ||
      cJSON_AddStringToObject(answer_json, "function", "answer") == NULL){ //Si l'insertion ne marche pas
    cJSON_Delete(answer_json);
    return EXIT_FAILURE;
  }
      
  return renvoie_message(client_socket_fd, answer_json);
}



/**
 * Gestionnaire de signal pour Ctrl+C (SIGINT).
 * @param signal : Le signal capturé (doit être SIGINT pour Ctrl+C).
 */
void gestionnaire_ctrl_c(int signal)
{
  printf("\nSignal Ctrl+C capturé. Sortie du programme.\n");

  // Fermer le socket si ouvert
  if (socketfd != -1)
  {
    close(socketfd);
  }

  exit(0); // Quitter proprement le programme.
}



/**
 * Gère la communication avec un client spécifique.
 *
 * @param client_socket_fd Le descripteur de socket du client à gérer.
 */
void gerer_client(int client_socket_fd)
{
  char data[1024];

  while (1)
  {
    // Réinitialisation des données
    memset(data, 0, sizeof(data));

    // Lecture des données envoyées par le client
    int data_size = read(client_socket_fd, data, sizeof(data));

    if (data_size <= 0)
    {
      // Erreur de réception ou déconnexion du client
      if (data_size == 0)
      {
        // Le client a fermé la connexion proprement
        printf("Client déconnecté.\n");
      }
      else
      {
        perror("Erreur de réception");
      }

      // Fermer le socket du client et sortir de la boucle de communication
      close(client_socket_fd);
      break; // Sortir de la boucle de communication avec ce client
    }

    //Parse le json. data contient le json sous forme de string
    cJSON* json = cJSON_Parse(data);
    if (json == NULL){ //Si la lecture ne marche pas...
      const char* error_ptr = cJSON_GetErrorPtr();
      if (error_ptr != NULL){
	  fprintf(stderr, "Error before: %s\n", error_ptr);
        }
      return;
    }

    //Recupere la fonction/etiquette de l'action demandee.
    cJSON* etiquette = cJSON_GetObjectItemCaseSensitive(json, "function");
    if (cJSON_IsString(etiquette) && (etiquette->valuestring != NULL)){ //Si etiquette est bien une string
      if (!strncmp(etiquette->valuestring, "message",7)){
	recois_envoie_message(client_socket_fd, json);
      }
      else if (!strncmp(etiquette->valuestring, "calcule",7)){
	recois_numeros_calcule(client_socket_fd, json);
      }
      else if (!strncmp(etiquette->valuestring, "analyse",7)){
	plot(json);
      }
      else{
	printf("L'etiquette %s n'a pas de correspondace.\n", etiquette->valuestring);
	cJSON* answer_json = cJSON_CreateObject();
	if (cJSON_AddStringToObject(answer_json, "error", "La commade saisie n'a pas de correspondace dans notre serveur.\n") == NULL ||
	    cJSON_AddStringToObject(answer_json, "function", "error") == NULL){ //Si l'insertion ne marche pas
	  cJSON_Delete(answer_json);
	  continue;
	}
	renvoie_message(client_socket_fd, answer_json);
	
	//Libere le json
	cJSON_Delete(json);
      }
    }
  }
}


/**
 * Configuration du serveur socket et attente de connexions.
 */

int main()
{

  int bind_status;                // Statut de la liaison
  struct sockaddr_in server_addr; // Structure pour l'adresse du serveur
  int option = 1;                 // Option pour setsockopt

  // Création d'une socket
  socketfd = socket(AF_INET, SOCK_STREAM, 0);

  // Vérification si la création de la socket a réussi
  if (socketfd < 0)
  {
    perror("Impossible d'ouvrir une socket");
    return -1;
  }

  // Configuration de l'option SO_REUSEADDR pour permettre la réutilisation de l'adresse du serveur
  setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

  // Initialisation de la structure server_addr
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);       // Port d'écoute du serveur
  server_addr.sin_addr.s_addr = INADDR_ANY; // Accepter les connexions de n'importe quelle adresse

  // Liaison de l'adresse à la socket
  bind_status = bind(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

  // Vérification si la liaison a réussi
  if (bind_status < 0)
  {
    perror("bind");
    return (EXIT_FAILURE);
  }

  // Enregistrement de la fonction de gestion du signal Ctrl+C
  signal(SIGINT, gestionnaire_ctrl_c);

  // Mise en attente de la socket pour accepter les connexions entrantes jusqu'à une limite de 10 connexions en attente
  listen(socketfd, 10);

  printf("Serveur en attente de connexions...\n");

  struct sockaddr_in client_addr;                     // Structure pour l'adresse du client
  unsigned int client_addr_len = sizeof(client_addr); // Longueur de la structure client_addr
  int client_socket_fd;                               // Descripteur de socket du client

  // Boucle infinie
  while (1)
  {
    // Nouvelle connexion cliente
    client_socket_fd = accept(socketfd, (struct sockaddr *)&client_addr, &client_addr_len);

    if (client_socket_fd < 0)
    {
      perror("accept");
      continue; // Continuer à attendre d'autres connexions en cas d'erreur
    }

    // Créer un processus enfant pour gérer la communication avec le client
    pid_t child_pid = fork();

    if (child_pid == 0)
    {
      // Code du processus enfant
      close(socketfd); // Fermer la socket du serveur dans le processus enfant
      gerer_client(client_socket_fd);
      exit(0); // Quitter le processus enfant
    }
    else if (child_pid < 0)
    {
      perror("fork");
      close(client_socket_fd); // Fermer le socket du client en cas d'erreur
    }
    else
    {
      // Code du processus parent
      close(client_socket_fd); // Fermer le socket du client dans le processus parent
    }
  }

  // Le programme ne devrait jamais atteindre cette ligne dans la boucle infinie
  return 0;
}

