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

// Define o nivel de dificuldade utilizado em varias partes do jogo
int nivel;

// Permite criar ponteiro para a funcao play_*()
typedef int (*func_t)(jogador j, mesa matriz, mesa mascara);

/* Funcoes Internas */

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


void game()
{
        // Definição de variaveis
        int i,
            p = 0,
            jogadores,
            vazio;
        char spaco[100],
             nome[20];
        func_t joga_1, joga_2;

        jogador j1 = new_jogador(txt_default.txt[2]);
        jogador j2 = new_jogador(txt_default.txt[3]);
        mesa matriz_a;
        mesa matriz_b;
        mesa mascara_a;
        mesa mascara_b;

        // Inicio
        print_banner(10);
        // Digite o numero de jogadores:  (1-2)
        printf("%s\n", txt_perguntas.txt[3]);
        while ((jogadores=read_char('0','2')) < 0)
        {
                printf("%s\n%s\n", txt_falhas.txt[1], txt_falhas.txt[0]);
        }

        print_banner(10);
        // Digite o nivel de dificuldade: (1-3)
        printf("%s\n", txt_perguntas.txt[4]);
        while ((nivel=read_char('1','3')) < 0)
        {
                printf("%s\n%s\n", txt_falhas.txt[1], txt_falhas.txt[0]);
        }

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

        if (jogadores > 0)
        {
                print_banner(10);
                // Digite o nome do primeiro jogador, ou ENTER para default.
                printf("%s\n", txt_perguntas.txt[1]);
                jog_set_name(j1, read_string(20));
        }

        if (jogadores > 1)
        {
                print_banner(10);
                // Digite o nome do segundo jogador, ou ENTER para default.
                printf("%s\n", txt_perguntas.txt[2]);
                jog_set_name(j2, read_string(20));
        }

        joga_1 = (func_t) *play_auto;
        joga_2 = (func_t) *play_auto;

        if (jogadores > 1)
        {
                print_banner(10);
                to_fill(j1, matriz_a);
                print_banner(10);
                to_fill(j2, matriz_b);
                joga_1 = (func_t) *play_man;
                joga_2 = (func_t) *play_man;
        }
        else
        if (jogadores > 0)
        {
                print_banner(10);
                to_fill(j1, matriz_a);
                fill_auto(matriz_b);
                joga_1 = (func_t) *play_man;
        }
        else
        {
                fill_auto(matriz_a);
                fill_auto(matriz_b);
        }

        memset(spaco, ' ', 100);
        vazio = (3*tam_tabuleiro) - strlen(j1->nome) - 8;
        spaco[vazio] = '\0';

        print_banner(tam_tabuleiro);
        print_game(mascara_a, mascara_b);
        print_status (j1, j2, spaco);

        while (j1->pecas > 0 && j2->pecas > 0)
        {
                j2->pecas -= joga_1(j1, matriz_b, mascara_b);
                print_banner(tam_tabuleiro);
                print_game(mascara_a, mascara_b);
                print_status (j1, j2, spaco);

                j1->pecas -= joga_2(j2, matriz_a, mascara_a);
                print_banner(tam_tabuleiro);
                print_game(mascara_a, mascara_b);
                print_status (j1, j2, spaco);
        }

        strcpy(nome, (j1->pecas > 0) ? j1->nome : j2->nome);

        print_banner(tam_tabuleiro);
        print_game_final(matriz_a, mascara_a, matriz_b, mascara_b);

        // O jogador #nome# Venceu!!
        printf("\n%s %s %s\n\n", txt_default.txt[10], nome, txt_default.txt[11]);

        free_jogador(j1);
        free_jogador(j2);
        free_board(matriz_a);
        free_board(matriz_b);
        free_board(mascara_a);
        free_board(mascara_b);
}

char* read_string (int tam)
{
        char   *texto,
                buffer[100];
        int     letra = 0;

        texto = (char*) malloc (tam*sizeof(char));
        memset (texto, '\0', tam);

        fgets (buffer, 100, stdin);
        fgets (buffer, 100, stdin);
        clean_stdin();

        while (buffer[letra] != '\n' && letra < tam)
        {
                texto[letra] = buffer[letra];
                letra++;
        }

        return texto;
}

int read_char (char inicio, char fim)
{
        char c;

        scanf(" %c", &c);
        clean_stdin();

        c = toupper(c);

        if (c < inicio) return -1;
        if (c > fim) return -1;

        return (int) c - inicio;
}

int read_int (int inicio, int fim)
{
        int c;

        scanf(" %d", &c);
        clean_stdin();

        if (c < inicio) return -1;
        if (c > fim) return -1;

        return c - inicio;
}

static void to_fill(jogador j, mesa m)
{
        int p;

        // Deseja preenchimento automatico?
        printf("%s\n%s\n %s\n %s\n", \
        j->nome, txt_perguntas.txt[5], txt_default.txt[6], txt_default.txt[7]);

        while ((p = read_char('1','2')) < 0)
        {
                printf("%s\n", txt_falhas.txt[1]);
        }

        if (p == 1) fill_man(m);
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
                a->linha = rand()%tam_tabuleiro;
                a->coluna = rand()%tam_tabuleiro;

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
                print_banner(10);
                print_board(matriz);

                // Digite o numero barco.
                printf("%s\n", txt_perguntas.txt[11]);
                loop(i, QTD_BARCOS)
                {
                        if (limite[i] > 0)
                                printf(" %d - %-12s ( %d )\n", i+1, txt_barcos.txt[i], limite[i]);
                }

                while ((barco=read_char('1','0'+QTD_BARCOS)) < 0 || \
                       limite[barco] == 0)
                {
                        if ( barco>=0 && limite[barco] == 0)
                                printf("%s %s %s\n%s\n", txt_falhas.txt[2], \
                                txt_barcos.txt[barco], txt_falhas.txt[3], txt_falhas.txt[0]);
                        else printf("%s\n%s\n", txt_falhas.txt[1], txt_falhas.txt[0]);
                }

                // Digite a linha do #barco#
                printf("%s %s:\n", txt_perguntas.txt[6] ,txt_barcos.txt[barco]);
                while ((a->linha=read_char('A','A'+tam_tabuleiro)) < 0)
                {
                        printf("%s\n%s\n", txt_falhas.txt[1], txt_falhas.txt[0]);
                }

                // Digite a coluna do #barco#
                printf("%s %s:\n", txt_perguntas.txt[7] ,txt_barcos.txt[barco]);
                while ((a->coluna=read_int(1,tam_tabuleiro)) < 0)
                {
                        printf("%s\n%s\n", txt_falhas.txt[1], txt_falhas.txt[0]);
                }

                // Digite a orientacao do #barco#
                printf("%s %s:\n %s\n %s\n", txt_perguntas.txt[8], \
                txt_barcos.txt[barco], txt_default.txt[8] , txt_default.txt[9]);
                while ((direcao=read_char('1','2')) < 0)
                {
                        printf("%s\n%s\n", txt_falhas.txt[1], txt_falhas.txt[0]);
                }

                if ((i=put_nav(matriz, barco+2, a, direcao)) == 0)
                {
                        limite[barco]--;
                        total--;
                }
                else if (i == 1)
                {
                        // Todos os #barco# ja foram usados.
                        printf("%s %s\n%s\n", \
                        txt_barcos.txt[barco], txt_falhas.txt[4], txt_falhas.txt[0]);
                }
                else if (i == 2)
                {
                        // #barco# ultrapassa os limites do mapa.
                        printf("%s %s\n%s\n", \
                        txt_barcos.txt[barco], txt_falhas.txt[5], txt_falhas.txt[0]);
                }
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
                // Digite a linha que quer atacar.
                printf("%s\n", txt_perguntas.txt[9]);
                a->linha=read_char('A','A'+tam_tabuleiro);
                while (a->linha < 0)
                {
                        printf("%s\n%s\n", txt_falhas.txt[1], txt_falhas.txt[0]);
                        a->linha=read_char('A','A'+tam_tabuleiro);
                }


                // Digite a coluna que quer atacar.
                printf("%s\n", txt_perguntas.txt[10]);
                a->coluna=read_int(1, tam_tabuleiro);
                while (a->coluna < 0)
                {
                        printf("%s\n%s\n", txt_falhas.txt[1], txt_falhas.txt[0]);
                        a->coluna=read_int(1, tam_tabuleiro);
                }

                fim = shot(matriz, mascara, a);

                if (fim == -1)
                {
                        printf("%s\n%s\n", txt_falhas.txt[6], txt_falhas.txt[0]);
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
