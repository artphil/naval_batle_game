/*
        Implementacao em C do jogo Batalha Naval
        Codigo para fins academicos
*/
#include "source.h"
#include "player.h"
#include "target.h"
#include "board.h"

/* Defincoes */
// Definição do sistema operacional
#if defined(__linux__) || defined(__linux)
#define LINUX
#endif

#if defined(__APPLE__)
#define OSX
#endif

#if defined(__WIN32__) || defined(__NT__)
#define WINDOWS
#endif

char *limpa_tela;

/* Funcoes */
// Identifica qual sistema esta sendo usado
void sistema();

void print_game(mesa m_a, mesa m_b);

// Le um caractere da tela de forma segura
int read_char (char i, char f);

int read_int (int i, int f);

// preenchimento automatico de barcos
void fill_auto(mesa matriz);

//
void fill_man(mesa matriz);

int shot (mesa matriz, mesa mascara, alvo a);

//
int play_auto (jogador j, mesa matriz, mesa mascara);

//
int play_man (jogador j, mesa matriz, mesa mascara);

//
void game();
