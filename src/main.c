/*
        Implementacao em C do jogo Batalha Naval
        ArtPhil © 2017
*/
#include "source.h"
#include "game.h"
#include "messages.h"


// Identifica qual sistema esta sendo usado (Linux/Windows/OSX)
void sistema();

int main ()
{
        int     continuar = 0,
                opcao;

        srand(time(NULL));

        set_language ("pt-br");
        sistema ();

        while (continuar == 0)
        {
                print_banner(10);
                // 1. Jogar / 2. lingua / 3. Sair
                printf("\n %s\n\n %s\n\n %s\n\n", \
                txt_default.txt[12], txt_default.txt[13], txt_default.txt[14]);
                while ((opcao = read_char('1','3')) < 0)
                {
                        printf("%s\n%s\n", txt_falhas.txt[1], txt_falhas.txt[0]);
                }

                if (opcao == 0)
                {
                        game();

                        // Deseja jogar novamente?
                        printf("%s\n %s\n %s\n", \
                        txt_perguntas.txt[0], txt_default.txt[6], txt_default.txt[7]);

                        while ((continuar = read_char('1','2')) < 0)
                        {
                                printf("%s\n%s\n", txt_falhas.txt[1], txt_falhas.txt[0]);
                        }
                }
                else
                if (opcao == 1)
                {
                        // 1. Portugues / 2. English
                        printf("\n %s\n %s\n", \
                        txt_default.txt[15], txt_default.txt[16]);
                        while ((opcao = read_char('1','2')) < 0)
                        {
                                printf("%s\n%s\n", txt_falhas.txt[1], txt_falhas.txt[0]);
                        }

                        if (opcao == 0) set_language ("pt-br");
                        if (opcao == 1) set_language ("en");

                }
                else
                if (opcao == 2) continuar = 1;
        }

        free_textos ();

        return 0;
}

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

void clean_stdin()
{
        setbuf(stdin, 0);
}
