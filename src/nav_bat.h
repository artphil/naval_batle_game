/*
        Implementacao em C do jogo Batalha Naval
        Codigo para fins academicos
*/
#ifndef _GLOBAL_
#define _GLOBAL_

/* Bibliotecas utilizadas */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

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

/* TADs */
// Tabuleiro
typedef char** mesa ;

mesa new_board(char a);
//
void free_board(mesa m);
// Imprime uma tabela com a borda alfabetica
void print_board(mesa matriz);
void print_game(mesa m_a, mesa m_b);
int put_nav(mesa matriz, int barco, int y, int x, int dir);



// Alvo
typedef struct ALVO
{
        int linha;
        int coluna;
struct ALVO *prox;    // Ponteiro para lista
} alvo;

alvo new_alvo(int l, int c);
void free_alvo(alvo a);
// Jogador
typedef struct JOGADOR
{
        char  nome[20]; // Nome do jogador
        int   acertou;  // Se acertou o ultimo tiro
        int   pecas;     // O Tabuleiro desse jogador
        alvo *certos;   // Lista de tiros certos
} jogador;

jogador new_jogador(char *nome);


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
extern const int max_barcos[3][QTD_BARCOS];
extern const char *nome_barcos[QTD_BARCOS];
extern const int tam_mesa[3];
#define NAVE  'H'
#define AGUA  '0'
#define SUJO  '@'
#define DANO  '#'
#define ERRO  'X'
#define NADA  '.'

// Simplifacacao de funcoes
#define loop(i,a) for(i=0;i<a;i++)

/* Funcoes */
// Identifica qual sistema esta sendo usado
void sistema();

//

//

//

// Le um caractere da tela de forma segura
int read_char (char i, char f);

// Coloca um barco no Tabuleiro

// preenchimento automatico de barcos
void fill_auto(mesa matriz);

//
void fill_man(mesa matriz);

//
int play_auto (jogador j, mesa matriz, mesa mascara);

//
int play_man (jogador j, mesa matriz, mesa mascara);

//
void game();

#endif
