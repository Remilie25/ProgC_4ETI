/* Nom du fichier : operator.h
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : declaration des prototypes d'operateurs
 */

int somme(int num1, int num2);

int difference(int num1, int num2);

int produit(int num1, int num2);

int quotient(int num1, int num2);

int modulo(int num1, int num2);

int et(int num1, int num2);

int ou(int num1, int num2);

int negation(int num1);

void faire_operation(int* num1, char* operator, int* num2);
