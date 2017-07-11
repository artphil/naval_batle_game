#include "player.h"

jogador new_jogador(char *nome)
{
        jogador j = (jogador)malloc(sizeof(struct JOGADOR));
        strcpy(j->nome, nome);
        j->acertou = 0;
        j->pecas = 0;
        j->alvos = NULL;

        return j;
}

void free_jogador(jogador j)
{
        if (j->alvos != NULL)
                free_alvo(j->alvos);
        free(j);
        j = NULL;
}

int jog_set_name(jogador j, char *nome)
{
        printf("oi\n");
        if (nome == NULL) return -1;
        if (strlen(nome) == 0) return -1;
        if (strcmp(nome, " ") == 0) return -1;
        strcpy(j->nome, nome);
        return 0;
}
