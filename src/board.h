/*
        Implementacao em C do jogo Batalha Naval
        ArtPhil © 2017
*/
#ifndef _MESA_
#define _MESA_

#include "source.h"
#include "target.h"

typedef char** mesa;

/* Funcoes exportadas */

// Define tamanho do tabuleiro
void set_size(int t);

// Cria novo tabuleiro
mesa new_mesa(char a);

// Libera Memoria
void free_board(mesa m);

// Imprime o tabuleiro com a borda alfanumerica
void print_board(mesa matriz);

// Imprime os dois tabuleiros com borda alfanumerica
void print_game(mesa m_a, mesa m_b);

// Imprime os dois tabuleiros descobertos
void print_game_final(mesa mx_a, mesa mc_a, mesa mx_b, mesa mc_b);

// Insere um barco no tabuleiro
int put_nav(mesa matriz, int barco, alvo a, int dir);

#endif
