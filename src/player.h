#ifndef _JOGADOR_
#define _JOGADOR_


#include "source.h"
#include "target.h"

// Jogador
typedef struct JOGADOR *jogador;
struct JOGADOR
{
        char  nome[20];  // Nome do jogador
        int   acertou;   // Se acertou o ultimo tiro
        int   pecas;     // O Tabuleiro desse jogador
        alvo  alvos;    // Lista de tiros certos
};

jogador new_jogador(char *nome);
int jog_set_name(jogador j, char *nome);
void free_jogador(jogador j);

#endif
