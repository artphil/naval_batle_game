#include "player.h"

jogador new_jogador(char *nome)
{
        jogador j = (jogador)malloc(sizeof(struct JOGADOR));
        strcpy(j->nome, nome);
        j->acertou = 0;
        j->pecas = 0;
        j->certos = NULL;

        return j;
}

void free_jogador(jogador j)
{
        if (j->certos != NULL)
                free_alvo(j->certos);
        free(j);
        j = NULL;
}
