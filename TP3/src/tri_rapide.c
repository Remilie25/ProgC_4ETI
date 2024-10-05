/* Nom du fichier : tri_rapide.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : Function du tri rapide de tableau d'entiers.
 */

#include <stdlib.h>
#include <stdio.h>


int partitionner(int* tab_ptr, unsigned int indice_min, unsigned int indice_max, unsigned int indice_pivot){
  /*Cette fonction est une fonction auxiliaire du tri_rapide. Elle separe le tri sur un tableau en deux tris
    sur un tableau d'element inferieur au pivot et un d'element superieur. Elle renvoie l'indice du pivot.
    Ce tri est effectue en place donc ce sont juste les indices de debut et fin de tableau qui changent.*/

  int tmp = tab_ptr[indice_pivot]; //tmp sert a echanger les valeurs du tab.
  unsigned int indice_fin_tab_inferieur = indice_min; //nom clair
  //Echange des elements en indice "indice_pivot" et "indice_max". On met le pivot a la fin.
  tab_ptr[indice_pivot] = tab_ptr[indice_max];
  tab_ptr[indice_max] = tmp;

  for(unsigned int indice = indice_min; indice <= indice_max - 1; indice++){
    if (tab_ptr[indice] <= tab_ptr[indice_max]){
      //Echange des elements en indice "indice" et "indice_fin_tab_inferieur";
      tmp = tab_ptr[indice];
      tab_ptr[indice] = tab_ptr[indice_fin_tab_inferieur];
      tab_ptr[indice_fin_tab_inferieur] = tmp;
      indice_fin_tab_inferieur++;
    }
  }
  /*Echange des elements en indice "indice_fin_tab_inferieur" et "indice_max". On met le pivot entre la
    partie inferieure et superieure.*/
  tmp = tab_ptr[indice_max];
  tab_ptr[indice_max] = tab_ptr[indice_fin_tab_inferieur];
  tab_ptr[indice_fin_tab_inferieur] = tmp;
  return indice_fin_tab_inferieur;
}

void tri_rapide(int* tab_ptr, unsigned int indice_min, unsigned int indice_max){
  /*Cette fonction effectue le tri de l' "indice_min" a l' "indice_max" d'un tableau d'entier pointe par
    "tab_ptr". Algorithme de tri rapide, variante avec choix du pivot aleatoire.*/
  
  if (indice_min < indice_max){
    unsigned int indice_pivot = (random() % (indice_max - indice_min + 1)) + indice_min;
    indice_pivot = partitionner(tab_ptr, indice_min, indice_max, indice_pivot);

    //Si l'indice pivot vaut 0, la soustraction va mal se passer. On met a 0 pour arreter les appels.
    if (indice_pivot){ 
      tri_rapide(tab_ptr, indice_min, indice_pivot - 1);
    }
    else{
      tri_rapide(tab_ptr, indice_min, 0);
    }
    
    tri_rapide(tab_ptr, indice_pivot + 1, indice_max);
  }
}
