/* Nom du fichier : fichier.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : prototypes pour lire et ecrire dans un fichier
 */

void lire_fichier(char* nom_de_fichier);

unsigned char ecrire_dans_fichier(char* nom_de_fichier, char* message);

void erase_EOL(char* path, unsigned long len);

void clear_file(char* nom_de_fichier);
