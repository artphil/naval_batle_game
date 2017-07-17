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

alvo new_alvo(int l, int c);
void free_alvo(alvo a);

#endif
