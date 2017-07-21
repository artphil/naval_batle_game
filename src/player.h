/*
        Implementacao em C do jogo Batalha Naval
        ArtPhil © 2017
*/
#ifndef _JOGADOR_
#define _JOGADOR_

#include "source.h"
#include "target.h"

// Jogador
typedef struct JOGADOR *jogador;
struct JOGADOR
{
        char  nome[20];         // Nome do jogador
        int   num_alvos;        // Quantos alvos tem na fila
        int   pecas;            // O Tabuleiro desse jogador
        alvo  alvos;            // Lista de tiros certos
};

/* Funcoes exportadas */

// Cria novo jogador
jogador new_jogador (char *nome);

// Nuda nome do jogador
int jog_set_name (jogador j, char *nome);

// Libera memoria
void free_jogador (jogador j);

// Fornece proximo alvo para disparo
alvo get_alvo (jogador j);

// Adiciona alvo ao jogador
void put_alvo (jogador j, alvo a);

#endif
