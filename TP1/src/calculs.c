/* Nom du fichier : calculs.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : realiser l'operation stocker dans op sur num1 et num2 : num1 (op) num2
 */

#include <stdio.h>


int main(){
  int num1 = 10; //num1 prendra le resultat de l'operation.
  int num2 = 25;
  char op = '%';
  switch (op){
  case '+' :{
    num1 += num2;
    break;
  }
  case '-' :{
    num1 -= num2;
    break;
  }
  case '*' :{
    num1 *= num2;
    break;
  }
  case '/' :{
    num1 /= num2;
    break;
  }
  case '%' :{
    num1 %= num2;
    break;
  }
  case '&' :{
    num1 &= num2;
    break;
  }
  case '|' :{
    num1 |= num2;
    break;
  }
  case '~' :{
    num1 = ~num1;
    break;
  }
  }
  printf("Resusltat de l'operation : %d\n", num1);
  return 0;
}
