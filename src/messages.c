/*
        Implementacao em C do jogo Batalha Naval
        ArtPhil © 2017
*/
#include "source.h"
#include "messages.h"

/* Funcoes internas */
static void free_txt(texto t);
static void fill_text (texto *t, FILE *f);


/* Variaveis internas */



void set_language(char *lingua)
{
        FILE *arq;
        char  caminho[20];

        caminho[0] = '\0';
        strcat (caminho, DIR);
        strcat (caminho, lingua);
        strcat (caminho, EXT);

        if ((arq = fopen (caminho, "r"))==NULL)
        {
                printf("Arquivo %s nao encontrado.\n", caminho);
                return;
        }

        fill_text (&txt_default, arq);
        fill_text (&txt_perguntas, arq);
        fill_text (&txt_falhas, arq);
        fill_text (&txt_barcos, arq);
        fill_text (&txt_tiro_certo, arq);
        fill_text (&txt_tiro_errado, arq);

        fclose (arq);
}

void free_textos ()
{
        free_txt (txt_falhas);
        free_txt (txt_default);
        free_txt (txt_barcos);
        free_txt (txt_tiro_certo);
        free_txt (txt_tiro_errado);
}

void print_banner(int largura)
{
        int i;

        system(limpa_tela);

        printf(YLW);
        loop(i,largura) printf("%s", "***");
        printf("***************");
        loop(i,largura) printf("%s", "***");

        printf("\n*");
        loop(i,largura) printf("%s", "   ");
        printf(RESET);
        printf("%s", txt_default.txt[1]);
        printf(YLW);
        loop(i,largura) printf("%s", "   ");
        printf("*\n");

        loop(i,largura) printf("%s", "***");
        printf("***************");
        loop(i,largura) printf("%s", "***");
        printf(RESET);
        printf("\n\n");

}

void congratulation_message() {
    printf("%s\n", txt_tiro_certo.txt[rand()%txt_tiro_certo.qtd]);
}

void fail_message() {
    printf("%s\n", txt_tiro_errado.txt[rand()%txt_tiro_errado.qtd]);
}

static void fill_text (texto *t, FILE *f)
{
        int   i;
        char  buffer[100];

        fgets (buffer, 100 ,f);
        t->qtd = atoi(buffer);
        t->txt = (char**) malloc (t->qtd*sizeof(char*));

        loop(i, t->qtd)
        {
                fgets (buffer, 100 ,f);
                buffer[strlen(buffer)-1] = '\0';
                t->txt[i] = malloc (strlen(buffer)*sizeof(char));
                strcpy (t->txt[i], buffer);
        }
}

static void free_txt(texto t)
{
        int i;
        loop(i, t.qtd) free (t.txt[i]);
        free (t.txt);
}
