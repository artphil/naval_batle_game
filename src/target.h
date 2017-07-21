/*
        Implementacao em C do jogo Batalha Naval
        ArtPhil © 2017
*/
#ifndef _ALVO_
#define _ALVO_

#include "source.h"

// Alvo
typedef struct ALVO *alvo;
struct ALVO
{
        int   linha;
        int   coluna;
        alvo  prox;    // Ponteiro para pilha
};

/* Funcoes exportadas */

// Cria novo alvo
alvo new_alvo(int l, int c);

// Libera memoria
void free_alvo(alvo a);

#endif
