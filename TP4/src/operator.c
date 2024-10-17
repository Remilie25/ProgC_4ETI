/* Nom du fichier : operator.h
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : declaration des fonctions des operateurs. Les operateurs realisent l'operation qui est leur nom.
 */


int somme(int num1, int num2){
  return num1 + num2;
}

int difference(int num1, int num2){
  return num1 - num2;
}

int produit(int num1, int num2){
  return num1 * num2;
}

int quotient(int num1, int num2){
  return num1 / num2;
}

int modulo(int num1, int num2){
  return num1 % num2;
}

int et(int num1, int num2){
  return num1 & num2;
}

int ou(int num1, int num2){
  return num1 | num2;
}

int negation(int num1){//Pas de sens de prendre deux parametres !
  return ~num1;
}

void faire_operation(int* num1, char* operator, int* num2){
  //Cette fonction realise l'operation demadee et stocke le resultat dans num1 avant affichage.
  //num1 et num2 sont des pointeurs vers un int sur lesquels on realise l'operation pointee par operateur.
  switch (*operator){
  case '+' :
    *num1 = somme(*num1, *num2);
    break;
    
  case '-' :
    *num1 = difference(*num1, *num2);
    break;
    
  case '*' :
    *num1 = produit(*num1, *num2);
    break;
    
  case '/' :
    *num1 = quotient(*num1, *num2);
    break;
    
  case '%' :
    *num1 = modulo(*num1, *num2);
    break;
    
  case '&' :
    *num1 = et(*num1, *num2);
    break;
    
  case '|' :
    *num1 = ou(*num1, *num2);
    break;
    
  case '~' :
    *num1 = negation(*num1);
    break;
  }
}
