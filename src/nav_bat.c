/* SOURCE */

#include "nav_bat.h"

/* Variaveis globais de apoio */

const int max_barcos[3][QTD_BARCOS] = {
        {1,1,1,1,0},
        {2,2,2,1,1},
        {3,3,2,2,1}
};

const char *nome_barcos[QTD_BARCOS] = {
        "Corveta",
        "Submarino",
        "Fragata",
        "Cruzador",
        "Porta Aviões"
};

const int tam_mesa[3] = {8,10,12};
char *limpa_tela;
int pos_x,pos_y,nivel;

void sistema()
{
        // código para windows
        #if defined(WINDOWS)
        limpa_tela = "cls";
        // código para linux
        #elif defined(LINUX)
        limpa_tela = "clear";
        // código para OS X.
        #elif defined(OSX)
        limpa_tela = "clear";
        #endif
}

/* Mesa */

mesa new_board(char a)
{
        int i;
        mesa matriz = (char**)malloc(tam_mesa[nivel] * sizeof(char*));
        loop(i, tam_mesa[nivel])
        {
                matriz[i] = (char*)malloc(tam_mesa[nivel] * sizeof(char));
                memset(matriz[i], a, tam_mesa[nivel]);
        }

        return matriz;
}

void free_board(mesa m)
{
        int i;
        loop(i, tam_mesa[nivel])
        {
                free(m[i]);
        }
        free(m);
}

void print_board(mesa matriz)
{
        int i, j;
        system(limpa_tela);
        printf("    ");
        loop(i,tam_mesa[nivel]) printf("%d  ", ('M'+i));
        printf("\n\n");

        loop(i,tam_mesa[nivel])
        {
                printf("%c   ", ('A'+i));
                loop(j,tam_mesa[nivel])
                {
                        printf("%c  ", matriz[i][j]);
                }
                printf("\n");
        }
        printf("\n");
}

void print_game(mesa m_a, mesa m_b)
{
        int i, j;

        system(limpa_tela);
        printf("    ");
        loop(i,tam_mesa[nivel]) printf("%c  ", ('M'+i));
        printf("    ");
        loop(i,tam_mesa[nivel]) printf("%c  ", ('M'+i));
        printf("\n\n");

        loop(i,tam_mesa[nivel])
        {
                printf("%c   ", ('A'+i));
                loop(j,tam_mesa[nivel])
                {
                        printf("%c  ", m_a[i][j]);
                }
                printf("    ");
                loop(j,tam_mesa[nivel])
                {
                        printf("%c  ", m_b[i][j]);
                }
                printf("   %c", ('A'+i));
                printf("\n");
        }
        printf("\n");
}

int put_nav(mesa matriz, int barco, int y, int x, int dir)
{
        int i;
        if (dir == 0)
        {
                if (x + barco >= tam_mesa[nivel]) return 1;

                for (i = 0; i < barco; i++)
                        if(matriz[y][x+i] != AGUA) return 2;

                for (i = 0; i < barco; i++)
                        matriz[y][x+i] = NAVE;
        }
        else if (dir == 1)
        {
                if (y + barco >= tam_mesa[nivel]) return 1;

                for (i = 0; i < barco; i++)
                        if(matriz[y+i][x] != AGUA) return 2;

                for (i = 0; i < barco; i++)
                        matriz[y+i][x] = NAVE;
        }
        else return 3;

        return 0;
}

/* JOGADOR */

jogador new_jogador(char *nome)
{
        jogador j;
        strcpy(j.nome, nome);
        j.acertou = 0;
        j.pecas = 0;
        j.certos = NULL;

        return j;
}


int read_char (char i, char f)
{
        char c;

        scanf(" %c", &c);
        c = toupper(c);

        if (c < i) return -1;
        if (c > f) return -1;

        return (int) c - i;
}

void fill_auto(mesa matriz)
{
        srand (time (NULL));

        int i;
        int barco = QTD_BARCOS-1;
        int total = 0;
        int limite[QTD_BARCOS];

        loop (i, QTD_BARCOS)
        {
                limite[i] = max_barcos[nivel][i];
                total += max_barcos[nivel][i];
        }
        while (total > 0)
        {
                printf("%s %d t= %d\n", nome_barcos[barco], limite[barco], total);
                if (limite[barco] == 0)
                        barco--;
                else if ((put_nav(matriz, barco+2, rand()%tam_mesa[nivel], \
                                  rand()%tam_mesa[nivel], (rand()%2))) == 0)
                {
                        limite[barco]--;
                        total--;
                }
        }
}

void fill_man(mesa matriz)
{
        int i;
        int linha, coluna, direcao, barco;
        int total = 0;
        int limite[QTD_BARCOS];

        loop (i, QTD_BARCOS)
        {
                limite[i] = max_barcos[nivel][i];
                total += max_barcos[nivel][i];
        }

        while (total > 0)
        {
                print_board(matriz);

                printf("Digite o numero barco:\n");
                loop(i, QTD_BARCOS)
                {
                        if (limite[i] > 0)
                                printf("%d - %12s ( %d )\n", i+1, nome_barcos[i], limite[i]);
                }

                while ((barco=read_char('1','0'+QTD_BARCOS)) < 0 || \
                       limite[barco] == 0)
                {
                        if (limite[barco] == 0)
                                printf("Todos os %s ja foram usados.\nTente novamente:\n", \
                                       nome_barcos[barco]);
                        else printf("Entrada invalida.\nTente novamente:\n");
                }

                printf("Digite a linha do %s:\n", nome_barcos[barco]);
                while ((linha=read_char('A','A'+tam_mesa[nivel])) < 0)
                {
                        printf("Entrada invalida.\nTente novamente:\n");
                }

                printf("Digite a coluna do %s:\n", nome_barcos[barco]);
                while ((coluna=read_char('M','M'+tam_mesa[nivel])) < 0)
                {
                        printf("Entrada invalida.\nTente novamente:\n");
                }

                printf("Digite a orientacao do %s:\n 1 - Horizontal.\n 2 - Vertical.\n", \
                       nome_barcos[barco]);
                while ((direcao=read_char('1','2')) < 0)
                {
                        printf("Entrada invalida.\nTente novamente:\n");
                }

                if ((i=put_nav(matriz, barco+2, linha, coluna, direcao)) == 0)
                {
                        limite[barco]--;
                        total--;
                }
                else if (i == 1)
                        printf("O %s ultrapassa os limites do mapa\nTente novamente:\n", \
                               nome_barcos[barco]);
                else if (i == 2)
                        printf("O %s sobrepoe aliado\nTente novamente:\n", \
                               nome_barcos[barco]);
        }

}

int shot (mesa matriz, mesa mascara, alvo a)
{
        if (matriz[a.linha][a.coluna] == AGUA)
        {
                matriz[a.linha][a.coluna] = SUJO;
                mascara[a.linha][a.coluna] = ERRO;
                return 0;
        }
        else
        if (matriz[a.linha][a.coluna] == NAVE)
        {
                matriz[a.linha][a.coluna] = SUJO;
                mascara[a.linha][a.coluna] = DANO;
                return 1;
        }
        else
        {
                return -1;
        }
}


int play_auto (jogador j, mesa matriz, mesa mascara)
{
        alvo a;
        int fim = -1;

        while (fim < 0)
        {
                if (j.acertou)
                {
                        /*
                        if (j.ultimo->linha<(tam_mesa[nivel]-1) && \
                        matriz[j.ultimo->linha+1][j.ultimo->coluna] == AGUA)
                        {
                                a->linha = matriz[j.ultimo->linha+1;
                                a->coluna = j.ultimo->coluna;
                        }
                        else if (y<9 && matriz[x][y+1] == 0)
                        {
                                linha = x;
                                coluna = y+1;
                        }
                        else if (x>0 && matriz[x-1][y] == 0)
                        {
                                linha = x-1;
                                coluna = y;
                        }
                        else if (y>0 && matriz[x][y-1] == 0)
                        {
                                linha = x;
                                coluna = y-1;
                        }
                        else*/
                        {
                                a.linha = rand()%tam_mesa[nivel];
                                a.coluna = rand()%tam_mesa[nivel];
                        }
                }
                else
                {
                        a.linha = rand()%tam_mesa[nivel];
                        a.coluna = rand()%tam_mesa[nivel];
                }

                fim = shot(matriz, mascara, a);
                // print_game(mascara, mascara);

                if (fim == 1)
                {
                        a.prox = j.certos;
                        j.certos = &a;
                        j.acertou = 1;
                }
                else
                if (fim == 0) {
                        j.acertou = 0;
                }
        }

        return fim;
}

int play_man (jogador j, mesa matriz, mesa mascara)
{
        alvo a;
        int fim = -1;

        while (fim < 0)
        {
                printf("Digite a linha que quer atacar:\n");
                while ((a.linha=read_char('A','A'+tam_mesa[nivel])) < 0)
                {
                        printf("Entrada invalida.\nTente novamente:\n");
                }


                printf("Digite a coluna que quer atacar:\n");
                while ((a.coluna=read_char('M','M'+tam_mesa[nivel])) < 0)
                {
                        printf("Entrada invalida.\nTente novamente:\n");
                }

                fim = shot(matriz, mascara, a);

                if (fim == -1)
                {
                        printf("Voce ja atirou aqui.\nTente denovo:\n");
                }
                else
                if (fim == 1)
                {
                        printf("Belo tiro!\n");
                }
                else
                {
                        printf("Voce errou.\n");
                }
        }
        return fim;
}

void game()
{
        int i;

        jogador j1 = new_jogador("Jogador 1");
        jogador j2 = new_jogador("Jogador 2");
        mesa matriz_a;
        mesa matriz_b;
        mesa mascara_a;
        mesa mascara_b;

        do {
                printf("Digite o nivel do jogo:\n");
        } while ((nivel=read_char('1','3')) < 0);

        matriz_a  = new_board(AGUA);
        matriz_b  = new_board(AGUA);
        mascara_a = new_board(NADA);
        mascara_b = new_board(NADA);

        fill_auto(matriz_a);
        fill_auto(matriz_b);

        while (1)
        {
                print_game(mascara_a, mascara_b);
                play_man(j1, matriz_b, mascara_b);
                print_game(mascara_a, mascara_b);
                play_auto(j2, matriz_a, mascara_a);
        }



        free_board(matriz_a);
        free_board(matriz_b);
        free_board(mascara_a);
        free_board(mascara_b);
}
