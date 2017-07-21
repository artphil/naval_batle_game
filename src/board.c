/*
        Implementacao em C do jogo Batalha Naval
        ArtPhil © 2017
*/
#include "board.h"

// Tamanho dos tabuleiros por nivel de dificuldade
const int tam_mesa[3] = {10,15,20};

void set_size (int nivel)
{
        tam_tabuleiro = tam_mesa[nivel];
}

mesa new_mesa (char a)
{
        int i;
        mesa matriz = (char**)malloc(tam_tabuleiro * sizeof(char*));
        loop(i, tam_tabuleiro)
        {
                matriz[i] = (char*)malloc(tam_tabuleiro * sizeof(char));
                memset(matriz[i], a, tam_tabuleiro);
        }

        return matriz;
}

void free_board(mesa matriz)
{
        int i;
        loop(i, tam_tabuleiro)
        {
                free(matriz[i]);
        }
        free(matriz);
}

void print_board(mesa matriz)
{
        int i, j;
        printf("   ");
        loop(i,tam_tabuleiro) printf("%2d ", (1+i));
        printf("\n\n");

        loop(i,tam_tabuleiro)
        {
                printf("%c   ", ('A'+i));
                loop(j,tam_tabuleiro)
                {
                        printf("%c  ", matriz[i][j]);
                }
                printf("\n");
        }
        printf("\n");
}


int put_nav(mesa matriz, int barco, alvo a, int dir)
{
        int i;
        if (dir == 0)
        {
                if (a->coluna + barco >= tam_tabuleiro) return 1;

                for (i = 0; i < barco; i++)
                        if(matriz[a->linha][a->coluna+i] != AGUA) return 2;

                for (i = 0; i < barco; i++)
                        matriz[a->linha][a->coluna+i] = NAVE;
        }
        else if (dir == 1)
        {
                if (a->linha + barco >= tam_tabuleiro) return 1;

                for (i = 0; i < barco; i++)
                        if(matriz[a->linha+i][a->coluna] != AGUA) return 2;

                for (i = 0; i < barco; i++)
                        matriz[a->linha+i][a->coluna] = NAVE;
        }
        else return 3;

        return 0;
}

void print_game(mesa m_a, mesa m_b)
{
        int i, j;

        system(limpa_tela);
        // Titulo
        printf(YLW);
        loop(i,tam_tabuleiro) printf("%s", "***");
        printf("***************");
        loop(i,tam_tabuleiro) printf("%s", "***");

        printf("\n*");
        loop(i,tam_tabuleiro) printf("%s", "   ");
        printf(RESET);
        printf("BATALHA NAVAL");
        printf(YLW);
        loop(i,tam_tabuleiro) printf("%s", "   ");
        printf("*\n");

        loop(i,tam_tabuleiro) printf("%s", "***");
        printf("***************");
        loop(i,tam_tabuleiro) printf("%s", "***");
        printf(RESET);
        printf("\n\n");

        // Tabuleiros
        printf("   ");
        loop(i,tam_tabuleiro) printf("%2d ", (1+i));
        printf("       ");
        loop(i,tam_tabuleiro) printf("%2d ", (1+i));
        printf("\n\n");

        loop(i,tam_tabuleiro)
        {
                printf("%c   ", ('A'+i));
                loop(j,tam_tabuleiro)
                {
                        if (m_a[i][j]==NADA) printf(BLU);
                        else if (m_a[i][j]==ERRO) printf(RED);
                        else if (m_a[i][j]==DANO) printf(GRN);
                        printf("%c  ", m_a[i][j]);
                        printf(RESET);
                }
                printf("       ");
                loop(j,tam_tabuleiro)
                {
                        if (m_b[i][j]==NADA) printf(BLU);
                        else if (m_b[i][j]==ERRO) printf(RED);
                        else if (m_b[i][j]==DANO) printf(GRN);
                        printf("%c  ", m_b[i][j]);
                        printf(RESET);

                }
                printf("   %c", ('A'+i));
                printf("\n");
        }
        printf("\n");
}
