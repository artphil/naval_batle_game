/*
        Implementacao em C do jogo Batalha Naval
        ArtPhil © 2017
*/
#include "player.h"

jogador new_jogador(char *nome)
{
        jogador j = (jogador)malloc(sizeof(struct JOGADOR));
        strcpy(j->nome, nome);
        j->num_alvos = 0;
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

alvo get_alvo (jogador j)
{
        alvo a;

        if (j->num_alvos > 0)
        {
                j->num_alvos--;
                a = j->alvos;
                j->alvos = a->prox;
        }
        else
                a = new_alvo(rand()%tam_tabuleiro, rand()%tam_tabuleiro);

        return a;
}

void put_alvo (jogador j, alvo a)
{
        j->num_alvos++;
        a->prox = j->alvos;
        j->alvos = a;
}
