#include "target.h"

alvo new_alvo()
{
        alvo a = (alvo)malloc(sizeof(struct ALVO));
        a->linha = 0;
        a->coluna = 0;
        a->prox = NULL;

        return a;
}

void free_alvo(alvo a)
{
        if (a->prox != NULL)
                free_alvo(a->prox);
        free(a);
        a = NULL;
}
