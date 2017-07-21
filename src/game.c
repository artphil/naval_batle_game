/*
        Implementacao em C do jogo Batalha Naval
        ArtPhil © 2017
*/
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

// Mensagens de parabenizacao pelo tiro
const char *mensagens_acertou_tiro[QTD_MSGS_ACERTOU] = {
    "Belo tiro!",
    "Na mosca!",
    "Acertou!",
    "Cabum!"
};

// Mensagens de parabenizacao pelo tiro
const char *mensagens_errou_tiro[QTD_MSGS_ERROU] = {
    "Água!",
    "Errou!!",
    "Splash!",
    "Assustou os peixes..."
};

// Define o nivel de dificuldade utilizado em varias partes do jogo
int nivel;

// Permite criar ponteiro para a funcao play_*()
typedef int (*func_t)(jogador j, mesa matriz, mesa mascara);

/* Funcoes Internas */

// Le um caractere da tela de forma de char
static int read_char (char i, char f);

// Le um caractere da tela de forma de int
static int read_int (int i, int f);

// Preenchimento automatico de barcos
static void fill_auto(mesa matriz);

// Preenchimento manual de barcos
static void fill_man(mesa matriz);

// Define o tipo de preenchimento do tabuleiro
static void to_fill(jogador j, mesa m);

// Insere um palpite no tabuleiro do inimigo
static int shot (mesa matriz, mesa mascara, alvo a);

// Jogo automatico
static int play_auto (jogador j, mesa matriz, mesa mascara);

// Jogo manual
static int play_man (jogador j, mesa matriz, mesa mascara);

// Imprime a mensagens de parabenizacao pelo tiro
static void congratulation_message();
static void fail_message();


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
        %s\n", YLW, RESET, YLW, RESET);
        do {
                printf("Digite o numero de jogadores:  (1-2)\n");
        } while ((jogadores=read_char('0','2')) < 0);


        do {
                printf("Digite o nivel de dificuldade: (1-3)\n");
        } while ((nivel=read_char('1','3')) < 0);

        set_size(nivel);

        matriz_a  = new_mesa(AGUA);
        matriz_b  = new_mesa(AGUA);
        mascara_a = new_mesa(NADA);
        mascara_b = new_mesa(NADA);

        loop (i, QTD_BARCOS)
        {
                p += max_barcos[nivel][i]*(i+2);
        }
        j1->pecas = j2->pecas = p;

        fgets(nome, 20, stdin);
        if (jogadores > 0)
        {
                printf("Digite o nome do primeiro jogador, ou enter para default:\n");
                fgets(nome, 20, stdin);
                if (strlen(nome) > 1){
                        strcpy(nome, strtok(nome, "\n"));
                        jog_set_name(j1, nome);
                }
        }

        if (jogadores > 1)
        {
                printf("Digite o nome do segundo jogador, ou enter para default:\n");
                fgets(nome, 20, stdin);
                if (strlen(nome) > 1){
                        strcpy(nome, strtok(nome, "\n"));
                        jog_set_name(j2, nome);
                }
        }

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
        vazio = (3*tam_tabuleiro) - strlen(j1->nome) - 8;
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

static int read_char (char i, char f)
{
        char c;

        scanf(" %c", &c);
        c = toupper(c);

        if (c < i) return -1;
        if (c > f) return -1;

        return (int) c - i;
}

static int read_int (int i, int f)
{
        int c;

        scanf(" %d", &c);

        if (c < i) return -1;
        if (c > f) return -1;

        return c - i;
}

static void to_fill(jogador j, mesa m)
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

static void fill_auto(mesa matriz)
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
                a->linha = rand()%tam_tabuleiro;
                a->coluna = rand()%tam_tabuleiro;
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

static void fill_man(mesa matriz)
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
                while ((a->linha=read_char('A','A'+tam_tabuleiro)) < 0)
                {
                        printf("Entrada invalida\nTente novamente:\n");
                }

                printf("Digite a coluna do %s:\n", nome_barcos[barco]);
                while ((a->coluna=read_int(1,tam_tabuleiro)) < 0)
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

static int shot (mesa matriz, mesa mascara, alvo a)
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


static int play_auto (jogador j, mesa matriz, mesa mascara)
{
        alvo    a;
        int     fim = -1,
                alvos = j->num_alvos;

        while (fim < 0)
        {
                a = get_alvo(j);

                fim = shot(matriz, mascara, a);
                // print_game(mascara, mascara);

                if (fim == 1)
                {
                        if (alvos > 0)
                        {
                                if (a->linha>0 && a->linha<(tam_tabuleiro-1))
                                {
                                        if(mascara[a->linha+1][a->coluna] == DANO && \
                                            mascara[a->linha-1][a->coluna] == NADA)
                                        {
                                                put_alvo(j, new_alvo(a->linha-1, a->coluna));
                                        }

                                        if (mascara[a->linha-1][a->coluna] == DANO && \
                                            mascara[a->linha+1][a->coluna] == NADA)
                                        {
                                                put_alvo(j, new_alvo(a->linha+1, a->coluna));
                                        }
                                }
                                if (a->coluna>0 && a->coluna<(tam_tabuleiro-1))
                                {
                                        if (mascara[a->linha][a->coluna+1] == DANO && \
                                            mascara[a->linha][a->coluna-1] == NADA)
                                        {
                                                put_alvo(j, new_alvo(a->linha, a->coluna-1));
                                        }

                                        if (mascara[a->linha][a->coluna-1] == DANO && \
                                            mascara[a->linha][a->coluna+1] == NADA)
                                        {
                                                put_alvo(j, new_alvo(a->linha, a->coluna+1));
                                        }
                                }
                        }
                        else
                        {
                                if (a->linha<(tam_tabuleiro-1) && \
                                    mascara[a->linha+1][a->coluna] == NADA)
                                {
                                        put_alvo(j, new_alvo(a->linha+1, a->coluna));
                                }
                                if (a->coluna<(tam_tabuleiro-1) && \
                                    mascara[a->linha][a->coluna+1] == NADA)
                                {
                                        put_alvo(j, new_alvo(a->linha, a->coluna+1));
                                }
                                if (a->linha>0 && \
                                        mascara[a->linha-1][a->coluna] == NADA)
                                {
                                        put_alvo(j, new_alvo(a->linha-1, a->coluna));
                                }
                                if (a->coluna>0 && \
                                        mascara[a->linha][a->coluna-1] == NADA)
                                {
                                        put_alvo(j, new_alvo(a->linha, a->coluna-1));
                                }
                        }
                }

                free(a);
        }
        sleep(2);

        return fim;
}

static int play_man (jogador j, mesa matriz, mesa mascara)
{
        alvo a = new_alvo(0,0);
        int fim = -1;

        printf("%s\n", j->nome);

        while (fim < 0)
        {
                printf("Digite a linha que quer atacar:\n");
                a->linha=read_char('A','A'+tam_tabuleiro);
                while (a->linha < 0)
                {
                        printf("Entrada invalida\nTente novamente:\n");
                        a->linha=read_char('A','A'+tam_tabuleiro);
                }


                printf("Digite a coluna que quer atacar:\n");
                a->coluna=read_int(1, tam_tabuleiro);
                while (a->coluna < 0)
                {
                        printf("Entrada invalida\nTente novamente:\n");
                        a->coluna=read_int(1, tam_tabuleiro);
                }

                fim = shot(matriz, mascara, a);

                if (fim == -1)
                {
                        printf("Voce ja atirou aqui.\nTente novamente:\n");
                }
                else
                if (fim == 1)
                {
                        congratulation_message();
                        a->prox = j->alvos;
                        j->alvos = a;
                        j->num_alvos = 1;
                }
                else
                {
                        fail_message();
                        j->num_alvos = 0;
                }
        }
        sleep(2);

        return fim;
}

static void congratulation_message() {
    printf("%s\n", mensagens_acertou_tiro[rand()%QTD_MSGS_ACERTOU]);
}

static void fail_message() {
    printf("%s\n", mensagens_errou_tiro[rand()%QTD_MSGS_ERROU]);
}
