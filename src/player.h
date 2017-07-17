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

jogador new_jogador (char *nome);
int jog_set_name (jogador j, char *nome);
void free_jogador (jogador j);
alvo get_alvo (jogador j);
void put_alvo (jogador j, alvo a);

#endif
