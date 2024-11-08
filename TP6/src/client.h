/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef __CLIENT_H__
#define __CLIENT_H__

/*
 * port d'ordinateur pour envoyer et recevoir des messages
 */
#define PORT 8089

/*
 * Fonction d'envoi et de réception de messages
 * Il faut un argument : l'identifiant de la socket
 */
int envoie_recois_message(int socketfd, char* commande);

void ajoute_num_data(char* mot, int* num);

int moyenne(int socketfd, char* chemin_dossier);

int envoie_operateur_numeros(int socketfd, char* commande, unsigned char display);

void man(char* cmd);

void help();

void fonction_inconnue();

int envoie_couleurs(int socketfd, char *commande);

cJSON* analyse(char *pathname, char* color_num_str);

#endif
