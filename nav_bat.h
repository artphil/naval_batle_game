/*
        Implementacao em C do jogo Batalha Naval
        Codigo para fins academicos
*/

/* Bibliotecas utilizadas */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

/* Definicao de ariaveis globais constantes */

/*      Naves
Nome            Tamanho
Corveta         2
Submarino       3
Fragata         4
Cruzador        5
Porta Aviões    6
*/

#define QTD_BARCOS 5

const int max_barcos[3][QTD_BARCOS] = {
        {1,1,1,1,0},
        {2,2,2,1,1},
        {3,3,2,2,1}
};

const char *nome_barcos[] = {
        "Corveta",
        "Submarino",
        "Fragata",
        "Cruzador",
        "Porta Aviões"
};


// Tabuleiro
#define NAVE  'H'
#define AGUA  '0'
#define VAZIO '.'

const int tam_mesa[] = {8,10,12};

/* Defincoes */
// Definição do sistema operacional
#if defined(__linux__) || defined(__linux)
        #define LINUX
#endif

#if defined(__APPLE__)
        #define OSX
#endif

#ifdef defined(__WIN32__) || defined(__NT__)
        #define WINDOWS
#endif

// Simplifacacao de funcoes
#define loop(i,a) for(i=0;i<a;i++)

/* Funcoes */
// Identifica qual sistema esta sendo usado
void sistema();

//
char **init_board(char a);

// Imprime uma tabela numerica com a borda alfabetica
void print_board(char **matriz);

// Le um caractere da tela de forma segura
int read_char (char i, char f);

// Coloca um barco no Tabuleiro
int put_nav(char **matriz, int barco, int y, int x, int dir);

// preenchimento automatico de barcos
void fill_auto(char **matriz);

//
void game();




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
