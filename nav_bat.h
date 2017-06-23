/*
        Implementacao em C do jogo Batalha Naval
        Codigo para fins academicos
*/

/* Bibliotecas utilizadas */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

/* Variaveis globais */
// Naves
#define CORVETA 2
#define SUBMARINO 3
#define FRAGATA 4
#define CRUZADOR 5
#define PORTA_AVIAO 6

#define BARCOS {"Corveta","Submarino","Fragata","Cruzador","Porta Aviões"}

/* Defincoes */
// Definição do sistema operacional
#ifdef defined(__WIN32__) || defined(__NT__)
#    define WINDOWS
#  endif

#if defined(__linux__) || defined(__linux)
#  define LINUX
#endif

#if defined(__APPLE__)
#  define OSX
#endif

// Simplifacacao de funcoes
#define loop(i,a) for(i=0;i<a;i++)

/* Funcoes */
// Identifica qual sistema esta sendo usado
void sistema();

// Imprime uma tabela numerica com a borda alfabetica
void print_board(int **matriz,int tam);

// Imprime uma tabela com os valores ocultos
void print_mask(int **matriz, int tam);


// Le um caractere da tela de forma segura
int read_char (char i, char f);




// funcoes antigas
void imprime_matriz();

void imprime_cpu();

void imprime_mascara();

void imprime_jogo();

int isere_barco (int barco, int y, int x, int dir, int matrizInsere[10][10]);

void preenche_barcos();

void preenche_cpu();

int player_joga (int *barcos);

int cpu_joga (int *barcos);

int jogar ();
