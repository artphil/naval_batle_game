#ifndef _ALVO_
#define _ALVO_

#include "source.h"

// Alvo
struct ALVO
{
        int linha;
        int coluna;
struct ALVO *prox;    // Ponteiro para lista
};
typedef struct ALVO *alvo;

alvo new_alvo();
void free_alvo(alvo a);

#endif
