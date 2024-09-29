/* Nom du fichier : ptrvariables.c
   Auteurs : Bourges Vincent, de Pretto Remi
   Objectif : creer et affiche une variable et un pointeur de chaque type de base.
 */

#include <stdio.h>

void print_addr_val(unsigned short* a_ptr, short* b_ptr, unsigned int* c_ptr, int* d_ptr, unsigned long* e_ptr,
		    long* f_ptr, unsigned long long* g_ptr, long long* h_ptr, float* i_ptr, double* j_ptr,
		    long double* k_ptr, unsigned char* l_ptr, char* m_ptr){
  //Cette fonciton affiche l'adresse et la valeur de chaque pointer en hexadecimal.

  //Affichage des types entiers
  printf("Adresse de a : %p, Valeur de a : %hx\nAdresse de b : %p, Valeur de b : %hx\nAdresse de c : %p, Valeur de c : %x\nAdresse de d : %p, Valeur de d : %x\nAdresse de e : %p, Valeur de e : %lx\nAdresse de f : %p, Valeur de f : %lx\nAdresse de g : %p, Valeur de g : %llx\nAdresse de h : %p, Valeur de h : %llx\n",
	 a_ptr, *a_ptr, b_ptr, *b_ptr, c_ptr, *c_ptr, d_ptr, *d_ptr, e_ptr, *e_ptr, f_ptr, *f_ptr, g_ptr,
	 *g_ptr, h_ptr, *h_ptr);
  
  /*Pour les nombres a virgule flottante il faut acceder a leurs valeurs octect par octect. Sinon printf ne
    sait pas les afficher en hexadecimal. Ici ne marche que avec sizeof(char) = 1, sinon aucun garantie.*/
  union flottant{
    float num;
    char octect_num[sizeof(float)];
  };
  
  union double_flottant{
    double num;
    char octect_num[sizeof(double)];
  };

  union long_flottant{
    long double num;
    char octect_num[sizeof(long double)];
  };

  union flottant i;
  union double_flottant j;
  union long_flottant k;

  i.num = *i_ptr;
  j.num = *j_ptr;
  k.num = *k_ptr;
  
  //Affichage des types a virgules flottantes.
  const short sizeof_float= (short) sizeof(float);
  const short sizeof_double = (short) sizeof(double);
  const short sizeof_long_double = (short) sizeof(long double);
  short indice = 1;
  
  //float
  printf("Adresse de i : %p, Valeur de i : %02hhx", i_ptr, i.octect_num[0]);
  for(; indice < sizeof_float; indice++){
    printf("%02hhx", i.octect_num[indice]);
  }

  //double
  printf("\nAdresse de j : %p, Valeur de j : %02hhx", j_ptr, j.octect_num[0]);
  for(indice = 1; indice < sizeof_double; indice++){
    printf("%02hhx", j.octect_num[indice]);
  }

  //long double
  printf("\nAdresse de k : %p, Valeur de k : %02hhx", k_ptr, k.octect_num[0]);
  for(indice = 1; indice < sizeof_long_double; indice++){
    printf("%02hhx", k.octect_num[indice]);
  }
  
  //Affichage des types char.
  printf("\nAdresse de l : %p, Valeur de l : %hhx\nAdresse de m : %p, Valeur de m : %hhx\n", l_ptr, *l_ptr, m_ptr, *m_ptr);

}

int main() {
  //Definition d'une variable de chaque type 
  unsigned short a = 25;
  short b = -20;
  unsigned int c = 30;
  int d = -40;
  unsigned long e = 50ul;
  long f = 0xfffffl;
  unsigned long long g = 70ull;
  long long h = 0x12345678;
  float i = 80.08164;
  double j = 9E1;
  long double k = 1E10;
  unsigned char l = 'a';
  char m = 'b';

  //Definition de leurs pointeurs
  unsigned short* a_ptr = &a;
  short* b_ptr = &b;
  unsigned int* c_ptr = &c;
  int* d_ptr = &d;
  unsigned long* e_ptr = &e;
  long* f_ptr = &f;
  unsigned long long* g_ptr = &g;
  long long* h_ptr = &h;
  float* i_ptr = &i;
  double* j_ptr = &j;
  long double* k_ptr = &k;
  unsigned char* l_ptr = &l;
  char* m_ptr = &m;

  //affichage de l'etat initial
  printf("Etat initial :\n");
  print_addr_val(a_ptr, b_ptr, c_ptr, d_ptr, e_ptr, f_ptr, g_ptr, h_ptr, i_ptr, j_ptr, k_ptr, l_ptr, m_ptr);

  //modification
  *a_ptr = 10;
  *b_ptr = -10;
  *c_ptr = 590;
  *d_ptr = -590;
  *e_ptr = 1000000;
  *f_ptr = -1000000;
  *g_ptr = 25;
  *h_ptr = -50;
  *i_ptr = 50.238;
  *j_ptr = 59053.99934;
  *k_ptr = -3425893.5234809;
  *l_ptr = 43;
  *m_ptr = 'z';

  //affichage apres modif
  printf("\nApres modif :\n");
  print_addr_val(a_ptr, b_ptr, c_ptr, d_ptr, e_ptr, f_ptr, g_ptr, h_ptr, i_ptr, j_ptr, k_ptr, l_ptr, m_ptr);
}
