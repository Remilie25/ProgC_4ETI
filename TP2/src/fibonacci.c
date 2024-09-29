/* Nom du fichier : fibonacci.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : calcule et affiche les termes de la suite de fibonacci jusqu'a l'indice entre par l'utilisateur.
 */

#include <stdio.h>

int main(){
  const int U_0 = 0;
  const int U_1 = 1;
  int indice = 2;
  int u_n = U_1; //stocke la valeur.
  int u_n_moins_1 = U_0; //stocke la valeur precedante de u_n.
  int tmp; //stocke des valeurs temporaire pour echanger u_n et u_n_moins_1

  /*recupere un entier rentre par l'utilisateur en evitant des debordements.
   sizeof(int) * 4 * 3/ 10 + 4 est superieure au nombre de carateres maximal pour un nombre representable par int.*/
  printf("Entrez l'indice d'arret du calcul de la suite de fibonacci (nombre sur un int) : ");
  char num_str[(sizeof(int) * 4 * 3 / 10 ) + 4];
  int num;
  fgets(num_str, sizeof(num_str), stdin);
  sscanf(num_str, "%d", &num);

  //affichage des deux premiers termes
  if (num >= 0){
    printf("Le terme 0 de la suite de fibonacci est 0.\n");
  }

  if (num >= 1){
    printf("Le terme 1 de la suite de fibonacci est 1.\n");
  }

  //calcul et affichage des termes suivant (jusqu'a intdice > num).
  for (;indice <= num; indice++){
    tmp = u_n;
    u_n += u_n_moins_1;
    u_n_moins_1 = tmp;
    printf("Le terme %d de la suite de fibonacci est %d.\n", indice, u_n);
  }
  
  return 0;
}
