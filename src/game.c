#include "game.h"

/* Variaveis globais de apoio */
// Quantidade maxima de cada barco por nivel de dificuldade
const int max_barcos[3][QTD_BARCOS] = {
        {1,1,1,1,0},
        {2,2,2,1,1},
        {3,3,2,2,1}
};
// Nomes dos barcos
const char *nome_barcos[QTD_BARCOS] = {
        "Corveta",
        "Submarino",
        "Fragata",
        "Cruzador",
        "Porta Aviões"
};
// Tamanho dos tabuleiros por nivel de dificuldade
const int tam_mesa[3] = {10,15,20};
// Define o nivel de dificuldade utilizado em varias partes do jogo
int nivel;
// Permite criar ponteiro para a funcao play_*()
typedef int (*func_t)(jogador j, mesa matriz, mesa mascara);


/* Funcoes Internas */

/* Funcoes Exportadas */
void game();
void print_game(mesa m_a, mesa m_b);
int read_char (char i, char f);
int read_int (int i, int f);
void to_fill(jogador j, mesa m);
void fill_auto(mesa matriz);
void fill_man(mesa matriz);
int shot (mesa matriz, mesa mascara, alvo a);
int play_auto (jogador j, mesa matriz, mesa mascara);
int play_man (jogador j, mesa matriz, mesa mascara);


void game()
{
        // Definição de variaveis
        int i,
            p=0,
            jogadores,
            vazio;
        char spaco[100],
             nome[20];
        func_t joga_1, joga_2;

        jogador j1 = new_jogador("Jogador 1");
        jogador j2 = new_jogador("Jogador 2");
        mesa matriz_a;
        mesa matriz_b;
        mesa mascara_a;
        mesa mascara_b;

        // Inicio
        system(limpa_tela);

        printf("%s\
********************************************************************************\n\
*                              %sBATAHA NAVAL%s                                    *\n\
********************************************************************************\n\
        %s\n", YEL, RESET, YEL, RESET);
        do {
                printf("Digite o numero de jogadores:  (1-2)\n");
        } while ((jogadores=read_char('0','2')) < 0);


        do {
                printf("Digite o nivel de dificuldade: (1-3)\n");
        } while ((nivel=read_char('1','3')) < 0);

        set_size(tam_mesa[nivel]);

        fgets(nome, 20, stdin);
        if (jogadores > 0)
        {
                printf("Digite o nome do primeiro jogador, ou enter para default:\n");
                // nome[0] = '\0';
                fgets(nome, 20, stdin);
                // nome[19] = '\0';
                printf("oii %s\n", nome );
                strcpy(nome, strtok(nome, "\n"));
                jog_set_name(j1, nome);
        }

        if (jogadores > 1)
        {
                printf("Digite o nome do segundo jogador, ou enter para default:\n");
                // nome[0] = '\0';
                fgets(nome, 20, stdin);
                // nome[19] = '\0';
                strcpy(nome, strtok(nome, "\n"));
                jog_set_name(j2, nome);
        }

        matriz_a  = new_mesa(AGUA);
        matriz_b  = new_mesa(AGUA);
        mascara_a = new_mesa(NADA);
        mascara_b = new_mesa(NADA);

        loop (i, QTD_BARCOS)
        {
                p += max_barcos[nivel][i]*(i+2);
        }
        j1->pecas = j2->pecas = p;

        joga_1 = (func_t) *play_auto;
        joga_2 = (func_t) *play_auto;

        if (jogadores > 1)
        {
                to_fill(j1, matriz_a);
                to_fill(j2, matriz_b);
                joga_1 = (func_t) *play_man;
                joga_2 = (func_t) *play_man;
        }
        else
        if (jogadores > 0)
        {
                to_fill(j1, matriz_a);
                fill_auto(matriz_b);
                joga_1 = (func_t) *play_man;
        }
        else
        {
                fill_auto(matriz_a);
                fill_auto(matriz_b);
        }


        print_game(mascara_a, mascara_b);

        memset(spaco, ' ', 100);
        vazio = (3*tam_mesa[nivel]) - strlen(j1->nome) - 8;
        spaco[vazio] = '\0';

        while (j1->pecas > 0 && j2->pecas > 0)
        {
                j2->pecas -= joga_1(j1, matriz_b, mascara_b);
                print_game(mascara_a, mascara_b);
                printf("Restam %d pecas do %s%sRestam %d pecas do %s\n", \
                j1->pecas, j1->nome, spaco, j2->pecas, j2->nome);
                j1->pecas -= joga_2(j2, matriz_a, mascara_a);
                print_game(mascara_a, mascara_b);
                printf("Restam %d pecas do %s%sRestam %d pecas do %s\n", \
                j1->pecas, j1->nome, spaco, j2->pecas, j2->nome);
        }

        strcpy(nome, (j1->pecas > 0) ? j1->nome : j2->nome);

        printf("\nO jogador %s Venceu!!\n\n", nome);

        free_jogador(j1);
        free_jogador(j2);
        free_board(matriz_a);
        free_board(matriz_b);
        free_board(mascara_a);
        free_board(mascara_b);
}

void print_game(mesa m_a, mesa m_b)
{
        int i, j;

        system(limpa_tela);
        // Titulo
        printf(YEL);
        loop(i,tam_mesa[nivel]) printf("%s", "***");
        printf("***************");
        loop(i,tam_mesa[nivel]) printf("%s", "***");

        printf("\n*");
        loop(i,tam_mesa[nivel]) printf("%s", "   ");
        printf(RESET);
        printf("BATALHA NAVAL");
        printf(YEL);
        loop(i,tam_mesa[nivel]) printf("%s", "   ");
        printf("*\n");

        loop(i,tam_mesa[nivel]) printf("%s", "***");
        printf("***************");
        loop(i,tam_mesa[nivel]) printf("%s", "***");
        printf(RESET);
        printf("\n\n");

        // Tabuleiros
        printf("   ");
        loop(i,tam_mesa[nivel]) printf("%2d ", (1+i));
        printf("       ");
        loop(i,tam_mesa[nivel]) printf("%2d ", (1+i));
        printf("\n\n");

        loop(i,tam_mesa[nivel])
        {
                printf("%c   ", ('A'+i));
                loop(j,tam_mesa[nivel])
                {
                        if (m_a[i][j]==NADA) printf(BLU);
                        else if (m_a[i][j]==ERRO) printf(RED);
                        else if (m_a[i][j]==DANO) printf(GRN);
                        printf("%c  ", m_a[i][j]);
                        printf(RESET);
                }
                printf("       ");
                loop(j,tam_mesa[nivel])
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

int read_char (char i, char f)
{
        char c;

        scanf(" %c", &c);
        c = toupper(c);

        if (c < i) return -1;
        if (c > f) return -1;

        return (int) c - i;
}

int read_int (int i, int f)
{
        int c;

        scanf(" %d", &c);

        if (c < i) return -1;
        if (c > f) return -1;

        return c - i;
}

void to_fill(jogador j, mesa m)
{
        int p;

        printf("%s\nDeseja preenchimento automatico\n 1 - Sim\n 2 - Nao\n", j->nome);
        p=read_char('1','2');
        while (p < 0) ;
        {
                printf("Valor invalido\n");
                p=read_char('1','2');
        }

        if (p) fill_man(m);
        else fill_auto(m);
}

void fill_auto(mesa matriz)
{
        int i;
        alvo a = new_alvo(0,0);
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
                print_board(matriz);
                a->linha = rand()%tam_mesa[nivel];
                a->coluna = rand()%tam_mesa[nivel];
                printf("%s %d t= %d\n", nome_barcos[barco], limite[barco], total);
                if (limite[barco] == 0)
                        barco--;
                else if ((put_nav(matriz, barco+2, a,(rand()%2))) == 0)
                {
                        limite[barco]--;
                        total--;
                }
        }
}

void fill_man(mesa matriz)
{
        int i;
        alvo a = new_alvo(0,0);
        int direcao, barco;
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
                        else printf("Entrada invalida\nTente novamente:\n");
                }

                printf("Digite a linha do %s:\n", nome_barcos[barco]);
                while ((a->linha=read_char('A','A'+tam_mesa[nivel])) < 0)
                {
                        printf("Entrada invalida\nTente novamente:\n");
                }

                printf("Digite a coluna do %s:\n", nome_barcos[barco]);
                while ((a->coluna=read_int(1,tam_mesa[nivel])) < 0)
                {
                        printf("Entrada invalida\nTente novamente:\n");
                }

                printf("Digite a orientacao do %s:\n 1 - Horizontal.\n 2 - Vertical.\n", \
                       nome_barcos[barco]);
                while ((direcao=read_char('1','2')) < 0)
                {
                        printf("Entrada invalida\nTente novamente:\n");
                }

                if ((i=put_nav(matriz, barco+2, a, direcao)) == 0)
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
        if (matriz[a->linha][a->coluna] == AGUA)
        {
                matriz[a->linha][a->coluna] = SUJO;
                mascara[a->linha][a->coluna] = ERRO;
                return 0;
        }
        else
        if (matriz[a->linha][a->coluna] == NAVE)
        {
                matriz[a->linha][a->coluna] = SUJO;
                mascara[a->linha][a->coluna] = DANO;
                return 1;
        }
        else
        {
                return -1;
        }
}


int play_auto (jogador j, mesa matriz, mesa mascara)
{
        alvo a, p;
        int fim = -1;

        while (fim < 0)
        {
                if (j->alvos != NULL)
                {
                        a = j->alvos;
                        j->alvos = a->prox;
                }
                else
                {
                        a = new_alvo( rand()%tam_mesa[nivel], rand()%tam_mesa[nivel] );
                }

                fim = shot(matriz, mascara, a);
                // print_game(mascara, mascara);

                if (fim == 1)
                {
                        if (j->acertou > 0)
                        {
                                j->acertou >>= 1;
                                if (a->linha>0 && a->linha<(tam_mesa[nivel]-1))
                                {
                                        if(mascara[a->linha+1][a->coluna] == DANO)
                                        {
                                                p = new_alvo(a->linha-1, a->coluna);
                                                p->prox = j->alvos;
                                                j->alvos = p;
                                        }
                                        else
                                        if (mascara[a->linha-1][a->coluna] == DANO)
                                        {
                                                p = new_alvo(a->linha+1, a->coluna);
                                                p->prox = j->alvos;
                                                j->alvos = p;
                                        }
                                }
                                if (a->coluna>0 && a->coluna<(tam_mesa[nivel]-1))
                                {
                                        if (mascara[a->linha][a->coluna+1] == DANO)
                                        {
                                                p = new_alvo(a->linha, a->coluna-1);
                                                p->prox = j->alvos;
                                                j->alvos = p;
                                        }
                                        else
                                        if (mascara[a->linha][a->coluna-1] == DANO)
                                        {
                                                p = new_alvo(a->linha, a->coluna+1);
                                                p->prox = j->alvos;
                                                j->alvos = p;
                                        }
                                }
                        }
                        else
                        {
                                if (a->linha<(tam_mesa[nivel]-1) && \
                                    mascara[a->linha+1][a->coluna] == NADA)
                                {
                                        p = new_alvo(a->linha+1, a->coluna);
                                        p->prox = j->alvos;
                                        j->alvos = p;
                                }
                                if (a->coluna<(tam_mesa[nivel]-1) && \
                                    mascara[a->linha][a->coluna+1] == NADA)
                                {
                                        p = new_alvo(a->linha, a->coluna+1);
                                        p->prox = j->alvos;
                                        j->alvos = p;
                                }
                                if (a->linha>0 && \
                                        mascara[a->linha-1][a->coluna] == NADA)
                                {
                                        p = new_alvo(a->linha-1, a->coluna);
                                        p->prox = j->alvos;
                                        j->alvos = p;
                                }
                                if (a->coluna>0 && \
                                        mascara[a->linha][a->coluna-1] == NADA)
                                {
                                        p = new_alvo(a->linha, a->coluna-1);
                                        p->prox = j->alvos;
                                        j->alvos = p;
                                }
                        }
                }

                free(a);
        }
        sleep(2);

        j->acertou |= fim<<1;
        return fim;
}

int play_man (jogador j, mesa matriz, mesa mascara)
{
        alvo a = new_alvo(0,0);
        int fim = -1;

        printf("%s\n", j->nome);

        while (fim < 0)
        {
                printf("Digite a linha que quer atacar:\n");
                a->linha=read_char('A','A'+tam_mesa[nivel]);
                while (a->linha < 0)
                {
                        printf("Entrada invalida\nTente novamente:\n");
                        a->linha=read_char('A','A'+tam_mesa[nivel]);
                }


                printf("Digite a coluna que quer atacar:\n");
                a->coluna=read_int(1, tam_mesa[nivel]);
                while (a->coluna < 0)
                {
                        printf("Entrada invalida\nTente novamente:\n");
                        a->coluna=read_int(1, tam_mesa[nivel]);
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
                        a->prox = j->alvos;
                        j->alvos = a;
                        j->acertou = 1;
                }
                else
                {
                        printf("Voce errou.\n");
                        j->acertou = 0;
                }
        }
        sleep(2);

        return fim;
}
