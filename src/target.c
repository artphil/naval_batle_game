#include "target.h"

alvo new_alvo(int l, int c)
{
        alvo a = (alvo)malloc(sizeof(struct ALVO));
        a->linha = l;
        a->coluna = c;
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
