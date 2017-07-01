/*
        Implementacao em C do jogo Batalha Naval
        Codigo para fins academicos
*/
#ifndef _JOGO_
#define _JOGO_

#include "source.h"
#include "player.h"
#include "target.h"
#include "board.h"

/* Funcoes */
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

#endif
