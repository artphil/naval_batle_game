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
// Faz tosas as tarefas referentes a batalha
void game();

// Imprime os dois tabuleiros na tela
void print_game(mesa m_a, mesa m_b);

// Le um caractere da tela de forma de char
int read_char (char i, char f);

// Le um caractere da tela de forma de int
int read_int (int i, int f);

// Preenchimento automatico de barcos
void fill_auto(mesa matriz);

// Preenchimento manual de barcos
void fill_man(mesa matriz);

// Insere um palpite no tabuleiro do inimigo
int shot (mesa matriz, mesa mascara, alvo a);

// Jogo automatico
int play_auto (jogador j, mesa matriz, mesa mascara);

// Jogo manual
int play_man (jogador j, mesa matriz, mesa mascara);

#endif
